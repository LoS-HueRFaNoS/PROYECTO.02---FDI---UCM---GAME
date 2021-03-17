<!-- Enlaces -->
[Web]: https://los-huerfanos.github.io/PROYECTO.02---FDI---UCM---GAME/
[Repositorio]: https://github.com/LoS-HueRFaNoS/PROYECTO.02---FDI---UCM---GAME
[Pivotal]: https://www.pivotaltracker.com/n/projects/2490864
[Twitter]: https://twitter.com/HuerfanosUCM
<!-- Imágenes -->
[IMG-Interfaz]: Proyecto.02/project/resources/images/interfaz/plantilla%20base%20interfaz.png "Esquema del HUD"
[fuego]: Proyecto.02/project/resources/sprites/iconos%20elementos/Fuego.jpg "IMG - Fuego"
[agua]: Proyecto.02/project/resources/sprites/iconos%20elementos/Agua.jpg "IMG - Agua"
[viento]: Proyecto.02/project/resources/sprites/iconos%20elementos/Viento.jpg "IMG - Viento"
[luz]: Proyecto.02/project/resources/sprites/iconos%20elementos/luz.jpg "IMG - Luz"
[oscuridad]: Proyecto.02/project/resources/sprites/iconos%20elementos/oscuridad.jpg "IMG - Oscuridad"
[Tierra]: Proyecto.02/project/resources/sprites/iconos%20elementos/Tierra.jpg "IMG - Tierra"
<!-- Personajes -->
[bardo]: Proyecto.02/project/resources/sprites/iconos%20personajes/bardo.png "IMG - Bardo"
[brujo]: Proyecto.02/project/resources/sprites/iconos%20personajes/brujo.png "IMG - Brujo"
[clerigo]: Proyecto.02/project/resources/sprites/iconos%20personajes/clerigo.png "IMG - Clerigo"
[guerrero]: Proyecto.02/project/resources/sprites/iconos%20personajes/guerrero.png "IMG - Guerrero"
[paladin]: Proyecto.02/project/resources/sprites/iconos%20personajes/paladin.png "IMG - Paladin"
[barbaro]: Proyecto.02/project/resources/sprites/iconos%20personajes/barbaro.png "IMG - Barbaro"
[explorador]: Proyecto.02/project/resources/sprites/iconos%20personajes/explorador.png "IMG - Explorador"
[picaro]: Proyecto.02/project/resources/sprites/iconos%20personajes/picaro.PNG "IMG - Picaro"
[druida]: Proyecto.02/project/resources/sprites/iconos%20personajes/druida.png "IMG - Druida"
[bestia]: Proyecto.02/project/resources/sprites/iconos%20personajes/bestia.png "IMG - Bestia"
[protagonista]: Proyecto.02/project/resources/sprites/iconos%20personajes/heroe-mago.png "IMG - Mago (protagonista)"
<!-- Enemigos -->
[lich]: Proyecto.02/project/resources/sprites/iconos%20personajes/lich.PNG "IMG - Lich"
[necro]: Proyecto.02/project/resources/sprites/iconos%20personajes/necrofago.png "IMG - Necrofago"
<!-- Objetos -->
<!-- Armas -->
[alabarda]: Proyecto.02/project/resources/sprites/iconos%20armas/alabarda.png "IMG - Alabarda"
[arco_largo]: Proyecto.02/project/resources/sprites/iconos%20armas/arco_largo.png "IMG - Arco Largo"
[arco_ligero]: Proyecto.02/project/resources/sprites/iconos%20armas/arco_ligero.png "IMG - Arco Ligero"
[ballesta_ligera]: Proyecto.02/project/resources/sprites/iconos%20armas/ballesta_ligera.png "IMG - Ballesta Ligera"
[ballesta_pesada]: Proyecto.02/project/resources/sprites/iconos%20armas/ballesta_pesada.png "IMG - Ballesta Pesada"
[baston]: Proyecto.02/project/resources/sprites/iconos%20armas/baston.png "IMG - Baston"
[clava]: Proyecto.02/project/resources/sprites/iconos%20armas/clava.png "IMG - Clava"
[daga]: Proyecto.02/project/resources/sprites/iconos%20armas/daga.png "IMG - Daga"
[espada_corta]: Proyecto.02/project/resources/sprites/iconos%20armas/espada_corta.png "IMG - Espada Corta"
[espada_larga]: Proyecto.02/project/resources/sprites/iconos%20armas/espada_larga.png "IMG - Espada Larga"
[hacha]: Proyecto.02/project/resources/sprites/iconos%20armas/hacha.png "IMG - Hacha"
[hacha_arrojadiza]: Proyecto.02/project/resources/sprites/iconos%20armas/hacha_arrojadiza.png "IMG - Hacha Arrojadiza"
[lanza]: Proyecto.02/project/resources/sprites/iconos%20armas/alabarda.png "IMG - Lanza"
[lucero]: Proyecto.02/project/resources/sprites/iconos%20armas/lucero.png "IMG - Lucero del Alba"
[martillo]: Proyecto.02/project/resources/sprites/iconos%20armas/martillo.png "IMG - Martillo"
[maza]: Proyecto.02/project/resources/sprites/iconos%20armas/maza.png "IMG - Maza"
[puños]: Proyecto.02/project/resources/sprites/iconos%20armas/puños.png "IMG - Puños"
<!-- Arquitecturas UML -->
[interfaz_uml]: Proyecto.02/project/resources/images/UML/interfaz_uml.png "Esquema UML del Interfaz"
[mapa_uml]: Proyecto.02/project/resources/images/UML/mapa_uml.png "Esquema UML del Mapa"
[personajes_uml]: Proyecto.02/project/resources/images/UML/personajes_uml.png "Esquema UML del Sistema de Personajes"
[combate_uml]: Proyecto.02/project/resources/images/UML/combate_uml.png "Esquema UML del Sistema de Combate"

