#include "editorprincipal.h"
#include "validadores.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>
#include <QSettings>
#include <QPixmap>
#include <QStandardPaths>

EditorPrincipal::EditorPrincipal(QWidget *parent) : Pantalla(parent) {
    inicializarUI();
    conectarEventos();
    cargarDatos();
    registrarEvento("Editor Principal iniciado.");
}

EditorPrincipal::~EditorPrincipal() {}

void EditorPrincipal::inicializarUI() {
    // Layout principal dividido en dos
    QHBoxLayout *layoutPrincipal = new QHBoxLayout(this);
    layoutPrincipal->setContentsMargins(10, 10, 10, 10);

    // --- PANEL IZQUIERDO: EL EDITOR ---
    QWidget *panelEditor = new QWidget(this);
    QVBoxLayout *layoutEditor = new QVBoxLayout(panelEditor);

    // Barra superior de herramientas
    QHBoxLayout *barraSup = new QHBoxLayout();
    cmbLenguaje = new QComboBox();
    cmbLenguaje->addItems({"C++", "Python", "Java"});
    btnExportar = new QPushButton("Exportar a JPG");
    barraSup->addWidget(new QLabel("<b>Lenguaje:</b>"));
    barraSup->addWidget(cmbLenguaje);
    barraSup->addStretch();
    barraSup->addWidget(btnExportar);

    // Nuestro editor polimórfico
    editor = new CodeEditor();
    lblEstado = new QLabel("Sintaxis OK.");
    lblEstado->setStyleSheet("color: green; font-weight: bold; padding: 5px;");

    layoutEditor->addLayout(barraSup);
    layoutEditor->addWidget(editor);
    layoutEditor->addWidget(lblEstado);

    // --- PANEL DERECHO: CURRÍCULUM LINKEDIN ---
    QWidget *panelCV = crearPanelCV();

    // Proporciones: 75% el código, 25% el CV
    layoutPrincipal->addWidget(panelEditor, 3);
    layoutPrincipal->addWidget(panelCV, 1);
}

QWidget* EditorPrincipal::crearPanelCV() {
    QWidget *cv = new QWidget();
    cv->setStyleSheet("background-color: #2c3e50; color: white; border-radius: 10px; padding: 10px;");
    QVBoxLayout *layout = new QVBoxLayout(cv);

    QLabel *lblFoto = new QLabel("👨‍💻"); // Un emoji como foto por ahora
    lblFoto->setAlignment(Qt::AlignCenter);
    lblFoto->setStyleSheet("font-size: 60px;");

    QLabel *lblNombre = new QLabel("Lorenzo Poletto");
    lblNombre->setStyleSheet("font-size: 22px; font-weight: bold; color: #3498db;");
    lblNombre->setAlignment(Qt::AlignCenter);

    QLabel *lblTitulo = new QLabel("Estudiante de Ingeniería Informática\nUniversidad Blas Pascal");
    lblTitulo->setStyleSheet("font-size: 14px; font-style: italic;");
    lblTitulo->setAlignment(Qt::AlignCenter);

    QLabel *lblSkills = new QLabel(
        "<b>🛠️ Habilidades Técnicas:</b><br><br>"
        "• C++ & Qt Framework<br>"
        "• Python (FastAPI)<br>"
        "• Node.js & Docker<br>"
        "• Google AI Studio & Gemini API<br>"
        "• Arquitectura Cliente-Servidor"
        );
    lblSkills->setStyleSheet("margin-top: 20px; font-size: 13px; line-height: 1.5;");

    layout->addWidget(lblFoto);
    layout->addWidget(lblNombre);
    layout->addWidget(lblTitulo);
    layout->addWidget(lblSkills);
    layout->addStretch();

    return cv;
}

