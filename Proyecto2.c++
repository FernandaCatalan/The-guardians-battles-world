#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

// Estructura ciudad
struct Ciudad {
    string nombre;
};

// Estructura para la batalla
struct ResultadoBatalla {
    string nombreGuardian;
    int puntos;
};

// Clase grafo
class Grafo {
public:
    // Estructura guardián
    struct Guardian {
        string nombre;
        int nivelPoder;
        string maestro;
        int indiceCiudad; // Índice de la ciudad en el grafo
    };

    // Constructor con parámetro para el número de vértices (ciudades)
    Grafo(int numVertices);

    // Métodos para agregar ciudad, conexión, guardian, y otros
    void agregarCiudad(const Ciudad& ciudad);
    void agregarConexion(int indiceCiudadOrigen, int indiceCiudadDestino);
    int obtenerIndiceCiudad(const string& nombreCiudad) const;
    void agregarGuardian(const Guardian& guardian);
    void mostrarListaAdyacencia();
    void mostrarMatrizAdyacencia();
    void mostrarGuardianes() const;
    bool hayCamino(int indiceCiudadOrigen, int indiceCiudadDestino, std::vector<bool>& visitado) const;
    bool existeCamino(const string& nombreCiudadOrigen, const string& nombreCiudadDestino);
    void agregarNuevoCamino(const string& nombreCiudadOrigen, const string& nombreCiudadDestino);
    void mostrarCaminosExistentes() const;
    bool existeCaminoEntreCiudades(const string& nombreCiudadOrigen, const string& nombreCiudadDestino) const;
    vector<Grafo::Guardian>& obtenerGuardianes();
    const vector<Ciudad>& obtenerCiudades() const;
    const vector<Grafo::Guardian>& obtenerGuardianes() const;

    // Constructor por defecto (sin parámetros)
    Grafo() : numVertices(0) {

    }

private:
    int numVertices;
    vector<Ciudad> ciudades;
    vector<list<int>> listaAdyacencia;
    vector<vector<int>> matrizAdyacencia;
    vector<Grafo::Guardian> guardianes;
};

// Devuelve una referencia constante a la lista de ciudades
const vector<Ciudad>& Grafo::obtenerCiudades() const {
    return ciudades;
}

// Devuelve una referencia constante al vector de guardianes
const vector<Grafo::Guardian>& Grafo::obtenerGuardianes() const {
    return guardianes;
}

// Constructor con parámetro para el número de vértices (ciudades)
Grafo::Grafo(int numVertices) : numVertices(numVertices) {
    listaAdyacencia.resize(numVertices);
    matrizAdyacencia.resize(numVertices, vector<int>(numVertices, 0));
}

// Método para agregar una ciudad al grafo
void Grafo::agregarCiudad(const Ciudad& ciudad) {
    ciudades.push_back(ciudad);
}

// Método para agregar una conexión entre dos ciudades en el grafo
void Grafo::agregarConexion(int indiceCiudadOrigen, int indiceCiudadDestino) {
    listaAdyacencia[indiceCiudadOrigen].push_back(indiceCiudadDestino);
    matrizAdyacencia[indiceCiudadOrigen][indiceCiudadDestino] = 1;
}

// Método para obtener el índice de una ciudad dado su nombre
int Grafo::obtenerIndiceCiudad(const string& nombreCiudad) const {
    for (int i = 0; i < numVertices; ++i) {
        if (ciudades[i].nombre == nombreCiudad) {
            return i;
        }
    }
    return -1;
}

// Método para agregar un guardián al grafo
void Grafo::agregarGuardian(const Guardian& guardian) {
    guardianes.push_back(guardian);
}

// Método para mostrar la lista de adyacencia del grafo
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

// Método para mostrar la matriz de adyacencia del grafo
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