# The elemental Maze #

| [Pagina web][Web] | [Repositorio][Repositorio] | [Gestión][Pivotal] | [Twitter][Twitter] |
| -- | -- | -- | -- |

> ###### Documento de diseño de videojuego - Versión 16/03/2021 (hito 1.0)

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

El juego se controla principalmente mediante el ***uso del ratón***, pulsando los distintos botones ofrecidos por la interfaz.

<p align="left"><b> <!-- ATAJOS DE TECLADO --> </b></p>

| Cursores | WASD | Función |
| -- | -- | -- |
| **Flecha derecha**   | **Tecla 'D'** | _rotar 90° a la derecha_ |
| **Flecha izquierda** | **Tecla 'A'** | _rotar 90° a la izquierda_ |
| **Flecha arriba**    | **Tecla 'W'** | _avanzar a la siguiente posición_ |
| **Espacio** | **Tecla 'E'** | _interactuar con el entorno_ |


## 4. Jugabilidad ##

- ### 4.1. Mecánicas ###

  - #### 4.1.1. Movimiento ####

* Para pasar de nivel, el jugador ha de recorrer el laberinto hasta encontrar una casilla final en la que se encuentra la salida.

* El jugador cuenta con un minimapa que le permite saber qué zonas del nivel ha visitado y cuáles son los caminos que no ha explorado.
* 
* Al final de cada nivel, el jugador puede salir de la mazmorra con todos los héroes que hayan sobrevivido y así mantener todas las cosas que ha conseguido o arriesgarse y seguir avanzando para intentar superar el siguiente nivel.

  - #### 4.1.2. Combate ####

* Cuando un enemigo o jugador realiza un ataque, realiza una tirada de fuerza o inteligencia dependiendo de si el ataque es físico o mágico. Por otro lado, el contrincante realiza una tirada de destreza: Si el número de la tirada de destreza supera al número obtenido en el ataque, el personaje no recibe daño; si es al contrario, el atacante realiza otra tirada para calcular el daño según los índices que tenga el arma o el hechizo usado.

