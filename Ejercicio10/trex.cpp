#include "trex.h"
#include <QPainter>

TRex::TRex(QWidget *parent) : QWidget(parent) {
    posicionBaseY = 200;
    setGeometry(50, posicionBaseY, 50, 50);

    imagenDino.load("/Users/lolo/Desktop/facultad/Materias/POO/Ejercicio10/dino.png");

    velocidadY = 0;
    timerFisicas = new QTimer(this);
    connect(timerFisicas, SIGNAL(timeout()), this, SLOT(aplicarGravedad()));
    timerFisicas->start(20);
}

void TRex::saltar() {
    if (y() == posicionBaseY) {
        velocidadY = -26;
    }
}

void TRex::aplicarGravedad() {
    if (y() < posicionBaseY || velocidadY < 0) {
        velocidadY += 2;
        int nuevaY = y() + velocidadY;

        if (nuevaY > posicionBaseY) {
            nuevaY = posicionBaseY;
            velocidadY = 0;
        }

        setGeometry(x(), nuevaY, width(), height());
    }
}

void TRex::reiniciar() {
    velocidadY = 0;
    setGeometry(50, posicionBaseY, 50, 50);
    update();
}

void TRex::agacharse() {
    if (y() == posicionBaseY) {
        setGeometry(x(), posicionBaseY + 20, 50, 30);
    }
}

void TRex::adelantarse() { move(x() + 10, y()); }
void TRex::frenarse() { if (x() > 0) move(x() - 10, y()); }

void TRex::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), imagenDino);
}