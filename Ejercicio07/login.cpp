#include "login.h"
#include "ui_login.h"
#include "ventanaprincipal.h" // ¡Incluimos el archivo correcto de tu CV!
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>

Login::Login(QWidget *parent) :
    Pantalla(parent),
    ui(new Ui::Login),
    intentosFalla(0)
{
    ui->setupUi(this);

    timerBloqueo = new QTimer(this);
    timerBloqueo->setSingleShot(true);

    apiClima = new GestorClima(this);
    apiImagen = new GestorImagen(this);

    connect(ui->btnIngresar, &QPushButton::clicked, this, &Login::intentarLogin);
    connect(timerBloqueo, &QTimer::timeout, this, &Login::desbloquearLogin);

    connect(apiClima, &GestorClima::datosClimaListos, this, &Login::actualizarLabels);
    connect(apiImagen, &GestorImagen::imagenLista, this, &Login::abrirVentanaPrincipal);

    inicializarUI();
    cargarTextos();

    registrarLog("Aplicación iniciada. Pantalla de login cargada.");

    apiClima->iniciarPeticion();
}

Login::~Login() {
    delete ui;
}

void Login::inicializarUI() {
}

void Login::cargarTextos() {
    setWindowTitle("Ingreso al Sistema - Ejercicio 07");
    ui->lblClima->setText("Clima: Cargando...");
    ui->lblReloj->setText("Hora: Cargando...");
}

void Login::actualizarLabels(const QString &clima, const QString &hora) {
    ui->lblClima->setText(clima);
    ui->lblReloj->setText(hora);
}

void Login::registrarLog(const QString &mensaje) {
    QString rutaLog = QCoreApplication::applicationDirPath() + "/registro.log";
    QFile file(rutaLog);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString fechaHora = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        out << "[" << fechaHora << "] - " << mensaje << "\n";
        file.close();
    }
}

void Login::intentarLogin() {
    QString user = ui->txtUsuario->text();
    QString pass = ui->txtPassword->text();

    if (user == "admin" && pass == "1234") {
        registrarLog("Login EXITOSO. Usuario: " + user);

        ui->btnIngresar->setEnabled(false);
        ui->btnIngresar->setText("Descargando recursos...");

        apiImagen->iniciarPeticion();

    } else {
        intentosFalla++;
        registrarLog("Login FALLIDO (" + QString::number(intentosFalla) + "/3). Usuario intentado: " + user);

        if (intentosFalla >= 3) {
            ui->btnIngresar->setEnabled(false);
            QMessageBox::critical(this, "Bloqueado", "Demasiados intentos fallidos. Espere 10 segundos.");
            registrarLog("Sistema BLOQUEADO por seguridad.");
            timerBloqueo->start(10000);
        } else {
            QMessageBox::warning(this, "Error", "Credenciales incorrectas. Intentos restantes: " + QString::number(3 - intentosFalla));
        }
    }
}

void Login::desbloquearLogin() {
    intentosFalla = 0;
    ui->btnIngresar->setEnabled(true);
    ui->btnIngresar->setText("Ingresar");
    ui->txtPassword->clear();

    registrarLog("Sistema DESBLOQUEADO tras tiempo de espera.");
    QMessageBox::information(this, "Desbloqueado", "Puede volver a intentar.");
}

void Login::abrirVentanaPrincipal(const QString &rutaImagen) {
    registrarLog("Imagen descargada/leída. Abriendo CV en FullScreen.");

    // ¡Acá llamamos a TU clase VentanaPrincipal exactamente como la armaste!
    VentanaPrincipal *cv = new VentanaPrincipal(rutaImagen);
    cv->showFullScreen();

    this->close();
}