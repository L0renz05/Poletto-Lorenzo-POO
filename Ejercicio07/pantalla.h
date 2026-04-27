#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>

// CLASE ABSTRACTA: Todas nuestras ventanas van a heredar de acá
class Pantalla : public QWidget {
    Q_OBJECT
public:
    explicit Pantalla(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~Pantalla() {}

    // Funciones virtuales puras (El contrato)
    virtual void inicializarUI() = 0;
    virtual void cargarTextos() = 0;
};

#endif // PANTALLA_H