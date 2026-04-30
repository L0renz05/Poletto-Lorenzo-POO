#include "pintura.h"

Pintura::Pintura(AdminDB *db, QWidget *parent)
    : QWidget(parent), baseDatos(db)
{
    setFixedSize(800, 600);
    setWindowTitle("Lienzo de Dibujo");

    lienzo = QPixmap(size());
    lienzo.fill(Qt::white);

    colorActual = Qt::black;
    grosorPincel = 3;

    guardarEstadoUndo();
}

void Pintura::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, lienzo);
}

void Pintura::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        guardarEstadoUndo();
        ultimoPunto = event->pos();
        baseDatos->guardarPunto(ultimoPunto.x(), ultimoPunto.y(),
                                colorActual.red(), colorActual.green(), colorActual.blue(),
                                grosorPincel, true);
    }
}

void Pintura::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPainter painter(&lienzo);
        QPen pen(colorActual, grosorPincel, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);

        painter.drawLine(ultimoPunto, event->pos());
        ultimoPunto = event->pos();

        update();

        baseDatos->guardarPunto(ultimoPunto.x(), ultimoPunto.y(),
                                colorActual.red(), colorActual.green(), colorActual.blue(),
                                grosorPincel, false);
    }
}

void Pintura::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) grosorPincel++;
    else if (grosorPincel > 1) grosorPincel--;
}

void Pintura::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_R) colorActual = Qt::red;
    else if (event->key() == Qt::Key_G) colorActual = Qt::green;
    else if (event->key() == Qt::Key_B) colorActual = Qt::blue;
    else if (event->key() == Qt::Key_Escape) {
        guardarEstadoUndo();
        lienzo.fill(Qt::white);
        update();
    }
    else if (event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_Z) {
        if (!historialUndo.isEmpty()) {
            lienzo = historialUndo.takeLast();
            update();
        }
    }
}

void Pintura::guardarEstadoUndo() {
    if (historialUndo.size() >= 10) historialUndo.removeFirst();
    historialUndo.append(lienzo);
}