// Método para mostrar la información de los guardianes del grafo
void Grafo::mostrarGuardianes() const {
    cout << "Guardianes:\n";
    cout << setw(15) << "Nombre" << setw(15) << "Nivel de Poder" << setw(15) << "Maestro" << setw(15) << "Ciudad\n";
    for (const auto& guardian : guardianes) {
        cout << setw(15) << guardian.nombre << setw(15) << guardian.nivelPoder << setw(15) << guardian.maestro << setw(15) << ciudades[guardian.indiceCiudad].nombre << "\n";
    }
}

// Método recursivo para verificar si hay un camino entre dos ciudades
bool Grafo::hayCamino(int indiceCiudadOrigen, int indiceCiudadDestino, std::vector<bool>& visitado) const {
    if (indiceCiudadOrigen == indiceCiudadDestino) {
        return true;
    }

    visitado[indiceCiudadOrigen] = true;

    for (int ciudad : listaAdyacencia[indiceCiudadOrigen]) {
        if (!visitado[ciudad] && hayCamino(ciudad, indiceCiudadDestino, visitado)) {
            return true;
        }
    }

    return false;
}

// Método para verificar si existe un camino entre dos ciudades
bool Grafo::existeCamino(const string& nombreCiudadOrigen, const string& nombreCiudadDestino) {
    int indiceCiudadOrigen = obtenerIndiceCiudad(nombreCiudadOrigen);
    int indiceCiudadDestino = obtenerIndiceCiudad(nombreCiudadDestino);

    if (indiceCiudadOrigen == -1 || indiceCiudadDestino == -1) {
        cerr << "Ciudad no encontrada.\n";
        return false;
    }

    vector<bool> visitado(numVertices, false);
    return hayCamino(indiceCiudadOrigen, indiceCiudadDestino, visitado);
}

// Método para agregar un nuevo camino entre dos ciudades
void Grafo::agregarNuevoCamino(const string& nombreCiudadOrigen, const string& nombreCiudadDestino) {
    int indiceCiudadOrigen = obtenerIndiceCiudad(nombreCiudadOrigen);
    int indiceCiudadDestino = obtenerIndiceCiudad(nombreCiudadDestino);

    if (indiceCiudadOrigen != -1 && indiceCiudadDestino != -1) {
        agregarConexion(indiceCiudadOrigen, indiceCiudadDestino);
        cout << "Se ha agregado un nuevo camino entre " << nombreCiudadOrigen << " y " << nombreCiudadDestino << ".\n";
    } else {
        cerr << "Una o ambas ciudades no existen\n";
    }
}

// Método para mostrar los caminos existentes en el grafo
void Grafo::mostrarCaminosExistentes() const {
    cout << "Caminos existentes:\n";
    for (int i = 0; i < numVertices; ++i) {
        for (int ciudad : listaAdyacencia[i]) {
            cout << ciudades[i].nombre << " -> " << ciudades[ciudad].nombre << "\n";
        }
    }
}

// Método para verificar si existe un camino entre dos ciudades
bool Grafo::existeCaminoEntreCiudades(const string& nombreCiudadOrigen, const string& nombreCiudadDestino) const {
    int indiceCiudadOrigen = obtenerIndiceCiudad(nombreCiudadOrigen);
    int indiceCiudadDestino = obtenerIndiceCiudad(nombreCiudadDestino);

    if (indiceCiudadOrigen == -1 || indiceCiudadDestino == -1) {
        cerr << "Ciudad no encontrada\n";
        return false;
    }

    vector<bool> visitado(numVertices, false);
    return hayCamino(indiceCiudadOrigen, indiceCiudadDestino, visitado);
}

