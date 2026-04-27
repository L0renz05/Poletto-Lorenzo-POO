#include "gestorimagen.h"
#include <QFile>
#include <QCoreApplication>
#include <QNetworkRequest>

GestorImagen::GestorImagen(QObject *parent) : GestorDatos(parent) {
    connect(manager, &QNetworkAccessManager::finished, this, &GestorImagen::procesarRespuesta);
}

void GestorImagen::iniciarPeticion() {
    QString rutaCache = QCoreApplication::applicationDirPath() + "/fondo_cache.jpg";

    // 1. REVISAR LA CACHÉ LOCAL
    if (QFile::exists(rutaCache)) {
        // Si ya existe, nos ahorramos la descarga
        emit imagenLista(rutaCache);
        return;
    }

    // 2. DESCARGAR DE INTERNET (Usamos una API pública de imágenes aleatorias en Full HD)
    QNetworkRequest request(QUrl("https://picsum.photos/1920/1080"));
    manager->get(request);
}

void GestorImagen::procesarRespuesta(QNetworkReply *reply) {
    QString rutaCache = QCoreApplication::applicationDirPath() + "/fondo_cache.jpg";

    if (reply->error() == QNetworkReply::NoError) {
        QFile file(rutaCache);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
        }
    }

    reply->deleteLater();

    // Haya funcionado o haya fallado (offline), avisamos que termine el bloqueo
    emit imagenLista(rutaCache);
}