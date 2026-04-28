#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>
#include <QString>

// CLASE BASE ABSTRACTA PARA LA INTERFAZ
class Pantalla : public QWidget {
    Q_OBJECT
public:
    explicit Pantalla(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~Pantalla() {}

    // El contrato polimórfico estricto (funciones virtuales puras = 0)
    virtual void inicializarUI() = 0;
    virtual void conectarEventos() = 0;
    virtual void cargarDatos() = 0;
    virtual void validarEstado() = 0;
    virtual void registrarEvento(const QString &mensaje) = 0;

signals:
    // Esta señal es vital para que las pantallas avisen cuando quieren cerrarse y abrir otra
    void solicitarCambio(int idPantalla);
};

#endif // PANTALLA_H