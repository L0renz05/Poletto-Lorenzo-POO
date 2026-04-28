#ifndef EDITORPRINCIPAL_H
#define EDITORPRINCIPAL_H

#include "pantalla.h"
#include "codeeditor.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

// HEREDAMOS DEL CONTRATO PANTALLA
class EditorPrincipal : public Pantalla {
    Q_OBJECT
public:
    explicit EditorPrincipal(QWidget *parent = nullptr);
    ~EditorPrincipal();

    // Cumplimos los 5 métodos virtuales puros obligatorios
    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    void validarEstado() override;
    void registrarEvento(const QString &mensaje) override;

protected:
    // REDEFINICIÓN DE EVENTOS DE VENTANA (Requisito del profe)
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void cambiarLenguaje(const QString &lenguaje);
    void mostrarErrorSintaxis(const QString &mensaje, bool esError);
    void exportarCodigo();

private:
    CodeEditor *editor;
    QComboBox *cmbLenguaje;
    QLabel *lblEstado;
    QPushButton *btnExportar;
    QString rutaExportacion;

    // Método auxiliar para no hacer un solo método inicializarUI() gigante
    QWidget* crearPanelCV();
};

#endif // EDITORPRINCIPAL_H