// Función para ver la lista de candidatos en el rango de nivel de poder especificado
void verListaCandidatos(const Grafo& grafo) {
    cout << "Lista de candidatos:\n";

    const vector<Ciudad>& ciudades = grafo.obtenerCiudades();
    const vector<Grafo::Guardian>& guardianes = grafo.obtenerGuardianes();

    if (guardianes.empty()) {
        cout << "No hay candidatos disponibles\n";
    } else {
        cout << setw(15) << "Nombre" << setw(15) << "Nivel de Poder" << setw(15) << "Maestro" << setw(15) << "Ciudad\n";
        for (const auto& guardian : guardianes) {
            if (guardian.nivelPoder >= 90 && guardian.nivelPoder <= 99) {
                const Ciudad& ciudadGuardian = ciudades[guardian.indiceCiudad];
                cout << setw(15) << guardian.nombre << setw(15) << guardian.nivelPoder << setw(15) << guardian.maestro << setw(15) << ciudadGuardian.nombre << "\n";
            }
        }

        // Verificación si no hay candidatos en el rango especificado
        bool hayCandidatos = false;
        for (const auto& guardian : guardianes) {
            if (guardian.nivelPoder >= 90 && guardian.nivelPoder <= 99) {
                hayCandidatos = true;
                break;
            }
        }

        if (!hayCandidatos) {
            cout << "No hay candidatos con nivel de poder entre 90 y 99\n";
        }
    }
}

// Función para ver la información detallada de un guardián específico
void verGuardian(const Grafo& grafo) {
    cout << "Ver al guardian:\n";

    const vector<Ciudad>& ciudades = grafo.obtenerCiudades();
    const vector<Grafo::Guardian>& guardianes = grafo.obtenerGuardianes();

    if (guardianes.empty()) {
        cout << "No hay guardianes disponibles\n";
        return;
    }

    // Solicitar el nombre del guardián al usuario
    string nombreGuardian;
    cout << "Ingrese el nombre del guardian que desea ver: ";
    cin.ignore();  // Limpiar el buffer de entrada
    getline(cin, nombreGuardian);

    // Buscar el guardián por nombre
    bool encontrado = false;
    for (const auto& guardian : guardianes) {
        if (guardian.nombre == nombreGuardian) {
            encontrado = true;
            // Mostrar información detallada sobre el guardián
            const Ciudad& ciudadGuardian = ciudades[guardian.indiceCiudad];
            cout << "Informacion sobre el guardian:\n";
            cout << setw(15) << "Nombre" << setw(15) << "Nivel de Poder" << setw(15) << "Maestro" << setw(15) << "Ciudad\n";
            cout << setw(15) << guardian.nombre << setw(15) << guardian.nivelPoder << setw(15) << guardian.maestro << setw(15) << ciudadGuardian.nombre << "\n";
            break;  // Salir del bucle una vez encontrado el guardián
        }
    }

    if (!encontrado) {
        cout << "El guardian con el nombre \"" << nombreGuardian << "\" no se encontro\n";
    }
}

// Función para mostrar información general del reino (número de ciudades y guardianes)
void conocerReino(const Grafo& grafo) {
    cout << "Informacion del reino:\n";

    const vector<Ciudad>& ciudades = grafo.obtenerCiudades();
    const vector<Grafo::Guardian>& guardianes = grafo.obtenerGuardianes();

    if (ciudades.empty() && guardianes.empty()) {
        cout << "El reino esta vacio\n";
        return;
    }

    // Mostrar el número de ciudades en el reino
    cout << "Numero de ciudades en el reino: " << ciudades.size() << "\n";

    // Mostrar la lista de ciudades en el reino
    cout << "Lista de ciudades en el reino:\n";
    for (const auto& ciudad : ciudades) {
        cout << "- " << ciudad.nombre << "\n";
    }

    // Mostrar el número de guardianes en el reino
    cout << "Numero de guardianes en el reino: " << guardianes.size() << "\n";
}

