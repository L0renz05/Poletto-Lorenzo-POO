#include "admindb.h"

AdminDB::AdminDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool AdminDB::conectar(QString ruta) {
    db.setDatabaseName(ruta);
    if(db.open()) {
        qDebug() << "Conexión exitosa a la DB";
        return true;
    }
    qDebug() << "Error al conectar:" << db.lastError().text();
    return false;
}

bool AdminDB::validarUsuario(QString usuario, QString clave) {
    QSqlQuery query;
    query.prepare("SELECT id FROM usuarios WHERE usuario = :u AND clave = :c");
    query.bindValue(":u", usuario);
    query.bindValue(":c", clave);

    if (query.exec() && query.next()) {
        registrarEvento("Acceso exitoso: " + usuario);
        return true;
    }
    registrarEvento("Fallo de login: " + usuario);
    return false;
}

void AdminDB::registrarEvento(QString mensaje) {
    QSqlQuery query;
    query.prepare("INSERT INTO logs (evento) VALUES (:msg)");
    query.bindValue(":msg", mensaje);
    query.exec();
}

void AdminDB::guardarPunto(int x, int y, int r, int g, int b, int grosor, bool inicio) {
    QSqlQuery query;
    query.prepare("INSERT INTO coordenadas (x, y, r, g, b, grosor, inicio_trazo) "
                  "VALUES (:x, :y, :r, :g, :b, :gr, :ini)");
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":r", r);
    query.bindValue(":g", g);
    query.bindValue(":b", b);
    query.bindValue(":gr", grosor);
    query.bindValue(":ini", inicio ? 1 : 0);
    query.exec();
}