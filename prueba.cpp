#include <iostream>
#include <fstream>
using namespace std;

#define  NOMBRE_ARCHIVO "data1.txt"
#define NOVISITADO -1

//Para TDA.
struct Nodo {
    int destino;
    Nodo* sig;
};

//Para TDA Grafo.
class TDAGrafo {
    private:
        Nodo** ListaVecinoAdyacente; 
        int TotalNodos;
        int* conductores;
        int cantidadConductores;

    public:
        //Constructor.
        TDAGrafo(int cantidadNodos) {
        TotalNodos = cantidadNodos;
        conductores = nullptr; 

        ListaVecinoAdyacente = new Nodo*[TotalNodos + 1];
        for (int i = 0; i <= TotalNodos; ++i) {
            ListaVecinoAdyacente[i] = nullptr; // Inicializamos las listas vacías.
        }
    }

    /* ****
    * Tipo Función: void agregarArco
    ******
    * Resumen Función: Agrega un arco desde un nodo origen
    * hacia un nodo "destino" en la lista de adyacencia (ListaVecinoAdyacente).
    ******
    * Input :
    * int origen: Índice del nodo desde donde se origina el arco.
    * int destino: Índice del nodo hacia donde apunta el arco.
    ******
    * Returns :
    * No retorna nada, pero modifica la estructura ListaVecinoAdyacente.
    **** */

    void agregarArco(int origen, int destino) {
        Nodo* nuevo = new Nodo;
        nuevo->destino = destino;
        nuevo->sig = ListaVecinoAdyacente[origen]; // Insertar al inicio.
        ListaVecinoAdyacente[origen] = nuevo;
    } 
    
    /* ****
    * Tipo Función: setConductores
    ******
    * Resumen Función: carga y almacena la lista de los confuctores disponibles.
    ******
    * Input :
    * int* lista: Es un arreglo donde se guardan los conductores identificados.
    * int cant: Son la cantidad de conductores en el arreglo (lista como anteriormente le pusimos).
    ******
    * Returns :
    * No retorna nada, solo asigna memoria y copia la lista.
    **** */
   
    void setConductores(int* lista, int cant) {
        cantidadConductores = cant;
        conductores = new int[cant];
        for (int i = 0; i < cant; ++i) {
            conductores[i] = lista[i];
        }
    }
    int getCantidadNodos() const { return TotalNodos; }
    int getCantidadConductores() const { return cantidadConductores; }
    int getConductor(int i) const { return conductores[i]; }
    void setConductor(int i, int nodo) { conductores[i] = nodo; }

    /* ****
    * Tipo Función: void BFS
    ******
    * Resumen Función: Realiza un recorrido en anchura desde el nodo de inicio. Calcula la distancia mínima
    * en número de aristas desde el nodo de inicio a todos los demás, luego regustra el padre de cada nodo alcanzado.
    ******
    * Input :
    * int inicio: Es el nodo en donde comienza el recorrido BFS.
    * int* distancia: Arreglo en donde se guarda la distancia desde el nodo de inicio hasta cada nodo.
    * int* padre: Arreglo en donde se indica desde que nodo se llego a cada nodo.
    ******
    * Returns :
    * No retorna nada, solo modifica los arreglos "distancia" y "padre"
    **** */

    //Como se ocupa una lista de ady, se visita el nodo una vez O(n) y las aristas se recorren una sola vez O(a). Complejidad O(n + a).
    void BFS(int inicio, int* distancia, int* padre) {
    
        //Se inicializan los nodos.
        for (int i = 0; i <= TotalNodos; ++i) {
            distancia[i] = NOVISITADO; //Cuantos pasos hay desde inicio hasta el nodo[i].
            padre[i] = NOVISITADO;  //Desde que nodo se llego a nodo[i].
        }//O(n).

        int* Cola = new int[TotalNodos + 1]; //O(n).
        int head = 0;
        int fin = 0; //Quien llega al sgte elemento (El sgte lugar libre).

        distancia[inicio] = 0;
        Cola[fin++] = inicio;

        //Mientras la cola no este vacia.
        while (head < fin) {
            int actual = Cola[head++];
            Nodo* temp = ListaVecinoAdyacente[actual];
            while (temp != nullptr) {
                int vecino = temp->destino;
                if (distancia[vecino] == NOVISITADO) {
                    distancia[vecino] = distancia[actual] + 1;
                    padre[vecino] = actual;
                    Cola[fin++] = vecino;
                }
                temp = temp->sig;
            }//O(a).

        }

        delete[] Cola;
    }

