#include "modobloqueado.h"
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

ModoBloqueado::ModoBloqueado(QWidget *parent) : Pantalla(parent) {
    inicializarUI();
    cargarDatos();
    conectarEventos();
    registrarEvento("Sistema bloqueado temporalmente.");
}

ModoBloqueado::~ModoBloqueado() {}

void ModoBloqueado::inicializarUI() {
    setWindowTitle("Sistema Bloqueado");
    setFixedSize(300, 200);
    setStyleSheet("background-color: #8b0000; color: white;"); // Rojo oscuro de alerta

    QVBoxLayout *layout = new QVBoxLayout(this);

    lblMensaje = new QLabel("Demasiados intentos fallidos.\nEl sistema ha sido bloqueado.");
    lblMensaje->setAlignment(Qt::AlignCenter);
    lblMensaje->setStyleSheet("font-weight: bold; font-size: 14px;");

    lblTiempo = new QLabel("Espere...");
    lblTiempo->setAlignment(Qt::AlignCenter);
    lblTiempo->setStyleSheet("font-size: 24px; font-weight: bold; margin-top: 15px;");

    layout->addWidget(lblMensaje);
    layout->addWidget(lblTiempo);

    timerSegundos = new QTimer(this);
}

void ModoBloqueado::cargarDatos() {
    // Leemos el tiempo exacto que pusiste en el config.ini
    QString rutaConfig = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(rutaConfig, QSettings::IniFormat);

    segundosRestantes = settings.value("Seguridad/tiempo_bloqueo", 10).toInt();
    lblTiempo->setText(QString::number(segundosRestantes) + " s");
}

void ModoBloqueado::conectarEventos() {
    // Conectamos el timer para que haga "tic" cada 1000 milisegundos (1 segundo)
    connect(timerSegundos, &QTimer::timeout, this, &ModoBloqueado::actualizarReloj);
    timerSegundos->start(1000);
}

void ModoBloqueado::validarEstado() {
    if (segundosRestantes <= 0) {
        timerSegundos->stop();
        registrarEvento("Desbloqueo automático. Volviendo al Login.");

        // ¡POLIMORFISMO! Emitimos la señal avisando que volvemos a la pantalla 0 (Login)
        emit solicitarCambio(0);
    }
}

void ModoBloqueado::registrarEvento(const QString &mensaje) {
    QString rutaLog = QCoreApplication::applicationDirPath() + "/registro.log";
    QFile file(rutaLog);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "] BLOQUEO: " << mensaje << "\n";
        file.close();
    }
}

void ModoBloqueado::actualizarReloj() {
    segundosRestantes--;
    lblTiempo->setText(QString::number(segundosRestantes) + " s");
    validarEstado(); // Verificamos si ya llegó a 0
}