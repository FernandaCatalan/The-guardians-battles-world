#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <limits>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <unordered_map>

using namespace std;

// Estructura ciudad
struct Ciudad {
    string nombre;
    vector<string> guardianes;
    vector<string> ciudadConectada;   // Mapa de ciudades conectadas y la distancia
    Ciudad(string nombreCiudad){
        nombre = nombreCiudad;
    }

    Ciudad(){

    }
};

// Estructura para almacenar información detallada de un guardián
struct Guardian {
    string nombre;
    int nivelPoder;
    string maestro;
    string ciudad;
    bool esMaestro; 
};

// Arbol guardian
class NodoArbol {
public:
    Guardian guardian;
    vector<NodoArbol*> subordinados;

    NodoArbol(const Guardian& guard) : guardian(guard) {}

    ~NodoArbol() {
        for (NodoArbol* sub : subordinados) {
            delete sub;
        }
    }
};

class ArbolGuardianes {
private:
    NodoArbol* raiz;

public:
    ArbolGuardianes() : raiz(nullptr) {}

    ~ArbolGuardianes() {
        if (raiz != nullptr) {
            delete raiz;
        }
    }

    void agregarGuardian(const Guardian& guard) {
        if (raiz == nullptr) {
            raiz = new NodoArbol(guard);
        } else {
            agregarGuardianRecursivo(raiz, guard);
        }
    }

    void imprimirArbol() const {
        imprimirArbolRecursivo(raiz, 0);
    }

private:
    void agregarGuardianRecursivo(NodoArbol* nodo, const Guardian& guard) {
        if (nodo == nullptr) {
            return;
        }

        if (nodo->guardian.nombre == guard.maestro) {
            nodo->subordinados.push_back(new NodoArbol(guard));
        } else {
            for (NodoArbol* sub : nodo->subordinados) {
                agregarGuardianRecursivo(sub, guard);
            }
        }
    }

    void imprimirArbolRecursivo(const NodoArbol* nodo, int nivel) const {
        if (nodo == nullptr) {
            return;
        }

        for (int i = 0; i < nivel; ++i) {
            cout << "  ";
        }

        cout << "- " << nodo->guardian.nombre << endl;

        for (const NodoArbol* sub : nodo->subordinados) {
            imprimirArbolRecursivo(sub, nivel + 1);
        }
    }
};

// Definición de la estructura ResultadoBatalla 
struct ResultadoBatalla {
    string ganador;
    int puntosGanador;
};


vector<Guardian> leerGuardianesDesdeArchivo(const string& nombreArchivo, ArbolGuardianes& arbol) {
    vector<Guardian> guardianes;
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            Guardian guard;

            // Leer los elementos separados por comas
            getline(ss, guard.nombre, ',');
            ss >> guard.nivelPoder;
            ss.ignore();  // Ignorar la coma
            getline(ss, guard.maestro, ',');
            getline(ss, guard.ciudad, ',');
            ss >> boolalpha >> guard.esMaestro;

            // Agregar el guardián al vector
            guardianes.push_back(guard);

            // Agregar el guardián al árbol
            arbol.agregarGuardian(guard);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

    return guardianes;
}

// Función para leer las conexiones entre ciudades desde el archivo cities.conf
unordered_map<string, Ciudad> leerCiudadesDesdeArchivo(const string& nombreArchivo) {
    unordered_map<string, Ciudad> ciudades;
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string nombreCiudad, ciudadConectada;

            // Leer los elementos separados por comas
            getline(ss, nombreCiudad, ',');
            getline(ss, ciudadConectada, ',');

            // Verificar si las ciudades existen en el mapa
            if (ciudades.find(nombreCiudad) == ciudades.end()) {
                ciudades[nombreCiudad] = Ciudad(nombreCiudad);
            }
            if (ciudades.find(ciudadConectada) == ciudades.end()) {
                ciudades[ciudadConectada] = Ciudad(ciudadConectada);
            }

            // Agregar la conexión a la ciudad
            ciudades[nombreCiudad].ciudadConectada.push_back(ciudadConectada);
            ciudades[ciudadConectada].ciudadConectada.push_back(nombreCiudad);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

    return ciudades;
}