* Al coincidir con un enemigo en la misma casilla, comenzará un combate por turnos. Al comenzar el combate, se reparten los turnos según el número obtenido, por tanto, se hace una tirada por cada personaje en la batalla. Cuanto más alto sea el valor de la tirada, antes hará una acción ese personaje.
* Las acciones que el jugador puede realizar durante un turno del combate son: _atacar, protegerse, utilizar un objeto, lanzar un hechizo y/o habilidad o huir_ (Si queremos abandonar el combate) 
* El jugador debe seleccionar uno de los movimientos que tenga disponibles con cada uno de sus héroes. En el caso de que sea un ataque, se hará una tirada de 1d20 (+ MOD) que se comparará con la AC del objetivo así como su tirada de DEX, en el caso de superar ambas el ataque impactará. Para determinar el daño del ataque se tirará los dados requeridos por el mismo (ejemplo: Bola de Fuego 8d6 contra salvación), en el caso de que el ataque requiera una tirada de salvación por parte del objetivo se tirará 1d20 (+MOD) para calcular el daño/estado final. 
* En el caso de ser una habilidad defensiva/curativa dependerá de la descripción de la misma.
* Cuando se hace una tirada de ataque, al tirar el 1d20 por impacto se deben tener en cuenta dos casos especiales: 
    * **Crítico (roll 20)**: en el caso de sacar un 20 en una tirada de ataque se impactará al objetivo sin importar su AC, DEX o modificadores. También se volverá a tirar los dados de daño el doble de veces (ejemplo: si ataco con una daga con daño 1d4 y sale crítico atacará con 2d4 en su lugar).
    * **Pifia (roll 1)**: en el caso de sacar un 1 en la tirada, se fallará el ataque sin importar modificadores.
* Los hechizos consumen maná, al contrario que los ataques normales. Si un personaje no tiene maná suficiente para lanzar un hechizo, simplemente no podrá ejecutar esa acción.
* Al seleccionar la opción de huir, habrá una tirada de dados. Si el número es más alto que un valor determinado según el combate, huiremos con éxito y aparecemos en una casilla segura. Si el número que salga es menor, perderemos el turno.
* Cuando los puntos de vida del enemigo lleguen a cero, este morirá, acabará el combate y el jugador ganará dinero y experiencia.
* Si algún integrante del grupo pierde todos sus puntos de vida, el jugador perderá dicho personaje y todo el progreso alcanzado con el mismo.
* Si el grupo es derrotado, el jugador conserva el dinero recogido pero pierde a todos sus héroes y por tanto sus progresos.

  - #### 4.1.3. Gestión ####

* Al comenzar la partida, se muestra un menú en el que el jugador elige a un conjunto de héroes. Aquí comienza la estrategia del jugador.

* Todo el grupo se mueve en conjunto por el mapa. Cada integrante posee sus propios movimientos de combate, estadísticas y objetos.
* Las estadísticas de los personajes se dividen en cuatro grupos: 
    * **fuerza**, utilizada para medir el daño que realizan los ataques físicos y su eficacia; 
    
    * **destreza**, usada para calcular la capacidad para evadir ataques del personaje; 
    * **constitución**, determina la resistencia ante los ataques del enemigo y sus puntos extras de salud; 
    * **inteligencia**, usada para medir el daño que realizan los ataques mágicos y su eficacia, además de indicar los puntos extra de maná.

- ### 4.2. Dinámica ###

El jugador conforma un grupo de héroes equipados con armas, armaduras, habilidades y objetos disponibles antes de cada aventura. 

