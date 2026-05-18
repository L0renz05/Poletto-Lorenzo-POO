#ifndef CACTUS_H
#define CACTUS_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QPaintEvent>

class Cactus : public QWidget {
    Q_OBJECT
public:
    explicit Cactus(int vel, QWidget *parent = nullptr); // Ahora pide velocidad
    void frenarJuego();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_mover();

private:
    QTimer *timerCactus;
    QPixmap imagenCactus;
    int velocidad;
};

#endif // CACTUS_H#endif // CACTUS_H