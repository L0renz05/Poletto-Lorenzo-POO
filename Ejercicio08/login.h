#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"

// Esta parte vincula el archivo visual login.ui con el código
namespace Ui {
class Login;
}

class Login : public Pantalla {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    // Implementación obligatoria del contrato
    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    void validarEstado() override;
    void registrarEvento(const QString &mensaje) override;

private slots:
    void intentarLogin();

private:
    Ui::Login *ui;
    int intentosFalla;
};

#endif // LOGIN_H