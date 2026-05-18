#ifndef PAJARO_H
#define PAJARO_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QPaintEvent>

class Pajaro : public QWidget {
    Q_OBJECT
public:
    explicit Pajaro(int vel, QWidget *parent = nullptr); // Ahora pide velocidad
    void frenarJuego();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_mover();

private:
    QTimer *timerPajaro;
    QPixmap imagenPajaro;
    int velocidad;
};

#endif // PAJARO_H