Tendrá que elegir el camino a seguir e intentar llegar a la salida del laberinto de cada nivel. Durante la aventura, encontrará enemigos y deberá decidir si desea huir y buscar otro camino o intentar vencerlos para continuar por la ruta actual. Cuando pierde en la batalla, perderá el equipo de aventureros y tendrá que crear uno nuevo con otros héroes. 

Hay que tener en cuenta también la tabla de tipos elementales, para poder realizar ataques más efectivos.

- #### Objetivo ####
El jugador tiene como objetivo completar la mazmorra y derrotar al Lich. 
En caso de que lo consiga, el jugador habrá ganado la partida.

- #### Dificultad ####
La dificultad es igual para todos los jugadores, no se puede elegir, pero el jugador tiene a su disposición objetos y diferentes personajes que le permiten elegir entre si correr un mayor riesgo por mayor daño y menos salud, como llevar varios magos en el grupo de héroes, o por el contrario jugar de forma más segura, llevando un equipo más equilibrado. También la gestión del dinero y objetos del jugador hará que el juego se le haga más fácil o difícil de pasar. También depende de las decisiones que realicemos dentro del combate, como ir más a hacer daño de “golpe” o ir más poco a poco.

- #### Recompensas y castigos ####
El jugador es recompensado con la puntuación y los logros que se obtienen al usar determinados objetos, personajes u opciones, y la dificultad, que disminuirá si usamos objetos o personajes “correctos”. El castigo en respuesta a las malas elecciones y acciones del jugador será la muerte de los héroes, y si se queda sin ningún héroe, con la muerte, donde el jugador deberá empezar desde el principio cada vez que muera.

- ### 4.3. Estética ###

La ambientación del juego va a ser con temática _Dark Fantasy_, representando así un mundo maligno y con ambiente oscuro, con criaturas fantásticas y oscuras, que provoca que los héroes, de buen corazón, intenten acabar con el Lich, para acabar así con la oscuridad, en busca de una renovación del pueblo, por lo tanto haciendo el viaje del héroe (héroes en este caso) y salvando al pueblo, a cambio de una recompensa económica.

Las sensaciones que el jugador puede experimentar dentro de una partida es _el miedo_, cuando nos referimos a que son especies peligrosas y que estaremos en combate; _la incertidumbre_, al aparecer en una mazmorra desconocida donde el jugador debe pensar cuidadosamente cómo va a afrontar los problemas que están por venir, al tener que adaptar su comportamiento al estilo de juego dependiendo de los objetos equipados, los héroes contratados y las acciones que haga tanto el jugador como los enemigos; _la satisfacción_ al completar alguna sala y poder conseguir logros, objetos nuevos e incluso nuevos héroes o _la decepción_ de ser vencido dentro del juego teniendo que volver a empezar la partida.
La sensación de decepción puede llevar a la desesperación del jugador, aunque también se busca que ésta impulse las ganas por aprender del jugador.

El arte del juego será 2D, con una gama de colores oscura y fantástica, con tonos más apagados, para dar sensación de estar en un ambiente tétrico y oscuro.

El juego está dirigido a personas hispanohablantes a partir de los 12 años, ya que es un juego en castellano RPG, con estrategia, pelea y administración de recursos, por lo que una edad menor no podría comprender mucho del juego.

## 5. Contenido ##

