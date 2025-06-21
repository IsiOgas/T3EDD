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