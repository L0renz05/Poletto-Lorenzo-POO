#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include "validadores.h"

// Heredamos de QPlainTextEdit para crear nuestro propio editor superpoderoso
class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit CodeEditor(QWidget *parent = nullptr);
    ~CodeEditor();

    // Método para cambiar el validador cuando el usuario cambia el lenguaje en el ComboBox
    void setValidador(ValidadorSintaxis *nuevoValidador);

signals:
    // Le avisa a la ventana principal si hay error para mostrarlo en la UI
    void validacionResult(const QString &mensaje, bool esError);

protected:
    // LOS 4 EVENTOS OBLIGATORIOS DEL PROFE
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    ValidadorSintaxis *validador; // Puntero polimórfico al validador actual

    void validarLineaActual();
    void resaltarLinea(const QColor &color);
};

#endif // CODEEDITOR_H