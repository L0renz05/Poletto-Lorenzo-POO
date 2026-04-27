#include "ventanaprincipal.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

VentanaPrincipal::VentanaPrincipal(const QString &rutaFondo, QWidget *parent)
    : Pantalla(parent), rutaImagen(rutaFondo)
{
    // Aseguramos que la memoria se limpie cuando se cierre la ventana
    setAttribute(Qt::WA_DeleteOnClose);

    inicializarUI();
    cargarTextos();
}

VentanaPrincipal::~VentanaPrincipal() {}

void VentanaPrincipal::inicializarUI() {
    // 1. Layout maestro centrado
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    // 2. Contenedor del CV con estilo transparente oscuro (Estilo profesional)
    QWidget *cvContainer = new QWidget(this);
    cvContainer->setFixedSize(600, 350);
    cvContainer->setStyleSheet("QWidget { background-color: rgba(30, 30, 30, 220); border-radius: 15px; color: white; }");

    QVBoxLayout *cvLayout = new QVBoxLayout(cvContainer);
    cvLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    cvLayout->addSpacing(40);

    // 3. Etiquetas de datos
    QLabel *lblNombre = new QLabel("Lorenzo Poletto", cvContainer);
    lblNombre->setStyleSheet("font-size: 32px; font-weight: bold; background: transparent;");
    lblNombre->setAlignment(Qt::AlignCenter);

    QLabel *lblTitulo = new QLabel("Desarrollador de Software C++ / Qt", cvContainer);
    lblTitulo->setStyleSheet("font-size: 18px; color: #0a66c2; font-weight: bold; background: transparent;");
    lblTitulo->setAlignment(Qt::AlignCenter);

    QLabel *lblPerfil = new QLabel(
        "Estudiante enfocado en el desarrollo de aplicaciones robustas\n"
        "utilizando Arquitectura Orientada a Objetos.\n\n"
        "⚙️ Framework Qt (Widgets, Networking)\n"
        "🧠 C++ Moderno (Clases Abstractas, Memoria Dinámica)\n"
        "🌐 Sistemas Cliente-Servidor y APIs", cvContainer);
    lblPerfil->setStyleSheet("font-size: 15px; background: transparent; margin-top: 20px;");
    lblPerfil->setAlignment(Qt::AlignCenter);

    cvLayout->addWidget(lblNombre);
    cvLayout->addWidget(lblTitulo);
    cvLayout->addWidget(lblPerfil);

    mainLayout->addWidget(cvContainer);
}

void VentanaPrincipal::cargarTextos() {
    setWindowTitle("Currículum Vitae - Lorenzo Poletto");
}

// 4. MAGIA: Dibujar el fondo sin deformar
void VentanaPrincipal::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(rutaImagen);

    if (!pixmap.isNull()) {
        // Ajustamos la imagen manteniendo relación de aspecto y cortando los excesos
        QPixmap fondoEscalado = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        // Centramos el recorte
        int x = (this->width() - fondoEscalado.width()) / 2;
        int y = (this->height() - fondoEscalado.height()) / 2;

        painter.drawPixmap(x, y, fondoEscalado);
    } else {
        // Color oscuro por si el usuario está offline y no tiene caché
        painter.fillRect(this->rect(), QColor("#1e1e1e"));
    }
}