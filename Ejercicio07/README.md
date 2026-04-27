# 🚀 Ejercicio 07: Sistema de Autenticación con Consumo de APIs y UI Dinámica

**Autor:** Lorenzo Poletto  
**Materia:** Programación Orientada a Objetos (POO)  
**Tecnologías:** C++17, Qt Framework (Widgets, Network)  

## 📌 Descripción del Proyecto
Este proyecto es una aplicación de escritorio desarrollada en C++ utilizando el framework Qt. Implementa un sistema de Login seguro y robusto, integrando consumo de APIs REST en tiempo real, persistencia de datos en caché, manejo avanzado de memoria dinámica e interfaces gráficas escalables.

## ✅ Requisitos Cumplidos (Consigna Oficial)
- [x] **Login Seguro:** Interfaz desarrollada con QtDesigner. Credenciales por defecto (`admin` / `1234`).
- [x] **Bloqueo Temporal:** Sistema de seguridad que bloquea la UI por 10 segundos tras 3 intentos fallidos.
- [x] **Consumo de API Externa:** Conexión a OpenWeatherMap mediante peticiones HTTP nativas, sin SDKs.
- [x] **Interfaz en Tiempo Real:** Visualización de temperatura y hora local en la pantalla de Login.
- [x] **Descarga y Caché de Imágenes:** Descarga asíncrona de imagen de fondo desde URL pública y almacenamiento en caché local (`fondo_cache.jpg`).
- [x] **Sincronización de UI:** La Ventana Principal se abre *únicamente* cuando la imagen ha terminado de descargar/leerse del disco.
- [x] **Diseño Responsivo:** Imagen principal ajustada a FullScreen manteniendo la relación de aspecto sin deformaciones (`Qt::KeepAspectRatioByExpanding`).
- [x] **Arquitectura Abstracta (UI):** Uso de clase base abstracta `Pantalla` con métodos virtuales puros, heredada por `Login` y `VentanaPrincipal`.
- [x] **Manejo de Datos Estructurado:** Creación de clase base `GestorDatos` y clases derivadas (`GestorClima`, `GestorImagen`) utilizando `QNetworkAccessManager`.
- [x] **Sistema de Logging:** Registro automático de eventos en el archivo local `registro.log` con estampa de tiempo.
- [x] **Archivos de Configuración:** Lectura de ciudad y API Key desde un archivo externo `config.ini`.
- [x] **Modo Offline:** Detección de errores de red y carga de datos simulados/caché en caso de no tener conexión a Internet.
- [x] **Signals & Slots:** Comunicación asíncrona entre módulos respetando los estándares del framework Qt.
- [x] **Perfil Profesional:** Ventana principal diseñada como un currículum estilo LinkedIn, elegante y profesional.

## 🏗️ Arquitectura Orientada a Objetos
El proyecto fue diseñado utilizando fuertemente el **Polimorfismo** y la **Herencia**:
1. **Módulo de Interfaz (UI):** La clase abstracta `Pantalla` establece un contrato inquebrantable (`inicializarUI() = 0`, `cargarTextos() = 0`) asegurando un diseño estandarizado para sus hijas concretas `Login` y `VentanaPrincipal`.
2. **Módulo de Red:** Se aplicó el principio de responsabilidad única. La clase abstracta `GestorDatos` inicializa los recursos de red, delegando a `GestorClima` y `GestorImagen` el procesamiento específico de los paquetes de datos y JSON.

## ⚙️ Instrucciones de Ejecución
1. Clonar el repositorio.
2. Asegurarse de tener un archivo `config.ini` en la raíz del código fuente con la siguiente estructura:
   ```ini
   [API]
   key=TU_API_KEY_REAL_AQUI

   [Ubicacion]
   ciudad=Cordoba