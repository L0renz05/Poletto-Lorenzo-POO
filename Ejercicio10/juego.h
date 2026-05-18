#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QPaintEvent>
#include <QPixmap> // NUEVO: Para poder usar imágenes en el Manager
#include "trex.h"
#include "pajaro.h"
#include "cactus.h"

class Juego : public QWidget {
    Q_OBJECT
public:
    explicit Juego(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_buclePrincipal();
    void slot_spawnPajaro();
    void slot_spawnCactus();
    void slot_aumentarDificultad();
    void slot_obstaculoSorpresa();

private:
    TRex *dino;

    QTimer *timerPrincipal;
    QTimer *timerSpawnPajaros;
    QTimer *timerSpawnCactus;
    QTimer *timerDificultad;

    QList<Pajaro*> listaPajaros;
    QList<Cactus*> listaCactus;

    int velocidadJuego;
    bool juegoTerminado;
    QPixmap imagenGameOver; // NUEVO: La imagen del cartel final

    void gameOver();
    void reiniciarJuego();
};

#endif // JUEGO_H