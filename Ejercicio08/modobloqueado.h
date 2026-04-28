#ifndef MODOBLOQUEADO_H
#define MODOBLOQUEADO_H

#include "pantalla.h"
#include <QLabel>
#include <QTimer>

class ModoBloqueado : public Pantalla {
    Q_OBJECT
public:
    explicit ModoBloqueado(QWidget *parent = nullptr);
    ~ModoBloqueado();

    // Las 5 obligatorias
    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    void validarEstado() override;
    void registrarEvento(const QString &mensaje) override;

private slots:
    void actualizarReloj();

private:
    QLabel *lblMensaje;
    QLabel *lblTiempo;
    QTimer *timerSegundos;
    int segundosRestantes;
};

#endif // MODOBLOQUEADO_H