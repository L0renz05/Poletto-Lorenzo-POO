#ifndef PINTURA_H
#define PINTURA_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QList>
#include "admindb.h"

class Pintura : public QWidget {
    Q_OBJECT
public:
    explicit Pintura(AdminDB *db, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void guardarEstadoUndo();

    AdminDB *baseDatos;
    QPixmap lienzo;
    QPoint ultimoPunto;
    QColor colorActual;
    int grosorPincel;

    QList<QPixmap> historialUndo;
};

#endif // PINTURA_H#endif // PINTURA_H