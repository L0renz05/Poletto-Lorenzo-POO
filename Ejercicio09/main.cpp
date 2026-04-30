#include <QApplication>
#include <QMessageBox>
#include "admindb.h"
#include "login.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    AdminDB db;
    // Ruta absoluta que me pasaste para tu Mac
    QString rutaDB = "/Users/lolo/Desktop/facultad/Materias/POO/Ejercicio09/db_ejercicio09/clase.db";

    if (!db.conectar(rutaDB)) {
        QMessageBox::critical(nullptr, "Error Fatal", "No se pudo conectar a la base de datos en:\n" + rutaDB);
        return -1;
    }

    Login ventanaLogin(&db);
    ventanaLogin.show();

    return a.exec();
}