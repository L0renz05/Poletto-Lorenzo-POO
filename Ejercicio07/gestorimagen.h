#ifndef GESTORIMAGEN_H
#define GESTORIMAGEN_H

#include "gestordatos.h"
#include <QNetworkReply>

class GestorImagen : public GestorDatos {
    Q_OBJECT
public:
    explicit GestorImagen(QObject *parent = nullptr);
    void iniciarPeticion() override;

signals:
    // Señal que emite la ruta del archivo cuando ya está guardado en el disco
    void imagenLista(const QString &rutaLocal);

private slots:
    void procesarRespuesta(QNetworkReply *reply);
};

#endif // GESTORIMAGEN_H