- ### 5.1.  Historia ###
***The elemental Maze*** narra las desdichas del Gran Archimago durante sus numerosos intentos por acabar con un poderoso Lich que aterroriza los pueblos cercanos a la Torre de Magia, intentando eliminar a la amenaza con numerosos mercenarios contratados en la taberna y procurando obtener la mayor cantidad de beneficios en el proceso, ya sea invirtiendo la mínima cantidad de monedas en los supuestos héroes o saqueando los laberínticos pasillos infestados de monstruos de la cambiante mazmorra donde reside la temible criatura.
- ### 5.2.  Niveles ###
Cada nivel es un laberinto pequeño donde el jugador irá encontrando enemigos y objetos que podrá utilizar durante su recorrido por la mazmorra, mientras que busca la salida de la susodicha zona. Habrá salas especiales en las que nos encontraremos con enemigos más fuertes o con un cofre del tesoro, que al abrirlo nos permite obtener objetos para mejorar nuestros personajes.
- ### 5.3.  Héroes ###
| ICONO | NOMBRE | DESCRIPCIÓN |
| -- | -- | -- |
| ![img - bardo][bardo] | **BARDO** | Los bardos son unidades débiles en el combate, pero cuentan con una gran capacidad para evadir ataques enemigos y están especializados en los hechizos para mejorar las características de sus aliados o empeorar las de sus enemigos. |
| ![img - brujo][brujo] | **BRUJO** | Los brujos son unidades débiles en el combate físico, ya sea para atacar o evadir las arremetidas del enemigo, pero lo compensan con un gran arsenal de hechizos de ataque. |
| ![img - clerigo][clerigo] | **CLÉRIGO** | Los clérigos son unidades especializadas en los hechizos de curación y protección, aunque tienen bastantes dificultades para esquivar los ataques de los enemigos. |
| ![img - guerrero][guerrero] | **GUERRERO** | Los guerreros son unidades especializadas en el combate físico dada su fuerza y resistencia, pero que no cuentan con muchos hechizos y/o habilidades. |
| ![img - paladin][paladin] | **PALADÍN** | Los paladines son unidades lentas pero muy resistentes, especializándose en el combate físico y en los hechizos y/o habilidades de protección. |
| ![img - barbaro][barbaro] | **BÁRBARO** | Los bárbaros son unidades especializadas en el combate físico, aunque cuentan con un limitado número de hechizos y/o habilidades, los cuales suelen estar enfocados en aumentar su poder de ataque. |
| ![img - explorador][explorador] | **EXPLORADOR** | Los exploradores son unidades veloces pero con poca resistencia, que suelen estar especializadas en ataques débiles que afectan a varios enemigos en un solo turno. |
| ![img - picaro][picaro] | **PÍCARO** | Los pícaros son unidades veloces pero débiles en el combate físico, que poseen numerosos hechizos y/o habilidades especializadas en generar estados alterados en los enemigos. |
| ![img - druida][druida] | **DRUIDA** | Los druidas son unidades cambiantes, que comienzan los combates como unidades débiles en el combate físico pero con un gran arsenal de hechizos ofensivos. Tras finalizar varios turnos, si el jugador prefiere un estilo de juego más agresivo, podrá cambiar a la forma de ***bestia***. |
| ![img - bestia][bestia] | **BESTIA** | En esta forma, el druida, tendrá mucha fuerza y resistencia a cambio de anular su capacidad para lanzar hechizos. |
| ![img - protagonista][protagonista] | **GRAN ARCHIMAGO** | Cuenta con numerosos mercenarios contratados en la taberna y procura obtener la mayor cantidad de beneficios en el proceso, ya sea invirtiendo la mínima cantidad de monedas en los supuestos héroes o saqueando los laberínticos pasillos infestados de monstruos de la cambiante mazmorra donde reside la temible criatura. |
- ### 5.4.  Enemigos ###
| ICONO | NOMBRE | DESCRIPCIÓN |
| -- | -- | -- |
| ![img - lich][lich] | **LICH** | El todopoderoso Lich lanza hechizos sobre su propia guarida para transformarla y así cambiar la ruta para llegar hasta sus aposentos. Debido a su hechizo logra que la ruta sea cada vez distinta, por tanto nuestros héroes quedan totalmente desorientados y así trata que nadie interrumpa en sus maléficos planes. |
| ![img - necro][necro] | **NECROFAGO** | Los necrofagos son unidades débiles en el combate, pero cuentan con una gran capacidad para recuperarse comiendo los restos de aquellos héroes a los que logran matar. |
- ### 5.5.  Objetos ###
| ICONO | NOMBRE | DESCRIPCIÓN |
| -- | -- | -- |
- ### 5.6.  Equipo ###
| ICONO | NOMBRE | DESCRIPCIÓN |
| -- | -- | -- |
| ![img - maza][maza] | **MAZA** | Un arma **simple y ligera** que puede hacer hasta **6** puntos de daño **contundente**. |
| ![img - baston][baston] | **BASTÓN** | Un arma **simple y adaptable** que puede hacer hasta **6 u 8** puntos de daño **contundente**, dependiendo de si el jugador realiza un ataque fuerte o uno rápido. |
| ![img - daga][daga] | **DAGA** | Un arma **simple y ligera** que puede hacer hasta **6** puntos de daño **perforante**. |
| ![img - lanza][lanza] | **LANZA** | Un arma **simple y adaptable** que puede hacer hasta hasta **6 u 8** puntos de daño **perforante**, dependiendo de si el jugador realiza un ataque fuerte o uno rápido. Tiene además un ataque que puede ocasionar hasta **12** puntos de daño, pero necesita cargar durante un turno. |
| ![img - hacha][hacha] | **HACHA PEQUEÑA** | Un arma **simple y ligera** que puede hacer hasta **6** puntos de daño **cortante**. |
| ![img - clava][clava] | **CLAVA** | Un arma **simple y adaptable** que puede hacer hasta **6 u 8** puntos de daño **cortante**, dependiendo de si el jugador realiza un ataque fuerte o uno rápido. |
| ![img - arco_ligero][arco_ligero] | **ARCO LIGERO** | Un arma **simple y de área** que puede hacer hasta **4** puntos de daño. |
| ![img - ballesta_ligera][ballesta_ligera] | **BALLESTA LIGERA** | Un arma **simple y de área** que puede hacer hasta **8** puntos de daño, aunque necesita cargar antes de realizar cada disparo. |
| ![img - puños][puños] | **PUÑOS** | Un arma **marcial y ligera** que puede hacer hasta **8** puntos de daño **contundente**. |
| ![img - martillo][martillo] | **MARTILLO DE GUERRA** | Un arma **marcial y adaptable** que puede hacer hasta **10 u 12** puntos de daño **contundente**, dependiendo de si el jugador realiza un ataque fuerte o uno rápido. |
| ![img - espada_corta][espada_corta] | **ESPADA CORTA** | Un arma **marcial y ligera** que puede hacer hasta **8** puntos de daño **cortante**. |
| ![img - espada_larga][espada_larga] | **ESPADA LARGA** | Un arma **marcial y adaptable** que puede hacer hasta **10 u 12** puntos de daño **cortante**, dependiendo de si el jugador realiza un ataque fuerte o uno rápido. |
| ![img - lucero][lucero] | **LUCERO DEL ALBA** | Un arma **marcial y ligera** que puede hacer hasta **8** puntos de daño **perforante**. |
| ![img - alabarda][alabarda] | **ALABARDA** | Un arma **marcial y adaptable** que puede hacer hasta **10 u 12** puntos de daño **perforante**, dependiendo de si el jugador realiza un ataque fuerte o uno rápido. |
| ![img - arco_largo][arco_largo] | **ARCO LARGO** | Un arma **marcial y de área** que puede hacer hasta **6** puntos de daño. |
| ![img - ballesta_pesada][ballesta_pesada] | **BALLESTA PESADA** | Un arma **marcial y de área** que puede hacer hasta **10** puntos de daño, aunque necesita cargar antes de realizar cada disparo. |
<!-- - ### 5.7.  Armaduras ###
| ICONO | NOMBRE | DESCRIPCIÓN |
| -- | -- | -- | 
- ### 5.8.  Habilidades ###
| ICONO | NOMBRE | DESCRIPCIÓN |
| -- | -- | -- | -->
- ### 5.7.  Tipos elementales ###
Los tipos elementales serán seis: _fuego, agua, tierra, aire, luz y oscuridad_.