// Imprimir las ciudades
void impCiudad(const unordered_map<string, Ciudad>& ciudades) {
    for (const auto& par : ciudades) {
        const Ciudad& ciudad = par.second;
        cout << "Nombre: " << ciudad.nombre << endl;
        cout << "Conexiones: " << endl;

        for (const string& ciudadConectada : ciudad.ciudadConectada) {
            cout << "-" << ciudadConectada << endl;
        }

        cout << "-------------" << endl;
    }
}

// Función para mostrar el menú
int mostrarMenu() {
    int opcion;
    cout << "Menu:" << endl;
    cout << "  1. Ver la lista de candidatos." << endl;
    cout << "  2. Ver al guardian." << endl;
    cout << "  3. Conocer el reino." << endl;
    cout << "  4. Presenciar una batalla." << endl;
    cout << "  5. Salir." << endl;

    cout << "Seleccione una opcion (1-5): ";
    cin >> opcion;

    // Limpiar el buffer de entrada
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return opcion;
}

// Función para mostrar la lista de candidatos
void listaCandidatos(const vector<Guardian>& guardianes) {
    cout << "Lista de Candidatos:\n";

    // Contadores para asegurar que solo 1 tiene 100 y 3 tienen entre 90 y 99
    int candidato100 = 0;
    int candidatos90a99 = 0;

    // Recorrer los guardianes y obtener los candidatos
    for (const auto& nombreGuardian : guardianes) {
       if(nombreGuardian.nivelPoder>=90 && nombreGuardian.nivelPoder<=99){
            cout << "Detalles del guardian " << nombreGuardian.nombre << ":\n";
            cout << "Nivel de poder: " << nombreGuardian.nivelPoder << " puntos\n";
            cout << "Maestro: " << nombreGuardian.maestro << endl;
            cout << "Ciudad: " << nombreGuardian.ciudad << endl;
       }
    }
}


// Función para ver el detalle de un guardián
void verGuardian(const string& nombreGuardian, const unordered_map<string, Guardian>& detallesGuardianes) {
    // Buscar el guardián en los detalles
    auto it = detallesGuardianes.find(nombreGuardian);

    if (it != detallesGuardianes.end()) {
        // El guardián fue encontrado, imprimir detalles
        const Guardian& detalles = it->second;
        cout << "Detalles del guardian " << detalles.nombre << ":\n";
        cout << "Nivel de poder: " << detalles.nivelPoder << " puntos\n";
        cout << "Maestro: " << detalles.maestro << endl;
        cout << "Ciudad: " << detalles.ciudad << endl;

    } else {
        // El guardián no fue encontrado
        cout << "El guardian " << nombreGuardian << " no fue encontrado en la base de datos.\n";
    }
}

// Función para obtener la lista de candidatos
vector<Guardian> listaCandidatos(const unordered_map<string, Guardian>& guardianes) {
    vector<Guardian> candidatos;
    for (const auto& par : guardianes) {
        const Guardian& guard = par.second;
        if (guard.nivelPoder >= 90 && guard.nivelPoder <= 99 && !guard.esMaestro) {
            candidatos.push_back(guard);
        }
    }
    return candidatos;
}

string obtenerListaCandidatos(const vector<Guardian>& guardianes) {
    stringstream listaCandidatos;

    // Contadores para asegurar que solo 1 tiene 100 y 3 tienen entre 90 y 99
    int candidato100 = 0;
    int candidatos90a99 = 0;

    // Recorrer los guardianes y obtener los candidatos
    for (const auto& nombreGuardian : guardianes) {
        if (nombreGuardian.nivelPoder >= 90 && nombreGuardian.nivelPoder <= 99) {
            listaCandidatos << "Detalles del guardian " << nombreGuardian.nombre << ":\n";
            listaCandidatos << "Nivel de poder: " << nombreGuardian.nivelPoder << " puntos\n";
            listaCandidatos << "Maestro: " << nombreGuardian.maestro << endl;
            listaCandidatos << "Ciudad: " << nombreGuardian.ciudad << endl;
            listaCandidatos << "------------------------------\n";
        }
    }

    // Devolver la cadena de texto resultante
    return listaCandidatos.str();
}

