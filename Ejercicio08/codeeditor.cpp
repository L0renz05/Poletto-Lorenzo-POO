#include "codeeditor.h"
#include <QKeyEvent>
#include <QTextBlock>
#include <QTextCursor>
#include <QDebug>

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent), validador(nullptr) {
    // Estilo hacker/profesional
    setStyleSheet("background-color: #1e1e1e; color: #d4d4d4; font-family: 'Courier New'; font-size: 14px; border: 1px solid #555;");
}

CodeEditor::~CodeEditor() {
    if (validador) {
        delete validador; // Cuidamos la memoria dinámica
    }
}

void CodeEditor::setValidador(ValidadorSintaxis *nuevoValidador) {
    if (validador) {
        delete validador; // Borramos el validador anterior (Ej: si pasamos de C++ a Python)
    }
    validador = nuevoValidador;
}

void CodeEditor::validarLineaActual() {
    if (!validador) return; // Si no hay lenguaje seleccionado, no hacemos nada

    QTextCursor cursor = this->textCursor();
    QString lineaActual = cursor.block().text();
    QString mensajeError;

    // MAGIA POLIMÓRFICA: Llamamos al validador sin saber cuál es
    if (!validador->validarLinea(lineaActual, mensajeError)) {
        resaltarLinea(QColor(150, 0, 0, 100)); // Rojo semitransparente
        emit validacionResult(mensajeError, true);
    } else {
        resaltarLinea(QColor(30, 30, 30, 0)); // Transparente (sin error)
        emit validacionResult("Sintaxis OK.", false);
    }
}

void CodeEditor::resaltarLinea(const QColor &color) {
    QList<QTextEdit::ExtraSelection> selecciones;
    QTextEdit::ExtraSelection seleccion;

    seleccion.format.setBackground(color);
    seleccion.format.setProperty(QTextFormat::FullWidthSelection, true); // Resalta toda la fila
    seleccion.cursor = textCursor();
    seleccion.cursor.clearSelection();

    selecciones.append(seleccion);
    setExtraSelections(selecciones);
}

// ========================================================
// REDEFINICIÓN DE EVENTOS (Requisito del profe)
// ========================================================

void CodeEditor::keyPressEvent(QKeyEvent *event) {
    // Si apreta ENTER, validamos la línea que está dejando antes de hacer el salto de línea
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        validarLineaActual();
    }

    // Atajo de teclado personalizado: Ctrl + S para simular guardado rápido
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S) {
        emit validacionResult("Código guardado en memoria temporal.", false);
    }

    // Es VITAL llamar al evento original de la clase padre para que la letra se escriba
    QPlainTextEdit::keyPressEvent(event);
}

void CodeEditor::mousePressEvent(QMouseEvent *event) {
    qDebug() << "Mouse clicado en el editor. Validando posición anterior...";
    // Validamos por si el usuario hizo clic en otra línea y abandonó la actual
    validarLineaActual();

    QPlainTextEdit::mousePressEvent(event);
}

void CodeEditor::focusInEvent(QFocusEvent *event) {
    qDebug() << "Editor GANÓ el foco (Focus In)";
    setStyleSheet("background-color: #1e1e1e; color: #d4d4d4; font-family: 'Courier New'; font-size: 14px; border: 2px solid #0a66c2;"); // Borde azul estilo LinkedIn
    QPlainTextEdit::focusInEvent(event);
}

void CodeEditor::focusOutEvent(QFocusEvent *event) {
    qDebug() << "Editor PERDIÓ el foco (Focus Out)";
    // Requisito del profe: Validar al abandonar
    validarLineaActual();
    setStyleSheet("background-color: #1e1e1e; color: #d4d4d4; font-family: 'Courier New'; font-size: 14px; border: 1px solid #555;"); // Borde gris normal
    QPlainTextEdit::focusOutEvent(event);
}