Las armas que sean de un tipo elemental determinado realizarán una pequeña cantidad extra de daño, siendo esta cantidad dependiente de las debilidades que posea el enemigo. Es decir, si el enemigo es débil a ese elemento, los puntos de daño realizados se duplicarán. Si, por el contrario, el enemigo es resistente a ese elemento, no se realizará ningún punto extra de daño.

Respecto a las armaduras, el tipo elemental realizará la misma función que en las armas pero a la inversa. Por ejemplo, si una armadura recibe un ataque de un elemento al cual es resistente, no recibirá puntos de daño. Pero si, por el contrario, recibe un ataque de un elemento al cual es débil, el daño recibido se duplicará.

En ambos casos, tanto en armas como en armaduras, el tipo elemental estará representado con el fondo, siendo cada color una representación un elemento concreto.

| ICONO | NOMBRE | ICONO | NOMBRE |
| -- | -- | -- | -- |
| ![img - fuego][fuego] | **FUEGO** | ![img - agua][agua] | **AGUA** |
| ![img - viento][viento] | **VIENTO** | ![img - tierra][tierra] | **TIERRA** |
| ![img - luz][luz] | **LUZ** | ![img - oscuridad][oscuridad] | **OSCURIDAD** |

## 6. Arquitectura UML ##

