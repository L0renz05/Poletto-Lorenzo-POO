#include "cactus.h"
#include <QPainter>

Cactus::Cactus(int vel, QWidget *parent) : QWidget(parent), velocidad(vel) {
    setGeometry(800, 200, 30, 50);

    imagenCactus.load("/Users/lolo/Desktop/facultad/Materias/POO/Ejercicio10/cactus.png");

    timerCactus = new QTimer(this);
    connect(timerCactus, SIGNAL(timeout()), this, SLOT(slot_mover()));
    timerCactus->start(30);
}

void Cactus::slot_mover() {
    move(x() - velocidad, y()); // Se mueve usando la variable global
}

void Cactus::frenarJuego() {
    timerCactus->stop();
}

void Cactus::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), imagenCactus);
}