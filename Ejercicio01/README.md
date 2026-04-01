**Alumno:** Lorenzo Poletto  
**Materia:** Programación Orientada a Objetos (POO)  
---

## Descripción del Proyecto
Este es un gestor de trabajos prácticos desarrollado en **C++** utilizando el framework **Qt**. Permite organizar las materias de la facultad de forma dinámica.

### Funcionalidades Principales:
* **Login Seguro:** Validación de usuario personalizada.
* **Gestión Dinámica:** Permite agregar materias en tiempo real mediante una grilla (`QGridLayout`).
* **Control de Estados:** Cada materia posee un selector (`QComboBox`) para marcarla como *Pendiente*, *En curso* o *Entregado*.
* **Editor de Notas:** Espacio para anotaciones individuales por cada TP.
* **Persistencia Local:** Los apuntes se guardan en archivos `.txt` independientes para cada materia.

---

## Cómo compilar y ejecutar
1.  Abrir el archivo `Ejercicio1.pro` en **Qt Creator**.
2.  Configurar el kit de compilación (Desktop).
3.  Hacer clic derecho en el proyecto y seleccionar **"Run qmake"**.
4.  Presionar el botón **Play** (Build & Run).

---