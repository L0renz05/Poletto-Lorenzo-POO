#include "pajaro.h"
#include <QPainter>
#include <cstdlib>

Pajaro::Pajaro(int vel, QWidget *parent) : QWidget(parent), velocidad(vel) {
    int alturaAleatoria = rand() % 60 + 100;
    setGeometry(800, alturaAleatoria, 40, 30);

    imagenPajaro.load("/Users/lolo/Desktop/facultad/Materias/POO/Ejercicio10/pajaro.png");

    timerPajaro = new QTimer(this);
    connect(timerPajaro, SIGNAL(timeout()), this, SLOT(slot_mover()));
    timerPajaro->start(30);
}

void Pajaro::slot_mover() {
    move(x() - velocidad, y()); // Se mueve usando la variable global
}

void Pajaro::frenarJuego() {
    timerPajaro->stop();
}

void Pajaro::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), imagenPajaro);
}