    //Destructor para liberar memoria.
    //Dentro de la clase porque se llama nueva memoria desde aqui tb.
    ~TDAGrafo() {
        for (int i = 0; i <= TotalNodos; ++i) {
           Nodo* actual = ListaVecinoAdyacente[i];
            while (actual != nullptr) {
                Nodo* siguiente = actual->sig;
                delete actual;
                actual = siguiente;
            }
        }
        delete[] ListaVecinoAdyacente;
        if (conductores != nullptr) {
            delete[] conductores;
        }
    }
};

/* ****
    * Tipo Función: mostarCamino
    ******
    * Resumen Función: Imprime el camino desde el nodo de origen hasta el nodo de destino utilizando
    * información del arreglo padre, y si no hay camino imprime "{}".
    ******
    * Input :
    * int destino: Nodo destino del cual se reconstruye el arreglo.
    * int* padre: Arreglo donde padre[i] indica el nodo anterior a i en el camino.
    * int totalNodos: cantidad total de nodos en el grafo.
    ******
    * Returns :
    * No retorna valores, imprime por pantalla el camino en orden correcto.
    **** */

//Toma O(n).
void mostrarCamino(int destino, int* padre, int totalNodos) {
    int* camino = new int[totalNodos + 1];  //O(n).
    int longitud = 0;       //O(1).
    int actual = destino;   //O(1).

    // Construir camino desde destino hacia el origen.
    while (actual != NOVISITADO && longitud <= totalNodos) {
        camino[longitud++] = actual;
        actual = padre[actual];
    }//O(n).

    if (longitud == 0) {
        cout << "{}";
        delete[] camino;
        return;
    }//O(1).

    // Imprimir camino invertido.
    cout << "{";
    for (int i = longitud - 1; i >= 0; --i) {
        cout << camino[i];
        if (i != 0) cout << " , ";
    }//O(n).
    cout << "}";

    delete[] camino;    //O(1).
}

/* ****
    * Tipo Función: solicitarUber
    ******
    * Resumen Función: Busca el conductor más cercano al pasajero utilizando BFS. luego 
    * calcula el camino desde el conductor al pasajero y desde el pasajero al destino, y si
    * existe una ruta valida, imprime la ruta final y el costo total del viaje.
    ******
    * Input :
    * TDAGrafo& grafo: Grafo que contiene los nodos, aristas y posiciones de los conductores.
    * int pasajero: Nodo en donde se encuentran los pasajeros.
    * int destino: Nodo al que desea llegar el pasajero.
    ******
    * Returns :
    * No retorna valores, imprime la ruta y el costo por consola y actualiza la posición del 
    * conductor seleccionando el grafo.
    **** */

