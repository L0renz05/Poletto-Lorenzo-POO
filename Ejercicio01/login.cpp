#include "login.h"
#include "./ui_login.h"
#include "tablero.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    // Configuramos el campo de password para que no se vea el texto
    ui->txtPassword->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("AlcancIA - Login");
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnIngresar_clicked()
{
    QString user = ui->txtUsuario->text();
    QString pass = ui->txtPassword->text();

    // Validación local simple
    if (user == "lolo" && pass == "1234") {

        // PERSISTENCIA: Guardamos la sesión en un archivo local
        QFile archivo("sesion.txt");
        if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&archivo);
            out << user << "\n";
            out << QDateTime::currentDateTime().toString();
            archivo.close();
        }

        // SALTO DE VENTANA: Cerramos esta y abrimos el Tablero
        Tablero *ventanaTablero = new Tablero();
        ventanaTablero->show();
        this->close();

    } else {
        QMessageBox::critical(this, "Error de Acceso", "Usuario o contraseña incorrectos.");
    }
}