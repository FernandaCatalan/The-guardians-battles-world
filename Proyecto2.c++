#include <iostream>
using namespace std;

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