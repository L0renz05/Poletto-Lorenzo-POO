# 🎨 Ejercicio 03 - Lienzo Colaborativo en Tiempo Real

**Materia:** Programación Orientada a Objetos (POO)  
**Alumno:** Lorenzo Poletto  
**Equipo:** Santiago Agostini, Lorenzo Poletto, Avril Ogas  

---

## 🚀 Descripción del Proyecto
Esta aplicación es un **canvas compartido** desarrollado en **C++/Qt** que permite a múltiples usuarios dibujar de forma simultánea. Utiliza un backend en **Node.js** alojado en un VPS para centralizar los trazos, garantizando que todos los participantes vean los cambios en tiempo real sin perder información.

---

## ✨ Características Principales

* ✍️ **Dibujo fluido:** Implementación de curvas **Catmull-Rom** para suavizar el trazo a mano alzada, evitando líneas poligonales.
* 🤝 **Sincronización Colaborativa:** Sistema de "polling" cada 2 segundos que descarga y fusiona los trazos de otros usuarios.
* 🛡️ **Merge sin pérdida:** Los trazos se identifican con un **UUID único** y un **timestamp**. El servidor solo agrega trazos nuevos, por lo que nunca se pisa el trabajo de un compañero.
* 🎨 **Paleta Dinámica:** 9 colores calculados mediante interpolación lineal entre un tono rosa y un cian.
* 🖱️ **Control de Precisión:** Ajuste del grosor del trazo en tiempo real mediante la rueda del mouse.
* 🔳 **Interfaz Metro:** Botón de guardado diseñado con estilo visual *Windows Metro*.

---

## 📂 Estructura y Arquitectura (MVC)
El proyecto respeta una arquitectura modular para separar la lógica de la interfaz y la red:

* 📄 **`DrawingModel` (Modelo):** Gestiona el almacenamiento de los trazos (`QVector<Stroke>`). Implementa la lógica de fusión incremental y la exportación a JSON.
* 📄 **`CanvasView` (Vista):** Clase encargada del renderizado mediante `paintEvent`. Utiliza un sistema de **doble capa** (una para trazos fijos y otra para el trazo que se está dibujando en el momento) para un rendimiento óptimo.
* 📄 **`SyncManager` (Controlador/Red):** Maneja las peticiones HTTP (GET/POST) hacia el VPS de forma asíncrona mediante `QNetworkAccessManager`.
* 📄 **`server.js` (Backend):** Servidor API REST en Node.js que recibe, filtra y ordena los trazos por tiempo de creación.

---

## 🎮 Controles de la Aplicación

| Acción | Control |
| :--- | :--- |
| **Dibujar** | Clic Izquierdo + arrastrar |
| **Borrar** | Clic Derecho + arrastrar |
| **Cambiar Color** | Teclas **1** al **9** |
| **Grosor** | Rueda del mouse (Scroll) |
| **Guardar** | Botón **GUARDAR** (Sincronización manual) |

---

## ⚙️ Configuración y Ejecución

### 🌐 Servidor (VPS)
El backend está configurado y corriendo actualmente en:  
`http://161.97.92.143:3001`

Si deseas desplegarlo manualmente:
1. Navegar a `/server` y ejecutar `npm install express cors`.
2. Iniciar con `node server.js`.

### 💻 Cliente (Qt)
1. Abrir `collaborative_canvas.pro` en **Qt Creator**.
2. Configurar el kit de compilación (Qt 5.15+ / 6.x).
3. Compilar y ejecutar. Al iniciar, ingresar la URL del servidor mencionada arriba.