void EditorPrincipal::conectarEventos() {
    // Conectamos ComboBox, Señales del Editor y el Botón
    connect(cmbLenguaje, &QComboBox::currentTextChanged, this, &EditorPrincipal::cambiarLenguaje);
    connect(editor, &CodeEditor::validacionResult, this, &EditorPrincipal::mostrarErrorSintaxis);
    connect(btnExportar, &QPushButton::clicked, this, &EditorPrincipal::exportarCodigo);
}

void EditorPrincipal::cargarDatos() {
    QString rutaConfig = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(rutaConfig, QSettings::IniFormat);

    QString lengDefecto = settings.value("Editor/lenguaje_defecto", "C++").toString();
    rutaExportacion = settings.value("Editor/ruta_exportacion", "codigo_exportado.jpg").toString();

    // 1. FORZAMOS la creación de la inteligencia inicial (El polimorfismo arranca acá)
    cambiarLenguaje(lengDefecto);

    // 2. Actualizamos la cajita visual
    cmbLenguaje->setCurrentText(lengDefecto);
}

void EditorPrincipal::validarEstado() {
    // Si quisieras validar que el editor no esté vacío, iría acá
}

void EditorPrincipal::registrarEvento(const QString &mensaje) {
    QString rutaLog = QCoreApplication::applicationDirPath() + "/registro.log";
    QFile file(rutaLog);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "] EDITOR: " << mensaje << "\n";
        file.close();
    }
}

void EditorPrincipal::cambiarLenguaje(const QString &lenguaje) {
    registrarEvento("Cambio de lenguaje a: " + lenguaje);

    // POLIMORFISMO PURO: Cambiamos la inteligencia del editor en tiempo de ejecución
    if (lenguaje == "C++") {
        editor->setValidador(new ValidadorCpp());
    } else if (lenguaje == "Python") {
        editor->setValidador(new ValidadorPython());
    } else if (lenguaje == "Java") {
        editor->setValidador(new ValidadorJava());
    }
}

void EditorPrincipal::mostrarErrorSintaxis(const QString &mensaje, bool esError) {
    lblEstado->setText(mensaje);
    if (esError) {
        lblEstado->setStyleSheet("color: white; font-weight: bold; background-color: #cc0000; padding: 5px; border-radius: 3px;");
    } else {
        lblEstado->setStyleSheet("color: #00cc66; font-weight: bold; padding: 5px;");
    }
}

void EditorPrincipal::exportarCodigo() {
    // Buscamos la ruta del Escritorio automáticamente (funciona en Mac, Windows y Linux)
    QString rutaEscritorio = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString rutaFinal = rutaEscritorio + "/" + rutaExportacion;

    QPixmap captura = editor->grab();
    captura.save(rutaFinal, "JPG");

    QMessageBox::information(this, "Exportación exitosa", "El código se ha exportado como imagen en:\n" + rutaFinal);
    registrarEvento("Código exportado a " + rutaFinal);
}

// --------------------------------------------------------
// EVENTOS REESCRITOS DE LA VENTANA (Requisito)
// --------------------------------------------------------

void EditorPrincipal::closeEvent(QCloseEvent *event) {
    // Interceptamos el evento de cerrar la ventana (la 'X' de la esquina)
    QMessageBox::StandardButton res = QMessageBox::question(this, "Salir del Editor",
                                                            "¿Desea exportar el código a JPG antes de salir?",
                                                            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (res == QMessageBox::Yes) {
        exportarCodigo();
        event->accept(); // Permitimos que se cierre
    } else if (res == QMessageBox::No) {
        event->accept(); // Permitimos que se cierre sin guardar
    } else {
        event->ignore(); // CANCELAMOS el cierre. La ventana sigue abierta.
    }
}

void EditorPrincipal::resizeEvent(QResizeEvent *event) {
    // Registramos en el log cuando el usuario cambia el tamaño de la ventana
    registrarEvento("Resolución adaptada a: " + QString::number(event->size().width()) + "x" + QString::number(event->size().height()));
    Pantalla::resizeEvent(event);
}