// Función para simular la presencia en una batalla
void presenciarBatalla(Grafo& grafo) {
    cout << "Presenciar una batalla:\n";

    // Selección del guardián retador
    cout << "Seleccione un guardián retador:\n";
    grafo.mostrarGuardianes();

    string nombreGuardianRetador;
    cout << "Ingrese el nombre del guardian retador: ";
    cin.ignore();
    getline(cin, nombreGuardianRetador);

    // Obtener el índice del guardián retador
    int indiceGuardianRetador = -1;
    for (size_t i = 0; i < grafo.obtenerGuardianes().size(); ++i) {
        if (grafo.obtenerGuardianes()[i].nombre == nombreGuardianRetador) {
            indiceGuardianRetador = i;
            break;
        }
    }

    if (indiceGuardianRetador == -1) {
        cerr << "Guardian retador no encontrado\n";
        return;
    }

    Grafo::Guardian& guardianRetador = grafo.obtenerGuardianes()[indiceGuardianRetador];

    // Seleccionar ciudad para la batalla
    cout << "Seleccione una ciudad para la batalla:\n";
    grafo.mostrarListaAdyacencia();

    string nombreCiudadBatalla;
    cout << "Ingrese el nombre de la ciudad para la batalla: ";
    getline(cin, nombreCiudadBatalla);

    int indiceCiudadBatalla = grafo.obtenerIndiceCiudad(nombreCiudadBatalla);
    if (indiceCiudadBatalla == -1) {
        cerr << "Ciudad no encontrada\n";
        return;
    }

    // Obtener la probabilidad de ganar
    srand(static_cast<unsigned int>(time(nullptr)));
    int probabilidad = rand() % 10;  // Número aleatorio entre 0 y 9

    // Calcular el resultado de la batalla
    int puntosGanados;
    if (probabilidad < 4) {
        cout << "¡El guardian retador ha perdido la batalla!\n";
        puntosGanados = 0;
    } else {
        cout << "¡El guardian retador ha ganado la batalla!\n";
        puntosGanados = (guardianRetador.maestro == "Maestro") ? 5 : 3;
    }

    // Actualizar puntos y mostrar cambios en la lista de candidatos
    guardianRetador.nivelPoder += puntosGanados;
    grafo.mostrarGuardianes();

    // Guardar el resultado de la batalla
    ResultadoBatalla resultado;
    resultado.nombreGuardian = nombreGuardianRetador;
    resultado.puntos = puntosGanados;

    // Puedes almacenar este resultado en una lista/vector si deseas llevar un historial de batallas
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
    const vector<Grafo::Guardian>& guardianes = grafo.obtenerGuardianes();

    for (int i = 0; i < numGuardianes; ++i) {
        Grafo::Guardian nuevoGuardian;
        archivo >> nuevoGuardian.nombre >> nuevoGuardian.nivelPoder >> nuevoGuardian.maestro;

        // Validaciones
        if (nuevoGuardian.nivelPoder == 100) {
            // Solo un guardián puede tener 100
            if (grafo.obtenerGuardianes().size() > 0) {
                cerr << "Solo un guardian puede tener un nivel de poder de 100\n";
                return 1;
            }
        } else if (nuevoGuardian.nivelPoder >= 90 && nuevoGuardian.nivelPoder <= 99) {
            // Solo tres guardianes pueden tener entre 90 y 99
            if (grafo.obtenerGuardianes().size() >= 3) {
                cerr << "Solo tres guardianes pueden tener un nivel de poder entre 90 y 99\n";
                return 1;
            }
        } else {
            cerr << "Nivel de poder no valido\n";
            return 1;
        }

        string ciudadGuardian;
        archivo.ignore();  // Ignorar la coma
        getline(archivo, ciudadGuardian);
        int indiceCiudadGuardian = grafo.obtenerIndiceCiudad(ciudadGuardian);

        if (indiceCiudadGuardian == -1) {
            cerr << "La ciudad del guardian no existe\n";
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
                verListaCandidatos(grafo);
                break;
            case 2:
                verGuardian(grafo);
                break;
            case 3:
                conocerReino(grafo);
                break;
            case 4:
                presenciarBatalla(grafo);
                break;
            case 5:
                std::cout << "Saliendo del programa...¡Hasta luego!\n";
                break;
            default:
                std::cout << "Opcion no valida, ingrese una opcion valida\n";
        }

    } while (opcion != 5);

    return 0;
}