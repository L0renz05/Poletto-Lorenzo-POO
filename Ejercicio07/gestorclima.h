#ifndef GESTORCLIMA_H
#define GESTORCLIMA_H

#include "gestordatos.h"
#include <QNetworkReply>

// CLASE DERIVADA: Se encarga exclusivamente del Clima
class GestorClima : public GestorDatos {
    Q_OBJECT
public:
    explicit GestorClima(QObject *parent = nullptr);
    void iniciarPeticion() override; // Cumplimos el contrato

signals:
    // Señal que le avisa a la interfaz que ya tenemos los datos
    void datosClimaListos(const QString &clima, const QString &hora);

private slots:
    void procesarRespuesta(QNetworkReply *reply);
};

#endif // GESTORCLIMA_H