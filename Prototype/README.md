# Prototipo de Sistema de Sensor de Visión para IA
Se trata de un prototipo, apoyado para facilitar la depuración en las librerías de **SFML**, del sistema de visión que incluirá la inteligencia artificial en la versión final de Ancient Rise.

## Vista Previa
   ![Demo](https://i.imgur.com/ezuL9Ka.gif)
   ```
   Muestra del prototipo en funcionamiento
   ```
## Compilación y funcionamiento
Lo primero de todo es tener instaladas en nuestro sistema (Linux Manjaro preferiblemente) las librerías de [SFML](https://www.sfml-dev.org/download.php) .

Para iniciar el prototipo deberá ejecutarse desde un terminal y en la carpeta donde se encuentren los archivos, el ejecutable **PrototipoSensores**. Para ello utilizaremos el siguiente comando en dicho terminal:
 ```
 ./PrototipoSensores
 ```

En el caso de que pueda haber algún error con el ejecutable o se quiera realizar alguna modificación, se puede compilar un nuevo ejecutable con el comando **make**, haciendo uso del Makefile. Comando en el terminal:
 ```
 make
 ```
 Se generará un nuevo **PrototipoSensores** que pondremos en funcionamiento de la misma manera, explicada en el primer paso de este apartado *Compilación y funcionamiento*.
 
 Respecto al **funcionamiento**:
 
 Ya que se trata de un prototipo para el sensor de visión, dispondremos en éste de un personaje, representado con un cuadrado, el cual tiene asignado un área, en color blanco, correspondiente a su rango de visión.
 
 Con cuatro círculos de diferente color se representan objetos que puedan aparecer en el mapa. Uno de ellos, en concreto el de color cyan, es un objeto movible, del cual podremos modificar su posición.
 
 En el prototipo podremos manejar también al propio personaje, y modificar los parámetros que conforman su área de visión.

Los objetos dentro del área de visión del personaje en el momento actual, todos aquellos que el personaje puede ver, aparecen en la esquina superior izquierda, como podemos apreciar en la vista previa al inicio de éste documento. 

## Referencias y controles

![Personaje](https://i.imgur.com/OraMJHD.png) ---> Personaje, movimiento en el eje X (Izquierda y Derecha).

Tecla **D** - Movimiento a la Derecha.

Tecla **A** - Movimiento a la Izquierda.

![ObjetoMovible](https://i.imgur.com/kgofYSa.png) ---> Objeto Movible, movimiento en ambos ejes.

Tecla **↑** - Movimiento hacia Arriba.

Tecla **↓** - Movimiento hacia Abajo.

Tecla **→** - Movimiento hacia Derecha.

Tecla **←** - Movimiento hacia Izquierda.

![AreaVisión](https://i.imgur.com/HJQqPtQ.png) ---> Área de Visión, rango máximo y pendiente modificables.

Tecla **(/ División)** - Reducción del rango en X.

Tecla (* Multiplicación) - Aumento del rango en X.

Tecla **(- Resta)** - Reducción de la Pendiente.

Tecla **(+ Suma)** - Aumento de la Pendiente.
