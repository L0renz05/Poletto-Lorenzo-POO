#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Monitor : public QObject {
    Q_OBJECT
public:
    explicit Monitor(QObject *parent = nullptr);
    void pedirDatos(QString url);

signals:
    void datosListos(double cpu, double ram, double disk, QString status, QString uptime);
    void errorRed(QString mensaje);

private:
    QNetworkAccessManager *manager;
};

#endif