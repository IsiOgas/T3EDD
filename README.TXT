Nombre: Isidora Ogas 
Rol: 202473654-K

Nombre: Matilde Vásquez
Rol: 202473652-3


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
Se realiza un BFS desde la pos actual del conductor hacia el pasajero.  Complejidad: O(n + a).
Seguido se verifica si no hay conductor (O(1)) y se eliminan los arreglos (O(1)). Complejidad: O(1).
Complejidad del bloque: O(c*(O(n) + O(n + a) + O(1) + O(1))) = O(c*(n + a)). 

-Verifiacion y pos conductor:
Se realiza una comparación simple de si se encontro un conductor. Complejidad: O(1).
Se obtiene la pos del conductor más cercano. Complejidad: O(1).
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
Luego el costo del viaje, mostrar el resultado, actualizar la pos del conductor al destino y eliminar memoria, todas toman tiempo constante. O(1) x 5.
Complejidad del bloque: O(n) + O(1) x 5 = O(n).

Finalmente al sumar se obtiene:
Complejidad total: O(c*(n + a)) +  O(n + a) + O(n + a) + O(n) + O(1) = O(c *(n + a)).

Obs: Las operaciones de inicialización de variables, verifiacion y eliminacion de memoria son constantes, por lo que no afectan la complejidad.
