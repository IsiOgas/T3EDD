Nombre: Isidora Ogas 
Rol: 202473654-K

Nombre: Matilde Vásquez
Rol: 202473652-3

Al inicio de tarea3.cpp inicialmente está el macro #define NOMBRE_ARCHIVO "data1.txt". 
Cambiar "data1.txt" por el archivo que se quiera leer.

Grafo Data 2
La imagen abarca una zona delimitada (líneas amarillas) de la ciudad de Nueva York.
Los arcos bidimensionales son de color azul, mientras que los arcos dirigidos son de color rojo con una flecha.
Inicialmente, hay un conductor en cada nodo verde.
En el archivo data2.txt la primera línea indica la cantidad de nodos, la cantidad de arcos y la cantidad de conductores.


Análisis de Complejidad de solicitar_uber
n: cantidad nodos.
a: cantidad aristas (conexiones).
Cada BFS tiene complejidad de O(n + a) porque cada nodo y arista se visita una vez.

-Inicialización:
Se declaran 4 variables, todas de tiempo constante.
Complejidad: O(1).

-Búsqueda mejor conductor:
Se realiza un ciclo for que se repite c veces, donde c es la cantidadConductores. 
Dentro de este ciclo se crean dos arreglos de tamaño n. Complejidad: O(n)
Se realiza un BFS desde la posición actual del conductor hacia el pasajero.  Complejidad: O(n + a).
Seguido se verifica si no hay conductor (O(1)) y se eliminan los arreglos (O(1)). Complejidad: O(1).
Complejidad del bloque: O(c*(O(n) + O(n + a) + O(1) + O(1))) = O(c*(n + a)). 

-Verificación y posición conductor:
Se realiza una comparación simple de si se encontró un conductor. Complejidad: O(1).
Se obtiene la posición del conductor más cercano. Complejidad: O(1).
Complejidad del bloque: O(1) + O(1) = O(1).

-BFS desde el conductor al pasajero. 
Se crean dos arreglos de tamaño n. Complejidad: O(n).
Se realiza un BFS. Complejidad: O(n + a).
Seguido se verifica si el conductor puede llegar al pasajero (O(1)) y se eliminan los arreglos (O(1)). Complejidad: O(1).
Complejidad del bloque: O(n) + O(n + a) +  O(1) + O(1) =  O(n + a) 

-BFS desde el pasajero al destino:
Se crean dos arreglos de tamaño n. Complejidad: O(n).
Se realiza un BFS. Complejidad: O(n + a).
Seguido se verifica si hay un camino del pasajero al destino (O(1)) y se eliminan los arreglos (O(1)). Complejidad: O(1).
Complejidad del bloque: O(n) + O(n + a) +  O(1) + O(1) =  O(n + a) 

-Mostrar ruta y costo:
Se imprime por pantalla el camino desde el pasajero al destino mediante la función void mostrarCamino lo cual toma a lo más O(n).
Luego el costo del viaje, mostrar el resultado, actualizar la posición del conductor al destino y eliminar memoria, todas toman tiempo constante. O(1) x 5.
Complejidad del bloque: O(n) + O(1) x 5 = O(n).

Finalmente al sumar se obtiene:
Complejidad total: O(c*(n + a)) +  O(n + a) + O(n + a) + O(n) + O(1) = O(c *(n + a)).

Obs: Las operaciones de inicialización de variables, verificación y eliminación de memoria son constantes, por lo que no afectan la complejidad.