// Función para mostrar la información de un guardián
void verGuardian(const Guardian& guard) {
    cout << "Nombre: " << guard.nombre << endl;
    cout << "Nivel de Poder: " << guard.nivelPoder << endl;
    cout << "Maestro: " << (guard.maestro) << endl;
    cout << "Ciudad: " << (guard.ciudad) << endl;
}


/*
// Para seleccionar el guardian para jugar
Guardian seleccionarGuardianRetador(const listaCandidatos& candidatos) {
    // Mostrar la lista de candidatos disponibles para la selección
    cout << "Lista de Guardianes Disponibles:" << endl;
    for (const Guardian& candidato : candidatos) {
        cout << "Nombre: " << candidato.nombre << " | Ciudad: " << candidato.ciudad << endl;
    }

    // Solicitar al usuario que elija un guardián retador
    string nombreRetador;
    cout << "Ingrese el nombre del Guardián que desea como retador: ";
    cin >> nombreRetador;

    // Buscar el guardián en la lista de candidatos
    for (const Guardian& candidato : candidatos) {
        if (candidato.nombre == nombreRetador) {
            return candidato;
        }
    }

    // Manejar el caso en que el nombre ingresado no coincida con ningún candidato
    cerr << "Guardián no encontrado en la lista de candidatos. Seleccionando el primer guardián por defecto." << endl;
    return candidatos.front();
}

// Ir a una ciudad a combatir
string seleccionarCiudadDestino(const conexionesCiudades& ciudades) {
    // Mostrar la lista de ciudades disponibles para la selección
    cout << "Lista de Ciudades Disponibles:" << endl;
    for (const string& ciudad : ciudades) {
        cout << "- " << ciudad << endl;
    }

    // Solicitar al usuario que elija una ciudad destino
    string ciudadDestino;
    cout << "Ingrese el nombre de la ciudad destino: ";
    cin >> ciudadDestino;

    // Verificar si la ciudad destino está en la lista de ciudades
    auto it = find(ciudades.begin(), ciudades.end(), ciudadDestino);
    if (it != ciudades.end()) {
        return ciudadDestino;
    } else {
        cerr << "Ciudad no encontrada en la lista de ciudades. Seleccionando la primera ciudad por defecto." << endl;
        return ciudades.front();
    }
}

// Ir a la ciudad
void viajarACiudad(ArbolGuardianes& arbol, const string& ciudadDestino) {
    // Obtener la ciudad actual del guardián retador
    string ciudadActual = arbol.obtenerCiudadGuardianRetador();

    // Verificar si la ciudad destino es diferente de la ciudad actual
    if (ciudadDestino != ciudadActual) {
        // Realizar acciones de viaje, actualizar la ubicación del guardián, etc.
        arbol.actualizarCiudadGuardianRetador(ciudadDestino);

        // Mostrar mensaje de viaje exitoso
        cout << "Viajaste exitosamente a " << ciudadDestino << ".\n";
    } else {
        // Mostrar mensaje de que ya estás en esa ciudad
        cout << "Ya te encuentras en " << ciudadDestino << ". No es necesario viajar.\n";
    }
}

// Batalla
void batallarConCampeonesLocales(ArbolGuardianes& arbol, const vector<Guardian>& campeonesLocales) {
    // Seleccionar un campeón local aleatorio
    srand(time(0));
    int indiceCampeon = rand() % campeonesLocales.size();
    Guardian campeonLocal = campeonesLocales[indiceCampeon];

    // Obtener el guardián retador
    Guardian& retador = arbol.obtenerGuardianRetador();

    // Calcular la probabilidad de ganar
    bool retadorGana = (rand() % 10) < 4; // Probabilidad de 4/10

    // Actualizar puntos según el resultado de la batalla
    if (retadorGana) {
        if (campeonLocal.esMaestro) {
            retador.nivelPoder += 5; // Ganar a un Maestro
        } else {
            retador.nivelPoder += 3; // Ganar a un aprendiz
        }
    }

    // Mostrar el resultado de la batalla
    cout << "¡Batalla concluida!\n";
    cout << "Guardián Retador: " << retador.nombre << endl;
    cout << "Campeón Local: " << campeonLocal.nombre << endl;
    cout << (retadorGana ? "¡Ganaste la batalla!" : "¡Perdiste la batalla!") << endl;
    cout << "Puntos del Guardián Retador: " << retador.nivelPoder << endl;
}

// Para actualizar los puntos
void actualizarPuntosDespuesDeVictoria(Guardian& retador, bool esMaestro) {
    if (esMaestro) {
        retador.nivelPoder += 5; // Ganar a un Maestro
    } else {
        retador.nivelPoder += 3; // Ganar a un aprendiz
    }
}

void actualizarListaDeCandidatos(vector<Guardian>& candidatos, const Guardian& retador) {
    // Buscar al guardián retador en la lista de candidatos
    auto it = find_if(candidatos.begin(), candidatos.end(), [&retador](const Guardian& g) {
        return g.nombre == retador.nombre;
    });

    // Actualizar los puntos si se encontró al guardián retador
    if (it != candidatos.end()) {
        it->puntos = retador.nivelPoder;
    } else {
        cerr << "Error: No se encontró al guardián retador en la lista de candidatos." << endl;
    }

    // Ordenar la lista de candidatos según los puntos
    sort(candidatos.begin(), candidatos.end(), [](const Guardian& a, const Guardian& b) {
        return a.nivelPoder > b.nivelPoder;
    });
}

// Funcion para presenciar una batalla
void presenciarBatalla(Guardian& retador, Ciudad& ciudadActual, ArbolGuardianes& arbol, listaCandidatos& candidatos) {
    // 1. Selección del Guardián Retador
    retador = seleccionarGuardianRetador(candidatos);

    // 2. Viajar a una Ciudad
    Ciudad ciudadDestino = seleccionarCiudadDestino(ciudadActual);
    viajarACiudad(ciudadDestino, retador, arbol);

    // 3. Batalla con Campeones Locales
    bool victoria = batallarConCampeonesLocales(retador, ciudadDestino);

    // 4. Actualizar Puntos y Lista de Candidatos
    if (victoria) {
        actualizarPuntosDespuesDeVictoria(retador);
    } else {
        // Implementar lógica para manejar la derrota si es necesario
    }

    // Reflejar cambios en la lista de candidatos
    actualizarListaDeCandidatos(candidatos, retador);
} */


