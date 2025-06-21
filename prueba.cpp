#include <iostream>
#include <fstream>
using namespace std;

#define  NOMBRE_ARCHIVO "data1.txt"
#define NOVISITADO -1



//Para TDA
struct Nodo{
    int destino;
    Nodo *sig;
};




//Para TDA Grafo
class TDAGrafo {
    private:
        int** ListaVecinoAdyacente; //Matriz dinámica
        int* cantidadAdy; //Cantidad vecinos nodo correspondiente
        int TotalNodos;
        int* conductores;
        int cantidadConductores;

    public:
        //Constructor
        TDAGrafo(int cantidadNodos) {
        TotalNodos = cantidadNodos;
        conductores = nullptr; 

        ListaVecinoAdyacente = new int*[TotalNodos + 1];
        cantidadAdy = new int[TotalNodos + 1];

        for (int i = 0; i <= TotalNodos; ++i) {
            ListaVecinoAdyacente[i] = new int[TotalNodos + 1];
            cantidadAdy[i] = 0;
        }
    }

    //Agrega un arco entre dos nodos
    void agregarArco(int origen, int destino) {
        ListaVecinoAdyacente[origen][cantidadAdy[origen]] = destino; //Guarda un vecino en la lista de vecinos del nodo
        cantidadAdy[origen]++;
    } 
    
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
    
    void BFS(int inicio, int* distancia, int* padre) {
        //Distancia: cuantos pasos hay desde incio hasta el nodo[i]
        //Padre: desde que nodo se llego a nodo[i]
        //Se inicializan los nodos
        for (int i = 0; i <= TotalNodos; ++i) {
            distancia[i] = NOVISITADO; 
            padre[i] = NOVISITADO; 
        }

        int* Cola = new int[TotalNodos + 1];
        int head = 0; //Indice head (Quien va a salir)
        int fin = 0; //Quien llega al sgte elemento

        distancia[inicio] = 0;
        Cola[fin++] = inicio;

        //Mientras la cola no este vacia 
        while (head < fin) {
            int actual = Cola[head++];
            for (int i = 0; i < cantidadAdy[actual]; ++i) { //Se recorren todos los vecinos del nodo actual
                int vecino = ListaVecinoAdyacente[actual][i];
                if (distancia[vecino] == NOVISITADO) {
                    distancia[vecino] = distancia[actual] + 1;
                    padre[vecino] = actual;
                    Cola[fin++] = vecino;
                }
            }
        }

        delete[] Cola;
    }

    //Destructor para liberar memoria
    //Dentro de la clase porque se llama nueva memoria desde aqui tb
    ~TDAGrafo() {
        for (int i = 0; i <= TotalNodos; ++i) {
            delete[] ListaVecinoAdyacente[i];
        }
        delete[] ListaVecinoAdyacente;
        delete[] cantidadAdy;
        if (conductores != nullptr) {
            delete[] conductores; 
        }
    
    }
    

};

void mostrarCamino(int destino, int* padre, int totalNodos) {
    int* camino = new int[totalNodos + 1];
    int longitud = 0;
    int actual = destino;

    // Construir camino desde destino hacia el origen
    while (actual != NOVISITADO && longitud <= totalNodos) {
        camino[longitud++] = actual;
        actual = padre[actual];
    }

    if (longitud == 0) {
        cout << "{}";
        delete[] camino;
        return;
    }

    // Imprimir camino invertido
    cout << "{";
    for (int i = longitud - 1; i >= 0; --i) {
        cout << camino[i];
        if (i != 0) cout << " , ";
    }
    cout << "}";

    delete[] camino;
}


void solicitarUber(TDAGrafo& grafo, int pasajero, int destino) {
    int cantidadNodos = grafo.getCantidadNodos();
    int cantidadConductores= grafo.getCantidadConductores();

    int* distanciaPasajero = new int[cantidadNodos + 1]; //Distancia desde el pasajero a todos los nodos
    int* padrePasajero = new int[cantidadNodos + 1]; //Camino desde el pasajero
    grafo.BFS(pasajero, distanciaPasajero, padrePasajero);

    int mejor = -1;
    int menorDist = 1e9;
    for (int i = 0; i < cantidadConductores; ++i) {
        int posConductor = grafo.getConductor(i);
        if (distanciaPasajero[posConductor] != NOVISITADO && distanciaPasajero[posConductor] < menorDist) {
            mejor = i; //indice del conductor en el arreglo
            menorDist = distanciaPasajero[posConductor]; // Distamcia más corta encontrada
        }
    }
    //Si no se encuentra ningun conductor disponible
    if (mejor == -1 || distanciaPasajero[destino] == NOVISITADO){
        cout << "Ruta : {} - Costo : -1" << endl;
        delete[] distanciaPasajero;
        delete[] padrePasajero;
        return;
    }


    int posConductor = grafo.getConductor(mejor);
    
    int* distConductor = new int[cantidadNodos + 1];
    int* padreConductor = new int[cantidadNodos + 1];
    grafo.BFS(posConductor, distConductor, padreConductor);

    


    cout << "Ruta : ";
    mostrarCamino(destino, padrePasajero, cantidadNodos);
    cout << " - ";
    cout << "Pasos conductor -> pasajero: " << distConductor[pasajero] << endl;
    cout << "Pasos pasajero -> destino: " << distanciaPasajero[destino] << endl;

    int costo = 300 * distConductor[pasajero] + 500 * distanciaPasajero[destino];
    cout << "Costo total del viaje: " << costo << endl;

    // Actualizar posición del conductor
    grafo.setConductor(mejor, destino);

    delete[] distanciaPasajero;
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
    //BORRAR LUEGO
    cout<< "Nodos: " << cantidadNodos <<endl;
    cout<< "Arcos: "<< cantidadArcos << endl;
    cout<< "Conductores: " << cantidadConductores << endl;


    //Crear grafo usando el TDA
    TDAGrafo grafo(cantidadNodos);

    //Leer los arcos y agregarlos al grafo
    for (int i = 0; i < cantidadArcos; ++i) {
        int origen, destino;
        archivo >> origen >> destino;
        grafo.agregarArco(origen, destino);
    }

    // Leer conductores
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

    //BORRAR LUEGO
    // Mostrar el grafo
    //grafo.mostrar();
    

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

    // Liberar memoria dinámica
    delete[] PosConductores;

    return 0;
}