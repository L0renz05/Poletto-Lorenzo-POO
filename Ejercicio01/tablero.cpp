#include "tablero.h"
#include "ui_tablero.h"
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QComboBox> // Para el estado

// Variable global para saber qué materia estamos editando
QString materiaActual = "";

Tablero::Tablero(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tablero)
{
    ui->setupUi(this);
    this->setWindowTitle("AlcancIA - Planificador de TPs");

    // Limpiamos los textos de los botones de la UI que quedaron con "PushButton"
    ui->btnAgregar->setText("Agregar Materia");
    ui->btnGuardar->setText("Guardar Notas");

    grilla = qobject_cast<QGridLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!grilla) grilla = new QGridLayout(ui->scrollAreaWidgetContents);

    grilla->addWidget(new QLabel("<b>MATERIA</b>"), 0, 0);
    grilla->addWidget(new QLabel("<b>ESTADO</b>"), 0, 1);
    grilla->addWidget(new QLabel("<b>ACCIÓN</b>"), 0, 2);

    static int filaActual = 1;
    connect(ui->btnAgregar, &QPushButton::clicked, [=]() mutable {
        QString nombre = ui->txtNuevoTP->text();
        if(!nombre.isEmpty()){
            grilla->addWidget(new QLabel(nombre), filaActual, 0);

            // CAMBIO: Ahora el estado es un menú desplegable
            QComboBox *comboEstado = new QComboBox();
            comboEstado->addItems({"Pendiente", "En curso", "Entregado"});
            grilla->addWidget(comboEstado, filaActual, 1);

            QPushButton *btnAutoEdit = new QPushButton("Editar Notas");
            grilla->addWidget(btnAutoEdit, filaActual, 2);

            // Conectamos el botón para que sepa qué materia editar
            connect(btnAutoEdit, &QPushButton::clicked, [=](){
                materiaActual = nombre; // Guardamos el nombre de la materia clicqueada
                this->slot_editar_tp();
            });

            ui->txtNuevoTP->clear();
            filaActual++;
        }
    });

    connect(ui->btnGuardar, &QPushButton::clicked, this, &Tablero::slot_guardar_nota);
}

void Tablero::slot_editar_tp() {
    ui->editorNotas->setFocus();
    ui->editorNotas->clear();

    // Cargamos el archivo específico de ESTA materia
    QFile archivo(materiaActual + ".txt");
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        ui->editorNotas->setPlainText(in.readAll());
        archivo.close();
    }
    // Mostramos en el label qué estamos editando
    ui->btnGuardar->setText("Guardar Notas de: " + materiaActual);
}

void Tablero::slot_guardar_nota() {
    if(materiaActual == "") {
        QMessageBox::warning(this, "Error", "Primero seleccioná 'Editar' en una materia.");
        return;
    }

    QFile archivo(materiaActual + ".txt");
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo);
        out << ui->editorNotas->toPlainText();
        archivo.close();
        QMessageBox::information(this, "Guardado", "Notas de " + materiaActual + " guardadas.");
    }
}

Tablero::~Tablero() {
    delete ui;
}