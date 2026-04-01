#ifndef TABLERO_H
#define TABLERO_H

#include <QWidget>
#include <QGridLayout>

namespace Ui {
class Tablero;
}

class Tablero : public QWidget
{
    Q_OBJECT

public:
    explicit Tablero(QWidget *parent = nullptr);
    ~Tablero();

private slots:
    void slot_editar_tp();   // Para cuando tocas "Editar" en la lista
    void slot_guardar_nota(); // Para el botón de abajo de todo

private:
    Ui::Tablero *ui;
    QGridLayout *grilla;    // El organizador de tus TPs
};

#endif // TABLERO_H