<p align="center"><b> INTERFAZ </b></p>

![UML - Interfaz][interfaz_uml]

<p align="center"><b> MAPA Y LABERINTO </b></p>

![UML - mapa][mapa_uml]

<p align="center"><b> SISTEMA DE PERSONAJES </b></p>

![UML - personajes][personajes_uml]

<p align="center"><b> SISTEMA DE COMBATE </b></p>

![UML - combate][combate_uml]

## 7. Plataforma de gestión ##

La plataforma de gestión que estamos utilizado durante el desarrollo del juego es ***Pivotal Tracker***. La cual es una herramienta de gestión de proyectos ágiles desarrollada por expertos en desarrollo de software ágil. Fácil de usar, esta herramienta posibilita la colaboración en tiempo real en torno a un registro compartido priorizado.

En esta plataforma hemos organizado las historias de usuario de cada uno de los integrantes, su puntuación, los diferentes hitos, etc.

## 8. Plataformas de comunicación ##

La plataforma de comunicación que estamos utilizado durante el desarrollo del juego es ***Discord***. La cual es una plataforma social destinada a permitir crear grupos de chat para diferentes juegos y finalidades. Se puede pensar en ella como una aplicación similar a _Skype_ o _TeamSpeak_, aunque incluye las funciones de otras herramientas más profesionales. Además tiene bastantes funcionalidades, permitiendo la comunicación por chat de texto, de voz o incluso realizar videoconferencias, todo ello con una aplicación totalmente gratuita. Dentro de estas funcionalidades está la posibilidad de crear y gestionar tu propio servidor de trabajo, totalmente personalizado, seccionando las áreas de trabajo y permitiendo crear un sistema de roles para garantizar un uso adecuado del servidor.

En esta plataforma hemos debatido todos los problemas del proyecto, realizado las reuniones diarias y comentado aspectos fundamentales del proyecto e ideas relevantes a este.

## 9. Referencias ##

* **Estéticas**: 
    * Dark Souls (Videojuego)
    * Chronoweaver (Videojuego)
    * 7 Mages (Videojuego)

* **Mecánicas**:
    * Dungeons and Dragons (Juego de rol)
    * Might & Magic (Videojuego)
    * Eye of the Beholder (Videojuego)

* **Dinámicas**:
    * Crimson Keep (Videojuego)
    * Darkest Dungeon (Videojuego)
    * Wizards of Legends (Videojuego)
    * Elemental Dungeon (Videojuego)


###### DEVELOPED BY: LOS "HUÉRFANOS"
