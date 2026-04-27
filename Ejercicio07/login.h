#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"
#include "gestorclima.h"
#include "gestorimagen.h"
#include <QTimer>

namespace Ui {
class Login;
}

class Login : public Pantalla {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void inicializarUI() override;
    void cargarTextos() override;

private slots:
    void intentarLogin();
    void desbloquearLogin();
    void actualizarLabels(const QString &clima, const QString &hora);

    // Este nombre debe coincidir EXACTAMENTE con el .cpp
    void abrirVentanaPrincipal(const QString &rutaImagen);

private:
    Ui::Login *ui;
    int intentosFalla;
    QTimer *timerBloqueo;

    GestorClima *apiClima;
    GestorImagen *apiImagen;

    void registrarLog(const QString &mensaje);
};

#endif // LOGIN_H