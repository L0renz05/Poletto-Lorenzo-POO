#ifndef VALIDADORES_H
#define VALIDADORES_H

#include <QString>

// 1. CLASE BASE ABSTRACTA
class ValidadorSintaxis {
public:
    virtual ~ValidadorSintaxis() {}

    // Método virtual puro: Retorna true si está bien, false si hay error
    virtual bool validarLinea(const QString &linea, QString &mensajeError) = 0;
};


// 2. CLASE DERIVADA: C++
class ValidadorCpp : public ValidadorSintaxis {
public:
    bool validarLinea(const QString &linea, QString &mensajeError) override {
        QString limpia = linea.trimmed();

        // Ignoramos líneas vacías, comentarios o includes
        if (limpia.isEmpty() || limpia.startsWith("//") || limpia.startsWith("#")) return true;

        // Regla: Si no es llave de bloque, debe terminar con punto y coma
        if (!limpia.endsWith(";") && !limpia.endsWith("{") && !limpia.endsWith("}")) {
            mensajeError = "Error C++: Falta punto y coma (;) o llave al final.";
            return false;
        }
        return true;
    }
};


// 3. CLASE DERIVADA: Python
class ValidadorPython : public ValidadorSintaxis {
public:
    bool validarLinea(const QString &linea, QString &mensajeError) override {
        QString limpia = linea.trimmed();

        // Ignoramos vacías o comentarios
        if (limpia.isEmpty() || limpia.startsWith("#")) return true;

        // Regla: Bloques de control o funciones deben terminar con dos puntos (:)
        if ((limpia.startsWith("if ") || limpia.startsWith("for ") ||
             limpia.startsWith("while ") || limpia.startsWith("def "))
            && !limpia.endsWith(":")) {

            mensajeError = "Error Python: La declaración debe terminar con dos puntos (:).";
            return false;
        }
        return true;
    }
};


// 4. CLASE DERIVADA: Java
class ValidadorJava : public ValidadorSintaxis {
public:
    bool validarLinea(const QString &linea, QString &mensajeError) override {
        QString limpia = linea.trimmed();

        if (limpia.isEmpty() || limpia.startsWith("//") || limpia.startsWith("@")) return true;

        // Regla similar a C++, pero verificamos que no falten los ;
        if (!limpia.endsWith(";") && !limpia.endsWith("{") && !limpia.endsWith("}")) {
            mensajeError = "Error Java: Falta punto y coma (;) en la instrucción.";
            return false;
        }
        return true;
    }
};

#endif // VALIDADORES_H