void solicitarUber(TDAGrafo& grafo, int pasajero, int destino) {
    int cantidadNodos = grafo.getCantidadNodos();               //O(1).
    int cantidadConductores= grafo.getCantidadConductores();    //O(1).

    int mejor = -1;       //O(1).
    int menorDist = 1e9; //Inicialmente una cantidad muy grande. O(1)

    for (int i = 0; i < cantidadConductores; ++i) { 
        int posConductor = grafo.getConductor(i); //O(1).
        int* DisDesdeConductor = new int [cantidadNodos + 1];           //O(n).
        int* CaminoConductor = new int [cantidadNodos + 1];             //O(n).
        grafo.BFS(posConductor, DisDesdeConductor, CaminoConductor);    //O(n+a), a= arcos.

        if(DisDesdeConductor[pasajero] != NOVISITADO && DisDesdeConductor[pasajero] < menorDist){
            mejor = i;
            menorDist = DisDesdeConductor[pasajero];
        }//O(1).
        delete[] DisDesdeConductor; //O(1).
        delete[] CaminoConductor;   //O(1).
    }//Como se repite i < cantidadConductores, O(c *(n+a)), c=cantidadConductores.

    if (mejor == -1){
        cout << "Ruta : {} - Costo : -1" << endl;
        return;
    }//O(1).

    int posConductor = grafo.getConductor(mejor); //O(1).

    // BFS desde el conductor al pasajero.
    int* distConductor = new int[cantidadNodos + 1];        //O(n).
    int* padreConductor = new int[cantidadNodos + 1];       //O(n).
    grafo.BFS(posConductor, distConductor, padreConductor); //O(n+a).

    if (distConductor[pasajero] == NOVISITADO) {
        cout << "Ruta : {} - Costo : -1" << endl;
        delete[] distConductor;
        delete[] padreConductor;
        return;
    }//O(1).

    // BFS desde el pasajero al destino.
    int* distPasajero = new int [cantidadNodos + 1];    //O(n).
    int* padrePasajero = new int[cantidadNodos + 1];    //O(n).
    grafo.BFS(pasajero, distPasajero, padrePasajero);   //O(n+a).

    //Si no hay un camino desde el pasajero al destino.
    if(distPasajero[destino] == NOVISITADO){
        cout << "Ruta : {} - Costo : -1" << endl;
        delete[] distConductor;
        delete[] padreConductor;
        delete[] distPasajero;
        delete[] padrePasajero;
        return;
    }//O(1).

    cout << "Ruta : ";
    mostrarCamino(destino, padrePasajero, cantidadNodos);   //O(n).
    cout << " - ";

    //Calculamos el costo total.
    int costo = 300 * distConductor[pasajero] + 500 * distPasajero[destino];    //O(1).
    cout << "Costo total del viaje: " << costo << endl;

    // Actualizar posición del conductor.
    grafo.setConductor(mejor, destino); //O(1).


    //Todos O(1) x 4.
    delete[] distPasajero; 
    delete[] padrePasajero;
    delete[] distConductor;
    delete[] padreConductor;
}


int main() {
    ifstream archivo(NOMBRE_ARCHIVO);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    int cantidadNodos;
    int cantidadArcos; 
    int cantidadConductores;
    archivo >> cantidadNodos >> cantidadArcos >> cantidadConductores;

    //Crear grafo usando el TDA.
    TDAGrafo grafo(cantidadNodos);

    //Leer los arcos y agregarlos al grafo.
    for (int i = 0; i < cantidadArcos; ++i) {
        int origen, destino;
        archivo >> origen >> destino;
        grafo.agregarArco(origen, destino);
    }

    // Leer conductores.
    int* PosConductores = new int[cantidadConductores]; //Arreglo dinámico para guardar los nodos donde están ubicados los conductores.
    for (int i = 0; i < cantidadConductores; ++i) {
        archivo >> PosConductores[i];
    }

    grafo.setConductores(PosConductores, cantidadConductores);

    int desde; 
    int hasta;
    while (true) {
        cout << "Ingrese viaje : ";
        cin >> desde >> hasta;
        if (desde == -1 && hasta == -1) break;

        solicitarUber(grafo, desde, hasta);
    }

    /*
    // Mostrar la matriz de adyacencia (listas)
    for (int i = 1; i <= cantidadNodos; ++i) {
        cout << "Nodo " << i << " conectado con: ";
        for (int j = 0; j < cantidadAdy[i]; ++j) {
            cout << ListaVecinoAdyacente[i][j] << " ";
        }
        cout << "\n";
    }

    // Mostrar conductores
    cout << "Conductores en nodos: ";
    for (int i = 0; i < cantidadConductores; ++i) {
        cout << PosConductores[i] << " ";
    }
    cout << endl;
    */

    // Liberar memoria dinámica.
    delete[] PosConductores;

    return 0;
}