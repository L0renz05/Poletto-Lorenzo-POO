# 📚 Ejercicio 01 - Gestor de Trabajos Prácticos

**Materia:** Programación Orientada a Objetos (POO)  
**Alumno:** Lorenzo Poletto  

---

## 🚀 Descripción del Proyecto
Aplicación de escritorio desarrollada en **C++** utilizando el framework **Qt**. Está diseñada para gestionar, organizar y hacer un seguimiento dinámico de los trabajos prácticos y entregas de la facultad.

---

## 📂 Estructura de Archivos
El código está modularizado para respetar los principios de la Programación Orientada a Objetos, separando las distintas responsabilidades de la aplicación:

* 📄 **`Ejercicio1.pro`**: Archivo principal de configuración del proyecto de Qt. Aquí se definen los módulos utilizados (`core`, `gui`, `widgets`) y se enlazan las cabeceras y fuentes.
* 📄 **`main.cpp`**: Punto de entrada de la aplicación. Se encarga de instanciar `QApplication` y lanzar la primera ventana (el Login).
* 📄 **`login.h` / `login.cpp`**: Manejan la interfaz y la lógica de validación de seguridad. Solo permiten el acceso al panel si las credenciales son correctas.
* 📄 **`panel.h` / `panel.cpp`**: Representan el "corazón" de la aplicación. Aquí se encuentra toda la lógica de la grilla dinámica (`QGridLayout`), el manejo de eventos de los botones, los menús desplegables (`QComboBox`) y el sistema que lee y guarda los archivos `.txt` en el disco.

---

## ✨ Funcionalidades Principales

* 🔐 **Login Seguro:** Validación de credenciales de usuario para restringir el acceso al panel principal.
* ➕ **Gestión Dinámica de UI:** Creación de nuevas materias en tiempo real. La interfaz se adapta dinámicamente utilizando un sistema de grillas (`QGridLayout`).
* 🚦 **Control de Estados:** Seguimiento del progreso de cada trabajo práctico mediante menús desplegables (`QComboBox`) con los estados: *Pendiente*, *En curso* y *Entregado*.
* 📝 **Editor de Notas:** Área de texto dedicada (`QTextEdit`) para registrar observaciones, links o requerimientos específicos de cada TP.
* 💾 **Persistencia Local de Datos:** Guardado automático de los apuntes utilizando `QFile` y `QTextStream`. Cada materia genera su propio archivo `.txt` independiente, garantizando que la información persista entre distintas sesiones de la aplicación.

---

## 🛠️ Tecnologías Aplicadas
* **Lenguaje:** C++
* **Framework:** Qt (Módulos: Core, GUI, Widgets)
* **Almacenamiento:** Archivos de texto plano (.txt)

---

## ⚙️ Cómo compilar y ejecutar (macOS / Windows / Linux)

1. Abrir el archivo `Ejercicio1.pro` desde **Qt Creator**.
2. Configurar el kit de compilación correspondiente a tu sistema (Ej: *Desktop Qt... clang* para Mac).
3. En el menú superior, ir a **Build** (Compilar) y seleccionar **Clean All**.
4. Ir nuevamente a **Build** y seleccionar **Run qmake**.
5. Presionar el botón ▶️ **Play** (o `Cmd + R` en Mac) para compilar y lanzar la aplicación.