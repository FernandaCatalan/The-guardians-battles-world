#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

struct Ciudad {
    string nombre;
};

class Grafo {
public:
    struct Guardian {
        string nombre;
        int nivelPoder;
        string maestro;
        int indiceCiudad; // Índice de la ciudad en el grafo
    };

    Grafo(int numVertices);

    void agregarCiudad(const Ciudad& ciudad);
    void agregarConexion(int indiceCiudadOrigen, int indiceCiudadDestino);
    int obtenerIndiceCiudad(const string& nombreCiudad) const;
    void agregarGuardian(const Guardian& guardian);
    void mostrarListaAdyacencia();
    void mostrarMatrizAdyacencia();
    void mostrarGuardianes();

    vector<Guardian> guardianes; // Mover la declaración de guardianes aquí

private:
    int numVertices;
    vector<Ciudad> ciudades;
    vector<list<int>> listaAdyacencia;

    vector<vector<int>> matrizAdyacencia;
};

Grafo::Grafo(int numVertices) : numVertices(numVertices) {
    listaAdyacencia.resize(numVertices);
    matrizAdyacencia.resize(numVertices, vector<int>(numVertices, 0));
}

void Grafo::agregarCiudad(const Ciudad& ciudad) {
    ciudades.push_back(ciudad);
}

void Grafo::agregarConexion(int indiceCiudadOrigen, int indiceCiudadDestino) {
    listaAdyacencia[indiceCiudadOrigen].push_back(indiceCiudadDestino);
    matrizAdyacencia[indiceCiudadOrigen][indiceCiudadDestino] = 1;
}

int Grafo::obtenerIndiceCiudad(const string& nombreCiudad) const {
    for (int i = 0; i < numVertices; ++i) {
        if (ciudades[i].nombre == nombreCiudad) {
            return i;
        }
    }
    return -1;  // Devuelve -1 si la ciudad no se encuentra
}

void Grafo::agregarGuardian(const Guardian& guardian) {
    guardianes.push_back(guardian);
}

void Grafo::mostrarListaAdyacencia() {
    cout << "Lista de Adyacencia:\n";
    for (int i = 0; i < numVertices; ++i) {
        cout << ciudades[i].nombre << ": ";
        for (int ciudad : listaAdyacencia[i]) {
            cout << ciudades[ciudad].nombre << " ";
        }
        cout << "\n";
    }
}

void Grafo::mostrarMatrizAdyacencia() {
    cout << setw(10) << "Ciudad";
    for (const auto& ciudad : ciudades) {
        cout << setw(10) << ciudad.nombre;
    }
    cout << "\n";

    for (int i = 0; i < numVertices; ++i) {
        cout << setw(10) << ciudades[i].nombre;
        for (int j = 0; j < numVertices; ++j) {
            cout << setw(10) << matrizAdyacencia[i][j];
        }
        cout << "\n";
    }
}

void Grafo::mostrarGuardianes() {
    cout << "Guardianes:\n";
    cout << setw(15) << "Nombre" << setw(15) << "Nivel de Poder" << setw(15) << "Maestro" << setw(15) << "Ciudad\n";
    for (const auto& guardian : guardianes) {
        cout << setw(15) << guardian.nombre << setw(15) << guardian.nivelPoder << setw(15) << guardian.maestro << setw(15) << ciudades[guardian.indiceCiudad].nombre << "\n";
    }
}



void verListaCandidatos() {
    // Implementa la lógica para ver la lista de candidatos
    cout << "Lista de candidatos:\n";
    
}

void verGuardian() {
    // Implementa la lógica para ver al guardián
    cout << "Guardian:\n";
    
}

void conocerReino() {
    // Implementa la lógica para conocer el reino
    cout << "Informacion del reino:\n";
    
}

void presenciarBatalla() {
    // Implementa la lógica para presenciar una batalla
    cout << "Batalla:\n";
   
}

int main() {

    ifstream archivo("guardians.conf");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo guardians.conf\n";
        return 1;
    }

    int numCiudades;
    archivo >> numCiudades;

    Grafo grafo(numCiudades);

    archivo.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

    // Leer ciudades
    for (int i = 0; i < numCiudades; ++i) {
        string linea;
        getline(archivo, linea);
        Ciudad nuevaCiudad;

        // Separar la línea en nombre de la ciudad y ciudad conectada
        stringstream ss(linea);
        getline(ss, nuevaCiudad.nombre, ',');
        grafo.agregarCiudad(nuevaCiudad);
    }

    // Leer conexiones
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string ciudadOrigen, ciudadDestino;
        getline(ss, ciudadOrigen, ',');
        getline(ss, ciudadDestino);

        int indiceCiudadOrigen = grafo.obtenerIndiceCiudad(ciudadOrigen);
        int indiceCiudadDestino = grafo.obtenerIndiceCiudad(ciudadDestino);

        if (indiceCiudadOrigen != -1 && indiceCiudadDestino != -1) {
            grafo.agregarConexion(indiceCiudadOrigen, indiceCiudadDestino);
        }
    }

    // Leer guardianes
    int numGuardianes;
    archivo >> numGuardianes;

    for (int i = 0; i < numGuardianes; ++i) {
        Grafo::Guardian nuevoGuardian;
        archivo >> nuevoGuardian.nombre >> nuevoGuardian.nivelPoder >> nuevoGuardian.maestro;

        // Validaciones
        if (nuevoGuardian.nivelPoder == 100) {
            // Solo un guardián puede tener 100
            if (grafo.guardianes.size() > 0) {
                cerr << "Error: Solo un guardián puede tener un nivel de poder de 100.\n";
                return 1;
            }
        } else if (nuevoGuardian.nivelPoder >= 90 && nuevoGuardian.nivelPoder <= 99) {
            // Solo tres guardianes pueden tener entre 90 y 99
            if (grafo.guardianes.size() >= 3) {
                cerr << "Error: Solo tres guardianes pueden tener un nivel de poder entre 90 y 99.\n";
                return 1;
            }
        } else {
            cerr << "Error: Nivel de poder no válido.\n";
            return 1;
        }

        string ciudadGuardian;
        archivo >> ciudadGuardian;
        int indiceCiudadGuardian = grafo.obtenerIndiceCiudad(ciudadGuardian);

        if (indiceCiudadGuardian == -1) {
            cerr << "Error: La ciudad del guardián no existe.\n";
            return 1;
        }

        nuevoGuardian.indiceCiudad = indiceCiudadGuardian;
        grafo.agregarGuardian(nuevoGuardian);
    }

    archivo.close();

    // Mostrar la lista de adyacencia, la matriz de adyacencia y los guardianes
    grafo.mostrarListaAdyacencia();
    grafo.mostrarMatrizAdyacencia();
    grafo.mostrarGuardianes();


    int opcion;

    do {
        // Mostrar el menú
        cout << "Menu:\n";
        cout << "1. Ver la lista de candidatos\n";
        cout << "2. Ver al guardian\n";
        cout << "3. Conocer el reino\n";
        cout << "4. Presenciar una batalla\n";
        cout << "5. Salir\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        // Procesar la opción
        switch (opcion) {
            case 1:
                verListaCandidatos();
                break;
            case 2:
                verGuardian();
                break;
            case 3:
                conocerReino();
                break;
            case 4:
                presenciarBatalla();
                break;
            case 5:
                std::cout << "Saliendo del programa...¡Hasta luego!\n";
                break;
            default:
                std::cout << "Opcion no valida, ngrese una opcion valida.\n";
        }

    } while (opcion != 5);

    return 0;
}