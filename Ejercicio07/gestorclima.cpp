#include "gestorclima.h"
#include <QSettings>
#include <QCoreApplication>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

GestorClima::GestorClima(QObject *parent) : GestorDatos(parent) {
    // Enganchamos el manager de red con nuestro slot
    connect(manager, &QNetworkAccessManager::finished, this, &GestorClima::procesarRespuesta);
}

void GestorClima::iniciarPeticion() {
    // 1. LEER CONFIGURACIÓN (config.ini)
    QString rutaConfig = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(rutaConfig, QSettings::IniFormat);

    // Si no encuentra el archivo o la clave, pone valores por defecto
    QString apiKey = settings.value("API/key", "TU_API_KEY_ACA").toString();
    QString ciudad = settings.value("Ubicacion/ciudad", "Cordoba").toString();

    // 2. ARMAR LA URL (Usamos la API libre de OpenWeatherMap)
    QString urlString = "https://api.openweathermap.org/data/2.5/weather?q=" + ciudad + "&appid=" + apiKey + "&units=metric&lang=es";

    // 3. HACER LA PETICIÓN
    QNetworkRequest request;
    request.setUrl(QUrl(urlString));
    manager->get(request);
}

void GestorClima::procesarRespuesta(QNetworkReply *reply) {
    QString horaActual = QDateTime::currentDateTime().toString("HH:mm");
    QString textoClima;

    // 4. VERIFICAR INTERNET Y ERRORES (EL MODO OFFLINE)
    if (reply->error() == QNetworkReply::NoError) {
        // Hay internet y el servidor respondió bien
        QByteArray respuesta = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(respuesta);
        QJsonObject json = doc.object();

        // Parsear el JSON
        double temp = json["main"].toObject()["temp"].toDouble();
        QString desc = json["weather"].toArray()[0].toObject()["description"].toString();

        // Primera letra en mayúscula para que quede lindo
        if(!desc.isEmpty()) desc[0] = desc[0].toUpper();

        textoClima = QString("%1°C, %2").arg(qRound(temp)).arg(desc);
    } else {
        // MODO OFFLINE / Falló la red o la API Key está mal
        textoClima = "22°C, Soleado (Modo Offline)";
    }

    reply->deleteLater(); // Limpiamos la memoria

    // 5. AVISAR A LA INTERFAZ
    emit datosClimaListos("Clima: " + textoClima, "Hora local: " + horaActual);
}