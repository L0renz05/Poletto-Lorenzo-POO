# 🚀 Ejercicio 08: Editor Multilenguaje y Análisis Sintáctico Polimórfico

**Autor:** Lorenzo Poletto  
**Materia:** Programación Orientada a Objetos (POO)  
**Tecnologías:** C++17, Qt Framework (Widgets, PrintSupport, Manejo de Eventos)

## 📌 Descripción del Proyecto
Este proyecto consiste en un editor de código avanzado diseñado para demostrar el dominio de la Programación Orientada a Objetos mediante el uso intensivo del **polimorfismo** y la **redefinición de eventos nativos**. El sistema permite editar código en C++, Python y Java, validando la sintaxis en tiempo real al abandonar la línea de edición.

## ✅ Requisitos Cumplidos (Consigna Oficial)
- [x] **Arquitectura Abstracta:** Implementación de la clase base `Pantalla` con métodos virtuales puros (`inicializarUI`, `conectarEventos`, `cargarDatos`, `validarEstado`, `registrarEvento`).
- [x] **Flujo Polimórfico:** El motor de la aplicación gestiona las transiciones entre pantallas (`Login`, `EditorPrincipal`, `ModoBloqueado`) trabajando exclusivamente con punteros a la clase base.
- [x] **Jerarquía de Validadores:** Uso de polimorfismo para el análisis sintáctico mediante la clase abstracta `ValidadorSintaxis` y sus derivadas específicas para cada lenguaje.
- [x] **Editor Personalizado (`CodeEditor`):** Sobreescritura (override) de eventos nativos de Qt:
    - `keyPressEvent`: Captura de atajos y validación en saltos de línea.
    - `mousePressEvent` / `focusOutEvent`: Validación automática al cambiar de contexto o abandonar el foco.
    - `focusInEvent`: Retroalimentación visual al ganar el foco.
    - `closeEvent`: Intercepción de cierre para confirmar guardado/exportación.
    - `resizeEvent`: Adaptación del contenido y registro de dimensiones.
- [x] **Seguridad y Bloqueo:** Pantalla de `ModoBloqueado` con cuenta regresiva basada en el tiempo definido en la configuración, separada de la lógica del Login.
- [x] **Exportación Gráfica:** Funcionalidad para exportar el código fuente renderizado a un archivo `.JPG` legible.
- [x] **UI Dinámica:** Integración de un panel lateral con currículum estilo LinkedIn y visualización de la ventana principal en pantalla completa (`FullScreen`).
- [x] **Persistencia Local:** Registro detallado de acciones en `registro.log` y configuración flexible mediante `config.ini`.
- [x] **Soporte Offline:** Funcionamiento garantizado sin dependencias de red externas ni SDKs.

## 🏗️ Arquitectura Técnica
La aplicación se apoya en dos pilares polimórficos:
1.  **Gestor de Interfaces (UI Manager):** Un puntero abstracto central controla el ciclo de vida de las ventanas, permitiendo que la aplicación escale sin que los módulos se conozcan entre sí (bajo acoplamiento).
2.  **Motor de Sintaxis (Syntax Engine):** Permite añadir soporte para nuevos lenguajes simplemente heredando de la clase base `ValidadorSintaxis`, sin necesidad de modificar la lógica interna del componente del editor.

## ⚙️ Configuración y Ejecución
1. Asegurarse de compilar el proyecto con el módulo `printsupport` incluido en el archivo `.pro`.
2. El archivo de configuración `config.ini` debe estar en la raíz de ejecución con la siguiente estructura:
   ```ini
   [Seguridad]
   usuario=admin
   tiempo_bloqueo=10

   [Editor]
   lenguaje_defecto=C++
   ruta_exportacion=codigo_exportado.jpg