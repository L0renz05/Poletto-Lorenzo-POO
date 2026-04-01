#include "monitor.h"
#include <QJsonDocument>
#include <QJsonObject>

Monitor::Monitor(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void Monitor::pedirDatos(QString url) {
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            QJsonObject obj = doc.object();

            emit datosListos(obj["cpu"].toDouble(),
                             obj["ram"].toDouble(),
                             obj["disk"].toDouble(),
                             obj["status"].toString(),
                             obj["uptime"].toString());
        } else {
            emit errorRed("No se pudo conectar al VPS");
        }
        reply->deleteLater();
    });
}