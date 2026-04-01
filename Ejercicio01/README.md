# 🖥️ Ejercicio 02 - Panel de Monitoreo VPS

**Materia:** Programación Orientada a Objetos (POO)  
**Alumno:** Lorenzo Poletto  

---

## 🚀 Descripción del Proyecto
Este proyecto consiste en una aplicación de escritorio desarrollada en **C++ con Qt Framework** que funciona como un Dashboard de monitoreo para un servidor privado virtual (VPS). 

La aplicación se conecta de forma asíncrona a un **endpoint REST** alojado en el VPS, consume datos en formato **JSON** y los visualiza en tiempo real en una interfaz profesional estilo *Dark Mode*.

---

## 📂 Estructura de Archivos
El código aplica el principio de responsabilidad única, separando estrictamente la interfaz gráfica de la lógica de red:

* 📄 **`Ejercicio02.pro`**: Archivo de configuración principal de Qt. Habilita los módulos necesarios, destacando `network` para las peticiones HTTP y `widgets` para la interfaz.
* 📄 **`main.cpp`**: Punto de entrada del programa. Instancia la ventana principal (`Panel`) y arranca el ciclo de ejecución de la aplicación.
* 📄 **`monitor.h` / `monitor.cpp` (Capa de Red):** Clase encargada exclusivamente de la comunicación con el servidor. Utiliza `QNetworkAccessManager` para hacer la petición `GET`, parsea la respuesta con `QJsonDocument` y emite una señal (`datosListos`) con la información procesada.
* 📄 **`panel.h` / `panel.cpp` (Capa de Interfaz):** Clase visual que hereda de `QWidget`. Construye el dashboard mediante código puro (Layouts, sin archivos `.ui`), maneja un `QTimer` para el refresco automático y actualiza los indicadores cuando el `Monitor` emite nuevos datos.
* 🐍 **`server_lolo.py` (En el VPS):** Script en Python (utilizando Flask y la librería `psutil`) alojado en el servidor remoto. Extrae las métricas reales del sistema operativo y las expone en formato JSON en el puerto `5050`.

---

## ✨ Funcionalidades Principales y Métricas

* 🔄 **Auto-Refresco Dinámico:** Intervalo de actualización configurable por el usuario mediante un `QSpinBox`.
* 📡 **Peticiones Asíncronas:** La interfaz gráfica no se congela mientras espera la respuesta del VPS gracias a la arquitectura de Señales y Slots de Qt.
* 📊 **Lectura de Datos en Vivo:**
  * **Estado General:** Indicador visual de conexión (OK / Error de Red).
  * **CPU & RAM:** Porcentaje de uso de los recursos del servidor.
  * **Disco:** Espacio físico consumido.
  * **Uptime & Registro:** Registro de la hora exacta del último chequeo exitoso.

---

## 🛠️ Tecnologías Aplicadas
* **Frontend (Cliente):** C++, Qt Framework (Módulos: Core, GUI, Widgets, Network)
* **Backend (Servidor):** Python, Flask, psutil
* **Intercambio de Datos:** JSON sobre HTTP (API REST)

---

## ⚙️ Cómo compilar y ejecutar (macOS / Windows / Linux)

1. Verificar que el endpoint en el VPS esté activo.
2. Abrir el archivo `Ejercicio02.pro` desde **Qt Creator**.
3. Configurar el kit de compilación correspondiente a tu sistema (Ej: *Desktop Qt... clang* para Mac).
4. En el menú superior, ir a **Build** (Compilar) y seleccionar **Clean All**.
5. Ir nuevamente a **Build** y seleccionar **Run qmake**.
6. Presionar el botón ▶️ **Play** para compilar y abrir el panel.
