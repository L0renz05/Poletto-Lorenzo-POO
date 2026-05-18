#include "juego.h"
#include <QPainter>

Juego::Juego(QWidget *parent) : QWidget(parent), juegoTerminado(false) {
    setFixedSize(800, 300);
    setWindowTitle("T-Rex Extremo - Ejercicio 10");
    setFocusPolicy(Qt::StrongFocus);

    // NUEVO: Cargamos la imagen de Game Over (asegurate de tener el archivo gameover.png)
    imagenGameOver.load("/Users/lolo/Desktop/facultad/Materias/POO/Ejercicio10/gameover.png");

    dino = new TRex(this);
    velocidadJuego = 5;

    timerPrincipal = new QTimer(this);
    connect(timerPrincipal, SIGNAL(timeout()), this, SLOT(slot_buclePrincipal()));
    timerPrincipal->start(20);

    timerSpawnPajaros = new QTimer(this);
    connect(timerSpawnPajaros, SIGNAL(timeout()), this, SLOT(slot_spawnPajaro()));
    timerSpawnPajaros->start(3500);

    timerSpawnCactus = new QTimer(this);
    connect(timerSpawnCactus, SIGNAL(timeout()), this, SLOT(slot_spawnCactus()));
    timerSpawnCactus->start(2200);

    timerDificultad = new QTimer(this);
    connect(timerDificultad, SIGNAL(timeout()), this, SLOT(slot_aumentarDificultad()));
    timerDificultad->start(5000);

    QTimer::singleShot(12000, this, SLOT(slot_obstaculoSorpresa()));
}

void Juego::keyPressEvent(QKeyEvent *event) {
    // NUEVO: Si el juego terminó, escuchamos la tecla R o el Espacio para reiniciar
    if (juegoTerminado) {
        if (event->key() == Qt::Key_R || event->key() == Qt::Key_Space) {
            reiniciarJuego();
        }
        return;
    }

    // Si el juego sigue corriendo, controlamos al T-Rex
    switch (event->key()) {
    case Qt::Key_Space: dino->saltar(); break;
    case Qt::Key_Down: dino->agacharse(); break;
    case Qt::Key_Right: dino->adelantarse(); break;
    case Qt::Key_Left: dino->frenarse(); break;
    }
}

void Juego::slot_spawnPajaro() {
    if (juegoTerminado) return;
    Pajaro *nuevoPajaro = new Pajaro(velocidadJuego, this);
    nuevoPajaro->show();
    listaPajaros.append(nuevoPajaro);
}

void Juego::slot_spawnCactus() {
    if (juegoTerminado) return;
    Cactus *nuevoCactus = new Cactus(velocidadJuego, this);
    nuevoCactus->show();
    listaCactus.append(nuevoCactus);
}

void Juego::slot_obstaculoSorpresa() {
    if (juegoTerminado) return;
    Pajaro *pajaroKamikaze = new Pajaro(velocidadJuego * 2, this);
    pajaroKamikaze->show();
    listaPajaros.append(pajaroKamikaze);
}

void Juego::slot_aumentarDificultad() {
    if (!juegoTerminado) {
        velocidadJuego += 1;
    }
}

void Juego::slot_buclePrincipal() {
    if (juegoTerminado) return;

    QRect hitboxDino = dino->geometry().adjusted(15, 10, -10, -5);

    for (int i = 0; i < listaPajaros.size(); ++i) {
        Pajaro *pajaro = listaPajaros[i];
        if (pajaro->x() < -50) {
            listaPajaros.removeAt(i);
            pajaro->deleteLater();
            i--;
            continue;
        }
        QRect hitboxPajaro = pajaro->geometry().adjusted(5, 5, -5, -5);
        if (hitboxPajaro.intersects(hitboxDino)) {
            gameOver();
            return;
        }
    }

    for (int i = 0; i < listaCactus.size(); ++i) {
        Cactus *cactus = listaCactus[i];
        if (cactus->x() < -50) {
            listaCactus.removeAt(i);
            cactus->deleteLater();
            i--;
            continue;
        }
        QRect hitboxCactus = cactus->geometry().adjusted(4, 4, -4, -4);
        if (hitboxCactus.intersects(hitboxDino)) {
            gameOver();
            return;
        }
    }
}

void Juego::gameOver() {
    juegoTerminado = true;
    timerPrincipal->stop();
    timerSpawnPajaros->stop();
    timerSpawnCactus->stop();
    timerDificultad->stop();

    for (Pajaro *pajaro : listaPajaros) pajaro->frenarJuego();
    for (Cactus *cactus : listaCactus) cactus->frenarJuego();

    // NUEVO: En vez del QMessageBox, simplemente forzamos a que se vuelva a dibujar la pantalla
    update();
}

void Juego::reiniciarJuego() {
    for (Pajaro *pajaro : listaPajaros) {
        pajaro->close();
        pajaro->deleteLater();
    }
    listaPajaros.clear();

    for (Cactus *cactus : listaCactus) {
        cactus->close();
        cactus->deleteLater();
    }
    listaCactus.clear();

    dino->reiniciar();
    velocidadJuego = 5;

    juegoTerminado = false;
    timerPrincipal->start(20);
    timerSpawnPajaros->start(3500);
    timerSpawnCactus->start(2200);
    timerDificultad->start(5000);

    QTimer::singleShot(12000, this, SLOT(slot_obstaculoSorpresa()));

    // NUEVO: Limpiamos la pantalla del cartel de Game Over
    update();
}

void Juego::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawLine(0, 250, width(), 250);

    // NUEVO: Si el juego terminó, dibujamos la imagen en el centro
    if (juegoTerminado) {
        int anchoCartel = 300; // Ajustá este valor si tu imagen es muy grande
        int altoCartel = 100;  // Ajustá este valor si tu imagen es muy grande
        int posX = (width() - anchoCartel) / 2;
        int posY = (height() - altoCartel) / 2;

        painter.drawPixmap(posX, posY, anchoCartel, altoCartel, imagenGameOver);
    }
}