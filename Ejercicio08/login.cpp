#include "login.h"
#include "ui_login.h" // Este archivo lo genera Qt automáticamente al compilar
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>
#include <QSettings>

Login::Login(QWidget *parent) :
    Pantalla(parent),
    ui(new Ui::Login),
    intentosFalla(0)
{
    ui->setupUi(this); // Crea los botones y campos en la pantalla

    inicializarUI();
    conectarEventos();
    cargarDatos();

    registrarEvento("Pantalla de Login iniciada.");
}

Login::~Login() {
    delete ui;
}

void Login::inicializarUI() {
    setWindowTitle("Acceso al Editor Multilenguaje");
}

void Login::conectarEventos() {
    connect(ui->btnIngresar, &QPushButton::clicked, this, &Login::intentarLogin);
}

void Login::cargarDatos() {
    QString rutaConfig = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(rutaConfig, QSettings::IniFormat);
    QString userInicial = settings.value("Seguridad/usuario", "admin").toString();
    ui->txtUsuario->setText(userInicial);
}

void Login::validarEstado() {
    if (intentosFalla >= 3) {
        registrarEvento("Límite de intentos superado. Bloqueando...");
        emit solicitarCambio(2); // ID para ModoBloqueado
    }
}

void Login::registrarEvento(const QString &mensaje) {
    QString rutaLog = QCoreApplication::applicationDirPath() + "/registro.log";
    QFile file(rutaLog);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "] LOGIN: " << mensaje << "\n";
        file.close();
    }
}

void Login::intentarLogin() {
    if (ui->txtUsuario->text() == "admin" && ui->txtPassword->text() == "1234") {
        registrarEvento("Acceso concedido.");
        emit solicitarCambio(1); // ID para EditorPrincipal
    } else {
        intentosFalla++;
        registrarEvento("Intento fallido: " + QString::number(intentosFalla));
        QMessageBox::warning(this, "Error", "Credenciales incorrectas.");
        validarEstado();
    }
}