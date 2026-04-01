# 🖥️ Ejercicio 02 - Panel de Monitoreo VPS
**Materia:** Programación Orientada a Objetos  
**Alumno:** Lorenzo Poletto  

---

## 🚀 Descripción
Este proyecto consiste en una aplicación de escritorio desarrollada en **C++ con Qt Framework** que funciona como un Dashboard de monitoreo para un servidor privado virtual (VPS). 

La aplicación se conecta de forma asíncrona a un **endpoint REST** (desarrollado en Python/Flask) alojado en el VPS, consume datos en formato **JSON** y los visualiza en tiempo real.

## 🛠️ Tecnologías y Conceptos Aplicados
* **Qt Network:** Uso de `QNetworkAccessManager` para peticiones HTTP GET.
* **JSON Parsing:** Procesamiento de datos mediante `QJsonDocument` y `QJsonObject`.
* **Programación Orientada a Objetos:** Implementación de una clase lógica (`Monitor`) separada de la interfaz de usuario (`Panel`).
* **UI Dinámica:** Diseño de interfaz por código (sin archivos .ui) usando Layouts, GroupBoxes y hojas de estilo (CSS).
* **Servidor:** API en Flask corriendo en el puerto **5050** del VPS.

## 📊 Métricas Monitoreadas
1. **Estado General:** Indicador visual de conexión (OK / Error / Consultando).
2. **CPU:** Porcentaje de uso de procesamiento.
3. **RAM:** Consumo de memoria volátil.
4. **Disco:** Espacio utilizado en el servidor.
5. **Uptime:** Tiempo de actividad del servicio.

---
*Proyecto desarrollado para la cátedra de POO - 2026.*