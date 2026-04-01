#include "panel.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QDateTime>

Panel::Panel(QWidget *parent) : QWidget(parent) {
    // --- 1. CONFIGURACIÓN VISUAL DE LA VENTANA ---
    this->setWindowTitle("Panel de Monitoreo VPS");
    this->setStyleSheet("background-color: #1e1e1e; color: #ffffff; font-family: 'Segoe UI', Arial;");
    this->resize(500, 580);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(25);
    layoutPrincipal->setContentsMargins(25, 25, 25, 25);

    // Estilo especial para arreglar el bug visual de los títulos en Mac
    QString estiloCaja = "QGroupBox { border: 1px solid #555; border-radius: 6px; margin-top: 25px; font-weight: bold; } "
                         "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; left: 10px; padding: 0 5px; color: #4fc3f7; }";

    // --- 2. SECCIÓN SUPERIOR: CONTROLES ---
    QGroupBox *grupoConfig = new QGroupBox("⚙️ Configuración del Server");
    grupoConfig->setStyleSheet(estiloCaja);

    QVBoxLayout *layoutConfig = new QVBoxLayout(grupoConfig);
    layoutConfig->setSpacing(15);

    txtUrl = new QLineEdit("http://161.97.92.143:5050/health");
    txtUrl->setStyleSheet("background: #2d2d2d; padding: 8px; border: 1px solid #555; color: #ffffff;");

    spinIntervalo = new QSpinBox();
    spinIntervalo->setRange(2, 120);
    spinIntervalo->setValue(5);
    spinIntervalo->setSuffix(" segundos");
    spinIntervalo->setStyleSheet("background: #2d2d2d; padding: 6px; color: #ffffff; border: 1px solid #555;");

    layoutConfig->addWidget(new QLabel("URL del Endpoint:"));
    layoutConfig->addWidget(txtUrl);
    layoutConfig->addWidget(new QLabel("Frecuencia de actualización:"));
    layoutConfig->addWidget(spinIntervalo);
    layoutPrincipal->addWidget(grupoConfig);

    // --- 3. SECCIÓN CENTRAL: MÉTRICAS EN VIVO ---
    QGroupBox *grupoMetricas = new QGroupBox("📊 Estado del Sistema");
    grupoMetricas->setStyleSheet(estiloCaja);

    QVBoxLayout *layoutMetricas = new QVBoxLayout(grupoMetricas);
    layoutMetricas->setSpacing(18);

    lblStatus = new QLabel("ESTADO: INICIANDO...");
    lblStatus->setAlignment(Qt::AlignCenter);
    lblStatus->setStyleSheet("font-size: 16px; font-weight: bold; background: #333; padding: 20px 15px; border-radius: 5px;");

    lblCpu = new QLabel("CPU: -- %");
    lblRam = new QLabel("Memoria RAM: -- %");
    lblDisk = new QLabel("Uso de Disco: -- %");

    lblUltimoChequeo = new QLabel("Último chequeo: Esperando datos...");
    lblUltimoChequeo->setStyleSheet("color: #888; font-size: 11px; margin-top: 10px;");

    layoutMetricas->addWidget(lblStatus);
    layoutMetricas->addWidget(lblCpu);
    layoutMetricas->addWidget(lblRam);
    layoutMetricas->addWidget(lblDisk);
    layoutMetricas->addWidget(lblUltimoChequeo);
    layoutPrincipal->addWidget(grupoMetricas);

    // --- 4. BOTÓN DE ACCIÓN MANUAL ---
    btnRefrescar = new QPushButton("🔄 REFRESCAR AHORA");
    btnRefrescar->setStyleSheet("QPushButton { background-color: #0078d4; color: white; font-weight: bold; padding: 15px; border-radius: 4px; }"
                                "QPushButton:hover { background-color: #106ebe; }");
    layoutPrincipal->addWidget(btnRefrescar);

    // --- 5. LÓGICA DE FUNCIONAMIENTO ---
    monitor = new Monitor(this);
    timer = new QTimer(this);

    connect(btnRefrescar, &QPushButton::clicked, this, &Panel::actualizar);
    connect(monitor, &Monitor::datosListos, this, &Panel::mostrarDatos);
    connect(monitor, &Monitor::errorRed, this, &Panel::manejarError);
    connect(timer, &QTimer::timeout, this, &Panel::actualizar);

    timer->start(spinIntervalo->value() * 1000);
    actualizar();
}

void Panel::actualizar() {
    lblStatus->setText("Consultando al VPS...");
    lblStatus->setStyleSheet("font-size: 16px; font-weight: bold; background: #b8860b; color: white; padding: 20px 15px; border-radius: 5px;");

    monitor->pedirDatos(txtUrl->text());
    timer->setInterval(spinIntervalo->value() * 1000);
}

void Panel::mostrarDatos(double cpu, double ram, double disk, QString status, QString uptime) {
    lblStatus->setText("ESTADO: " + status + " (" + uptime + ")");
    lblStatus->setStyleSheet("font-size: 16px; font-weight: bold; background: #2e7d32; color: white; padding: 20px 15px; border-radius: 5px;");

    lblCpu->setText(QString("CPU: %1 %").arg(cpu));
    lblRam->setText(QString("Memoria RAM: %1 %").arg(ram));
    lblDisk->setText(QString("Uso de Disco: %1 %").arg(disk));

    QString hora = QDateTime::currentDateTime().toString("hh:mm:ss");
    lblUltimoChequeo->setText("Último chequeo exitoso: " + hora);
}

void Panel::manejarError(QString msg) {
    lblStatus->setText("ERROR: " + msg);
    lblStatus->setStyleSheet("font-size: 16px; font-weight: bold; background: #c62828; color: white; padding: 20px 15px; border-radius: 5px;");
}