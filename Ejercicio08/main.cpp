#include <QApplication>
#include "login.h"
#include "editorprincipal.h"
#include "modobloqueado.h"

// Nuestro puntero abstracto y polimórfico
Pantalla *pantallaActiva = nullptr;

// Función global que actúa como Gestor de Rutas
void cambiarPantalla(int id) {
    // 1. Limpiamos la memoria de la pantalla anterior
    if (pantallaActiva) {
        pantallaActiva->close();
        pantallaActiva->deleteLater();
    }

    // 2. Instanciamos la clase derivada correcta según el ID solicitado
    if (id == 0) {
        pantallaActiva = new Login();
    } else if (id == 1) {
        pantallaActiva = new EditorPrincipal();
    } else if (id == 2) {
        pantallaActiva = new ModoBloqueado();
    }

    // 3. Conectamos la señal de la nueva pantalla a esta misma función
    QObject::connect(pantallaActiva, &Pantalla::solicitarCambio, &cambiarPantalla);

    // 4. Mostramos la pantalla. Requisito: El Editor va en FullScreen.
    if (id == 1) {
        pantallaActiva->showFullScreen();
    } else {
        pantallaActiva->show();
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Arrancamos el sistema pidiendo la pantalla 0 (Login)
    cambiarPantalla(0);

    return a.exec();
}