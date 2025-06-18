#include <iostream>
#include <fstream>
using namespace std;

#define  NOMBRE_ARCHIVO "data1.txt"
//Para TDA
struct Nodo{
    int destino;
    Nodo *sig;
};




//Para TDA Grafo
class TDAGrafo {
private:
    int numNodos;

public:

    int cantidadNodos() const {
        return numNodos;
    }
};




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


    // Crear matriz dinámica para adyacencia
    int** VecinoAdyacente = new int*[cantidadNodos + 1]; //Como los nodos parten del 1 le sumamos uno para quedar con indices directos [1,40], sino seria [1,39].
    int* cantidadAdy = new int[cantidadNodos + 1]; //Arreglo para guardar, para cada nodo, la cantidad de vecinos adyacentes que tiene. 
    for (int i = 0; i <= cantidadNodos; ++i) {
        VecinoAdyacente[i] = new int[cantidadNodos + 1];  // Máximo vecinos igual a nodos
        cantidadAdy[i] = 0;
    }

    // Leer los arcos y llenar la lista de vecinos de cada nodo
    for (int i = 0; i < cantidadArcos; ++i) {
        int origen, destino;
        archivo >> origen >> destino;

        //Pone el nuevo vecino (el destino) en la siguiente posición disponible de la lista de vecinos de origen.
        VecinoAdyacente[origen][cantidadAdy[origen]] = destino;
        cantidadAdy[origen]++; //Aumenta la cantidad de nodos adyacentes
    }

    // Leer conductores
    int* PosConductores = new int[cantidadConductores]; //Arreglo dinámico para guardar los nodos donde están ubicados los conductores.
    for (int i = 0; i < cantidadConductores; ++i) {
        archivo >> PosConductores[i];
    }

    //BORRAR LUEGO
    /* 
    // Mostrar la matriz de adyacencia (listas)
    for (int i = 1; i <= cantidadNodos; ++i) {
        cout << "Nodo " << i << " conectado con: ";
        for (int j = 0; j < cantidadAdy[i]; ++j) {
            cout << adyacencia[i][j] << " ";
        }
        cout << "\n";
    }

    // Mostrar conductores
    cout << "Conductores en nodos: ";
    for (int i = 0; i < cantidadConductores; ++i) {
        cout << conductores[i] << " ";
    }
    cout << endl;
    */

    // Liberar memoria dinámica
    for (int i = 0; i <= cantidadNodos; ++i) {
        delete[] VecinoAdyacente[i];
    }
    delete[] VecinoAdyacente;
    delete[] cantidadAdy;
    delete[] PosConductores;

    return 0;
}