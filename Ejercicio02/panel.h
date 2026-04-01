#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QTimer>
#include "monitor.h"

class Panel : public QWidget {
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);

private slots:
    void actualizar();
    void mostrarDatos(double cpu, double ram, double disk, QString status, QString uptime);
    void manejarError(QString msg);

private:
    Monitor *monitor;
    QTimer *timer;

    QLineEdit *txtUrl;
    QSpinBox *spinIntervalo;
    QPushButton *btnRefrescar;
    QLabel *lblStatus, *lblCpu, *lblRam, *lblDisk, *lblUltimoChequeo;
};

#endif