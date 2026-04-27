#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include "pantalla.h"
#include <QString>

// Nuestra segunda pantalla que hereda el contrato abstracto
class VentanaPrincipal : public Pantalla {
    Q_OBJECT
public:
    explicit VentanaPrincipal(const QString &rutaFondo, QWidget *parent = nullptr);
    ~VentanaPrincipal();

    void inicializarUI() override;
    void cargarTextos() override;

protected:
    // Evento nativo de Qt que usamos para pintar el fondo de la pantalla completa
    void paintEvent(QPaintEvent *event) override;

private:
    QString rutaImagen;
};

#endif // VENTANAPRINCIPAL_H