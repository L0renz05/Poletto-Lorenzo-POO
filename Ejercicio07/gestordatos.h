#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <QObject>
#include <QNetworkAccessManager>

// CLASE BASE ABSTRACTA PARA MANEJO DE DATOS
class GestorDatos : public QObject {
    Q_OBJECT
public:
    explicit GestorDatos(QObject *parent = nullptr) : QObject(parent) {
        manager = new QNetworkAccessManager(this);
    }
    virtual ~GestorDatos() {}

    // El contrato: toda clase de datos debe saber cómo arrancar su trabajo
    virtual void iniciarPeticion() = 0;

protected:
    // Puntero protegido para que las clases hijas lo puedan usar
    QNetworkAccessManager *manager;
};

#endif // GESTORDATOS_H