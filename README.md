# Practica 3: DesConecta-4 Boom

Esta práctica consiste en diseñar e implementar un agente deliberativo para que, mediante técnicas de búsqueda con adversario, consigamos que este gane a los tres *ninjas*. Yo me he decantado por utilizar el algoritmo de ***Poda Alfa Beta***.

- [Función Poda](#funci%C3%B3n-poda)
- [Función Valoracion](#funci%C3%B3n-valoracion)
- [Función Think](#funci%C3%B3n-think)

## Poda Alfa Beta

Es un algoritmo en el que vamos recorriendo un árbol de estados de tipo MinMax. Se le da un valor a los nodos de profundidad máxima siguiendo una función heurística y vamos subiendo estos valores modificando nuestras cotas *alpha* y *beta* dependiendo de si nos encontramos en un nodo *MAX* o uno *MIN*.

---

## Función Poda

Para completar la práctica he realizado una función *Poda_AlfaBeta* que se va llamando recursivamente. A esta función se le pasan como parametros:
- ***tablero*** : de la clase *Environment*, es el estado del tablero de juego a la hora de llamar a la función.
- ***jugador*** : es un *int* que puede tomar valor 1 o 2, hace referencia al jugador que llama a la función (el que vamos a intentar que gane).
- ***profundidad*** : es un *int* que indica a qué profundidad nos encontramos dentro del árbol de estados.
- ***LIM_PROF*** : también un *int* que nos dice la profundidad máxima a la que vamos a explorar el árbol de estados.
- ***accion*** : es un elemento del enumerado *ActionType*, este parametro está pasado por referencia y es donde la función va a guardar la mejor acción que podemos tomar.
- ***alpha*** : de tipo *double* es nuestra cota *alpha* para la poda.
- ***beta*** : de tipo *double* es nuestra cota *beta* para la poda.

La función *Poda_AlfaBeta* devolverá una valoración (de la que hablaremos más adelante) del *Environment* cuando la profundidad sea la determinada por nuestra variable *LIM_PROF* o cuando sea un nodo terminal, en el que el juego ya se haya terminado.  
Si no nos encontramos en una de las situaciones anteriores comprobamos si nos encontramos en un nodo *MAX* o uno *MIN*.

En un nodo ***MAX*** generamos un descendiente, que guardaremos en una variable *hijo*, con la función *GenerateNextMove(n_accion)* donde *n_accion* es un *int* que indica el número de la última accion realizada, en este primer hijo generado la variable que le pasamos tiene valor -1. Esta función además de devolver el *Environment* descendiente, también actualiza *n_accion*.  
Ahora entramos en un *while(n_accion < 8)*, la condición del *while* se debe a que el los posibles valores que puede tomar una acción van desde 0 hasta 7. Este número se irá actualizando con las llamadas a *GenerateNextMove(n_accion)*.  
Dentro del *while* llamamos de nuevo a la función *Poda_AlfaBeta* pasandole como tablero actual el hijo que hemos generado y aumentando la profundidad en 1. Esta llamada a la función poda devolverá el valor que se le da al tablero *hijo* generado anteriormente.  
En un *if* comprobamos si el valor del hijo es mayor que alpha y estamos en un nodo de profundidad 0, osea el nodo raíz. Si se cumplen las dos condiciones actualizamos el valor del parametro *accion* haciendo un *cast* del valor que tenga *n_accion*.  
En otro *if* comprobamos si el valor del hijo generado es mayor que la cota *alpha*, si es así actualizamos el valor de *alpha* asignándole el valor del hijo.  
Después hacemos otro *if* para comprobar si la cota *beta* es menor o igual que la cota *alpha*, si es así hacemos un *break* para salirnos del bucle *while* en el que nos encontramos. Si no nos hemos salido del bucle por la condición anterior generamos el siguiente hijo del nodo actual actualizando los valores de las variables *hijo* y *n_accion*.  
Una vez nos hayamos salido del bucle *while* y al estar en un nodo *MAX*, hacemos *return* del valor *alpha*.

En un nodo ***MIN*** es todo casi igual que en el nodo *MAX*, sólo se diferencia en las comprobaciones para actualizar *accion* y en que en un nodo *MIN* la cota que se va actualizando es la cota *beta*.  
Así pues actualizamos el valor de *accion* cuando se cumple que el valor del hijo es menor que *beta* y que estamos en el nodo raíz.  
Actualizamos el valor de *beta* con el valor del hijo cuando este es menor que *beta*.  
Y la última diferencia con respecto a un nodo *MAX* es que el valor que se devuelve al final, fuera del *while*, es el valor que tiene *beta*.

---

## Función Valoración

La función de valoración sirve para evaluar un estado de juego y darle un valor. A esta función se le pasan dos parametros:

- ***estado*** : es el estado de juego que se quiere evaluar.
- ***jugador*** : es el jugador que pide la valoración, se va a dar una valoración más alta si este jugador tiene más probabilidad de ganar.

Lo primero que se hace es comprobar si alguno de los jugadores ya ha ganado. Si el jugador que pide la valoración es el que ha ganado se devuelve el valor *masinf*, si es el contrincante el que ha ganado se devuelve el valor *menosinf*, si ha habido empate se devuelve 0. Si no se da ninguno de los casos anteriores se recorre todo el tablero haciendo una sumatoria de los valores que la función *evaluarCasilla* va asignando. Esta función asigna los siguientes valores a cada casilla:

- Si el jugador tiene 2 fichas seguidas: -5.0
- Si el contrincante tiene 2 fichas seguidas: +5.0
- Si el jugador tiene 3 fichas seguidas: -30.0
- Si el contrincante tiene 3 fichas seguidas +30.0

---

## Función Think

En esta función he puesto como valores para la cota *alpha* el valor de la variable *menosinf* y para la cota *beta* el de la variable *masinf*.

Inicialmente lo único que hacía en esta función era llamar a la función *Poda_AlphaBeta* y hacía un *cout* con los valores que recibía y la acción que se iba a realizar. Pero me di cuenta de que, a pesar de ganar a todos los *ninjas*, lo hacía en más turnos de los que debería ya que había varias jugadas que recibían el valor *masinf* entonces para la función poda era indiferente cuál coger, siempre cogía el primero que encontraba, nunca la jugada *BOOM* ya que es la última que se evalúa.

Esto hacía que mi heurística a pesar de que explotando una bomba ya podía ganar no lo hacía, realizaba otra jugada que también recibía valor *masinf*. Para solucionar esto y que mi heurística ganase en menos turnos hice lo siguiente:

Comprobé en un *if* si el jugador tiene una bomba en el tablero, si es así generamos un *Environment* al que le aplicamos la jugada *BOOM*. Si en ese estado nuestro jugador ha ganado ponemos como valor de *accion* la jugada *BOOM* y no realizamos la llamada a la función *Poda_AlfaBeta*, si nuestro jugador no gana en ese estado llamamos a la función *Poda_AlfaBeta* que nos dirá qué estado es mejor.

Finalmente se devuelve *accion*.