#ifndef TREX_H
#define TREX_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QTimer>

class TRex : public QWidget {
    Q_OBJECT
public:
    explicit TRex(QWidget *parent = nullptr);
    void saltar();
    void agacharse();
    void adelantarse();
    void frenarse();
    void reiniciar();

private slots:
    void aplicarGravedad();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int posicionBaseY;
    QPixmap imagenDino;

    int velocidadY;
    QTimer *timerFisicas;
};

#endif // TREX_H