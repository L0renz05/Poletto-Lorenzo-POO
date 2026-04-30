#ifndef ADMINDB_H
#define ADMINDB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QDebug>

class AdminDB : public QObject {
    Q_OBJECT
public:
    AdminDB();
    bool conectar(QString ruta);
    bool validarUsuario(QString usuario, QString clave);
    void registrarEvento(QString mensaje);
    void guardarPunto(int x, int y, int r, int g, int b, int grosor, bool inicio);

private:
    QSqlDatabase db;
};

#endif // ADMINDB_H