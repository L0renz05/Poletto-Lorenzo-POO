# 🚀 Ejercicio 09: Integración de Interfaz Gráfica y Base de Datos Local

**Autor:** Lorenzo Poletto  
**Universidad:** Universidad Blas Pascal - Ingeniería Informática  
**Materia:** Programación Orientada a Objetos (POO)  
**Tecnologías:** C++17, Qt Framework (Widgets, Core), Base de Datos Local

## 📌 Consigna
El objetivo de este ejercicio consiste en desarrollar una aplicación de escritorio que implemente una interfaz gráfica de usuario (GUI) interactiva capaz de conectarse y gestionar información a través de una base de datos local. El sistema debe contar con un módulo de autenticación de usuarios, diferenciación de roles (Administrador/Usuario estándar) y permitir la navegación fluida mediante atajos de teclado, aplicando los conceptos de la Programación Orientada a Objetos para separar la lógica de presentación de la capa de persistencia de datos.

## 🛠️ Qué es lo que hice
Para resolver este proyecto, diseñé una arquitectura modular manteniendo un bajo acoplamiento entre la vista (UI) y el backend de datos. La interfaz gráfica se comunica mediante eventos con el gestor de la base de datos alojada en el directorio `db_ejercicio09`. Además, implementé un manejo robusto de excepciones para evitar cierres inesperados durante las consultas y redefiní eventos nativos de Qt para agilizar la experiencia de uso.

**Principales implementaciones:**
- [x] **Gestión de Base de Datos:** Conexión, lectura y escritura de registros apuntando a los archivos locales del proyecto (`db_ejercicio09`).
- [x] **Sistema de Autenticación:** Pantalla de Login inicial con validación de credenciales y separación de roles operativos.
- [x] **Atajos de Teclado Personalizados:** Sobreescritura del método `keyPressEvent` para interceptar teclas y optimizar la navegación sin depender exclusivamente del mouse.
- [x] **Arquitectura Orientada a Objetos:** Estructuración del código en clases modulares aislando la lógica de la base de datos de la interfaz gráfica.

## ⚙️ Instructivo de Ejecución y Uso

### 1. Cómo correrlo
1. Clonar el repositorio y abrir el archivo `.pro` en Qt Creator.
2. **Importante:** Verificar que el directorio `db_ejercicio09` (con los archivos de la base de datos) se encuentre en la raíz del directorio de compilación/ejecución (generalmente en la carpeta `build-...`).
3. Compilar y ejecutar el proyecto desde el entorno.

### 2. Controles y Atajos de Teclado
El sistema cuenta con atajos configurados para agilizar la interacción en las pantallas principales:
* **`Enter`**: Confirma el inicio de sesión en la pantalla de Login y valida el ingreso de datos en los formularios.
* **`Esc`**: Cancela la operación actual, limpia los campos de texto o cierra ventanas secundarias.
* **`Tab` / `Flechas`**: Permite la navegación secuencial entre los distintos campos de entrada y botones de la interfaz.

### 3. Acceso de Administrador
Para acceder al sistema con todos los privilegios habilitados (visualización, edición y borrado de registros en la base de datos), se deben ingresar las siguientes credenciales en la pantalla de inicio:
* **Usuario:** `admin`
* **Contraseña:** `1234`