#include "login.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>

Login::Login(QWidget *parent) : QWidget(parent) {

    txtUser = new QLineEdit(this);
    txtPass = new QLineEdit(this);
    txtPass->setEchoMode(QLineEdit::Password);
    btnEntrar = new QPushButton("Entrar", this);

    QFormLayout *form = new QFormLayout();
    form->addRow("Usuario:", txtUser);
    form->addRow("Clave:", txtPass);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(form);
    mainLayout->addWidget(btnEntrar);

    this->setLayout(mainLayout);

    connect(btnEntrar, &QPushButton::clicked, this, &Login::slot_validar);
}

void Login::slot_validar() {
    if(txtUser->text() == "admin" && txtPass->text() == "1234") {
    QMessageBox::information(this, "OK", "Exito");
    } else {
        QMessageBox::warning(this, "OK", "Fallo");
    }
}