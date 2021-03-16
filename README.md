[Web]: https://los-huerfanos.github.io/PROYECTO.02---FDI---UCM---GAME/
[Repositorio]: https://github.com/LoS-HueRFaNoS/PROYECTO.02---FDI---UCM---GAME
[Pivotal]: https://www.pivotaltracker.com/n/projects/2490864
[Twitter]: https://twitter.com/HuerfanosUCM
[IMG-Interfaz]: Proyecto.02/project/resources/images/interfaz/plantilla%20base%20interfaz.png "Esquema del HUD"

# The elemental Maze #

| [Pagina web][Web] | [Repositorio][Repositorio] | [Gestión][Pivotal] | [Twitter][Twitter] |
| -- | -- | -- | -- |

###### Documento de diseño de videojuego - Versión 16/03/2021 (hito 1.0)

## 1. Resumen ##

- **Géneros**: RPG, dungeon crawler, aventura, estrategia.

- **Modos**: 1 Jugador.
- **Público objetivo**: Jugadores casuales hispanohablantes mayores de 12 años.
- **Plataformas**: PC Windows.
- **Hitos**:
  
  + _Propuesta del concepto_: 24-02-2021
  
  + _Pre-producción_: 17-03-2021
  + _Producción_: 28-04-2021
  + _Lanzamiento_: 19-06-2021
  
## 2. Aspectos generales ##

*The elemental Maze* es un juego RPG de aventura estratégica, donde el jugador controla el equipo de héroes para explorar la mazmorra donde se refugia el Lich.
Si mueren todos los héroes, el jugador tiene que reclutar más.
Durante este periodo de tiempo, el Lich reformará la mazmorra, modificando la disposición de los pasillos.

- ### 2.1. Relato breve y parcial de una partida típica ###

El jugador selecciona a los héroes que quiere utilizar en la mazmorra, teniendo en cuenta sus estadísticas y su equipamiento.
Tras confirmar el grupo de aventureros, el jugador ve una transición y aparece en un laberinto.
Después, recorre el laberinto recogiendo objetos y derrotando enemigos.
Tras alcanzar la salida en varias ocasiones, encuentra la sala del jefe final.

## 3. Menús y modos de juego ##

El único modo de juego disponible es el modo de un solo jugador, en el que éste podrá jugar las veces que quiera, completando el juego de formas distintas.

Existen los siguientes menús dentro del juego:
* **Menú principal**: Es el menú que aparece al iniciar el juego.
En este menú encontramos los siguientes botones: _comenzar partida, configuración, mostrar ayuda_.
* **Menú de configuración**: En este menú se pueden modificar las siguientes opciones: _establecer volumen y establecer velocidad de animación_.
Es accesible en cualquier momento.
* **Ayuda**: Pantalla con breves instrucciones para comenzar una partida básica y con recordatorios acerca del objetivo que debe alcanzar el jugador.
* **Tienda de compra**: Este menú aparece al empezar una partida.
En él se puede _contratar héroes, comprar armas, mejorar habilidades, vender héroes u objetos, etc_.
* **Menú de partida**: Este menú aparece al darle al botón de mochila del HUD.
Se puede gestionar _el equipamiento de héroes, armas, mejora de habilidades, entrar a la mazmorra, curar a los personajes o aplicar buffs parciales a éstos_.
* **Menú de pausa**: Este menú aparece al darle al botón de ayuda y configuración.
En él se permite acceder al _Menú de configuración_ y a la _Ayuda_, así como _abandonar la partida actual_.

- ### 3.1. Interfaz y control ###

Dentro del juego, el HUD se divide en distintas partes o funcionalidades:
* **Ventana principal**: Aquí se muestra en primera persona la sala actual en la que se encuentra el jugador y los elementos de interés cercanos a ella tales como objetos o enemigos (siempre que no se encuentren tras ángulos muertos).
Está situada en la parte superior izquierda y ocupa más de la mitad de la pantalla.
  * **Vida de los enemigos**: Barras rojas situadas cada una sobre un enemigo durante un combate.
  Su nivel de relleno representa la vida restante del adversario sobre el que se ubica.