int main() {

    ArbolGuardianes arbol;

    // Leer ciudades desde el archivo cities.conf
    unordered_map<string, Ciudad> conexionesCiudades = leerCiudadesDesdeArchivo("cities.conf");

    // Leer detalles de los guardianes desde el archivo guardians.conf
    vector<Guardian> listaGuardianes = leerGuardianesDesdeArchivo("guardians.conf", arbol);

    unordered_map<string, int> nivelesDePoder;

    arbol.imprimirArbol();

    int opcion;
    string nombreGuardian;
    Guardian guardianElegido;

    do {
        opcion = mostrarMenu();

        // Realizar acciones según la opción seleccionada
        switch (opcion) {
            case 1:
                // Ver la lista de candidatos
                listaCandidatos(listaGuardianes);
                break;
            case 2:
                // Ver al guardián
                cout << "Ingrese el nombre del guardian: " << endl;
                getline(cin, nombreGuardian);

                for(const Guardian guardian: listaGuardianes){
                    if(guardian.nombre == nombreGuardian){
                        guardianElegido = guardian;
                        break;
                    }
                }

                verGuardian(guardianElegido);
                break;
            case 3:
                // Conocer el reino
                impCiudad(conexionesCiudades);
                break;
            case 4:
                // Presenciar una batalla
                cout << "En la siguiente actualizacion sera agregado...";
                break;
            case 5:
                cout << "Saliendo del programa... ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion no valida, seleccione una opcion del 1 al 5" << endl;
                break;
        }

    } while (opcion != 5);


    return 0;
}