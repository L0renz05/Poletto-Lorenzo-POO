#include "login.h"
#include "ui_Login.h"
#include <QMessageBox>
#include "pintura.h"

Login::Login(AdminDB *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    baseDatos(db)
{
    ui->setupUi(this);
    setWindowTitle("Sistema de Ingreso");
    connect(ui->btnIngresar, &QPushButton::clicked, this, &Login::slot_validar);
}

Login::~Login() {
    delete ui;
}

void Login::slot_validar() {
    QString user = ui->leUsuario->text();
    QString pass = ui->leClave->text();

    if (baseDatos->validarUsuario(user, pass)) {
        QMessageBox::information(this, "Éxito", "Bienvenido al sistema.");

        Pintura *ventanaPintura = new Pintura(baseDatos);
        ventanaPintura->show();

        this->close();
    } else {
        QMessageBox::critical(this, "Error", "Usuario o clave incorrectos.");
        ui->leClave->clear();
    }
}