* **Minimapa**: Muestra la parte del nivel cercana al jugador, incluyendo la sala en la que está y los caminos colindantes a ella.
Alguno de estos caminos puede contener algún símbolo que indique si hay algún tesoro o hay enemigos en ese punto.
Está situado en la parte superior derecha de la pantalla.
* **Estado de los personajes**: Muestra el icono y la información de cada uno de los héroes del equipo mediante una barra roja (barra de vida) y una barra azul (barra de maná).
Cada personaje tendrá un icono para poder diferenciarlo de otros.
Se encuentra en el margen derecho, debajo del minimapa.
Si se hace click en alguno de los personajes, aparece _una ficha con sus datos_: puntos de vida totales, puntos totales de maná, objetos equipados, etc.
* **Objetos y misceláneos**: En esta parte del HUD situada en la esquina inferior derecha encontraremos el botón de mochila, dos botones rápidos de pociones (uno de vida y el otro de maná) que restaurarán parte de alguno de estos atributos a alguno de los personajes, el interruptor para mostrar/ocultar el chat y el botón de configuración/ayuda.
  * **Mochila**: Al pulsar el botón de mochila del apartado anterior, aparece una pantalla con todos los objetos que lleva el jugador con él, el inventario. Esta pantalla también permite equipar a los personajes con los distintos objetos recogidos.
  * **Chat**: Al pulsar el botón aparecen en pantalla las últimas acciones realizadas en el juego (como el daño realizado/recibido de un enemigo, la apertura de un cofre o el         resultado de una tirada de dados).
* **Movimiento e interacción**: Esta parte del HUD sólo aparecerá cuando el jugador no se encuentre en combate.
Contiene 3 flechas de dirección: _movimiento hacia adelante, rotación hacia la derecha y rotación hacia la izquierda_.
También hay un botón que sirve para _interactuar con el entorno_: abrir un cofre, hablar con un personaje, etc.
Está situado en la esquina inferior izquierda.
* **Combate**: Esta parte sólo aparecerá cuando el jugador esté en combate y reemplaza la sección **“Movimiento e interacción”**.
Contiene los siguientes botones: _ataque básico, ataque mágico elemental (usa maná), defensa, huir y mostrar turnos_ (este último, es un interruptor que despliega un panel vertical, en él figura la cara del siguiente personaje que va a atacar).
  * **Pantalla de turnos**: Si se hace click en este último botón del apartado **“Combate”**, se despliega un panel vertical sustituyendo al botón, en el que se visualiza el orden de ataque de todos los personajes y enemigos.
  Si ya estaba desplegado el panel, esta zona de la interfaz vuelve a su estado original.
  
![Esta imagen muestra el esquema del HUD][IMG-Interfaz]

<p align="center"><b> Esquema del HUD </b></p>

El juego se controla principalmente mediante el uso del ratón, pulsando los distintos botones ofrecidos por la interfaz.

***TODO - ATAJOS TECLADO***

## 4. Jugabilidad ##

- ### 4.1. Mecánicas ###

  - #### 4.1.1. Movimiento ####

* Para pasar de nivel, el jugador ha de recorrer el laberinto hasta encontrar una casilla en la que halla la salida.
* El jugador cuenta con un minimapa que le permite saber qué zonas del nivel ha visitado y cuáles son los caminos que no ha explorado.
* Al final de cada nivel, el jugador puede salir de la mazmorra con todos los héroes que hayan sobrevivido y así mantener todas las cosas que ha conseguido o arriesgarse y seguir avanzando para intentar superar el siguiente nivel.

  - #### 4.1.2. Combate ####

* ***TODO - RELLENAR ESTO***

  - #### 4.1.3. Gestión ####

* Al comenzar la partida, se muestra un menú en el que el jugador elige a un conjunto de héroes.
* Todo el grupo se mueve en conjunto por el mapa. Cada integrante posee sus propios movimientos de combate, estadísticas y objetos.
* Las estadísticas de los personajes se dividen en cuatro grupos: fuerza, utilizada para medir el daño que realizan los ataques físicos y su eficacia; destreza, usada para calcular la capacidad para evadir ataques del personaje; constitución, que determina la resistencia ante los ataques del enemigo y sus puntos extras de salud; e inteligencia, usada para medir el daño que realizan los ataques mágicos y su eficacia, además de indicar los puntos extra de maná.

- ### 4.2. Dinámica ###

***TODO - RELLENAR ESTO***

- ### 4.3. Estética ###

***TODO - RELLENAR ESTO***

## 5. Contenido ##

***TODO - CONTINUAR***

###### DEVELOPED BY: LOS "HUÉRFANOS"
