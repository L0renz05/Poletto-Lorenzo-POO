🦖 Ejercicio 10: T-Rex Extremo - Físicas y Gestión de Eventos
Autor: Lorenzo Poletto

Universidad: Universidad Blas Pascal - Ingeniería Informática

Materia: Programación Orientada a Objetos (POO)

Tecnologías: C++17, Qt Framework (Widgets, Core, Gui)

El objetivo de este ejercicio consiste en desarrollar un videojuego de supervivencia en 2D basado en el clásico dinosaurio de Chrome, utilizando las herramientas gráficas y de control de tiempo que provee Qt. El sistema debe contar con un personaje principal capaz de saltar y agacharse, generación de obstáculos (terrestres y aéreos), un aumento progresivo de la dificultad, manejo de eventos temporales únicos (singleShot), detección de colisiones y una pantalla de "Game Over" con posibilidad de reinicio, aplicando los conceptos de la Programación Orientada a Objetos para la gestión de memoria y la interacción entre entidades.

🛠️ Qué es lo que hice
Para resolver este proyecto, diseñé una arquitectura orientada a objetos donde un "Manager" (Juego) administra las listas de entidades dinámicas (TRex, Cactus, Pajaro) manteniendo un bajo acoplamiento. Implementé un motor de físicas propio para el salto del personaje principal (creando una parábola con gravedad en lugar de un desplazamiento estático) y un manejo robusto de la memoria dinámica para evitar Segmentation Faults al destruir los obstáculos que salen de la pantalla.

Principales implementaciones:

[x] Físicas y Gravedad: Implementación de un salto fluido para el T-Rex mediante el uso de ciclos en un QTimer independiente y cálculo de velocidad vertical (velocidadY).

[x] Generación Dinámica y Limpieza de Memoria: Creación automatizada de obstáculos (Cactus fijos en el suelo y Pájaros en el aire) con eliminación segura (deleteLater()) y limpieza de punteros desde el Manager al salir de los límites de la ventana.

[x] Dificultad Progresiva y Eventos Únicos: Incremento automático de la velocidad general del juego cada 5 segundos y aparición de un obstáculo kamikaze de alta velocidad a los 12 segundos utilizando QTimer::singleShot().

[x] Hitboxes Personalizadas: Reducción analítica de las cajas de colisión (QRect::adjusted()) respecto al tamaño total del QPixmap, permitiendo roces justos y mejorando la experiencia de usuario (UX).

[x] Ciclo de Juego Completo: Pantalla de Game Over renderizada nativamente con QPainter y reseteo integral de variables y temporizadores sin necesidad de reiniciar la aplicación.

⚙️ Instructivo de Ejecución y Uso
1. Cómo correrlo
Clonar el repositorio y abrir el archivo .pro en Qt Creator.

Importante: Verificar que las imágenes (dino.png, pajaro.png, cactus.png, gameover.png) se encuentren en la ruta absoluta especificada en el código fuente, o bien actualizar la función load() de los archivos .cpp para que apunten a la carpeta local donde se descargaron.

Ejecutar la opción Build > Run qmake en Qt Creator para asegurar que el compilador enlace correctamente el módulo de widgets.

Compilar y ejecutar el proyecto desde el entorno.

2. Controles y Atajos de Teclado
El sistema intercepta los eventos del teclado mediante la sobreescritura de keyPressEvent para controlar al personaje y el flujo de la partida:

Espacio: Permite al T-Rex realizar el salto parabólico. También se utiliza para reiniciar la partida una vez que aparece la pantalla de Game Over.

Flecha Abajo: Permite al T-Rex agacharse (reduce su altura) para esquivar a los pájaros que vuelan a media altura.

Flechas Izquierda / Derecha: Permite el desplazamiento horizontal fino del personaje por la pantalla.

R: Tecla rápida alternativa para reiniciar la partida desde la pantalla de Game Over.