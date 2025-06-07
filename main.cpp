#include <iostream>
using namespace std;

struc Nodo {
    int id_Proceso;
    string NombreProceso;
    string Estado;
    string Prioridad
    Nodo* siguiente;
    
    Nodo(int id, string nomPro, string Es, string Prio) {
        id_Proceso = id;
        NombreProceso = nomPro;
        Estado = Es;
        Prioridad = Prio;
        siguiente = NULL;
    }
};
// Eliminar proceso por ID
void eliminarProceso() {
    int id;
    cout << "Ingrese el ID del proceso a eliminar: ";
    cin >> id;

    if (inicio == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }

    Nodo* actual = inicio;
    Nodo* anterior = NULL;

    while (actual != NULL && actual->id_Proceso != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "Proceso no encontrado.\n";
        return;
    }

    if (anterior == NULL) {
        inicio = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    cout << "Proceso eliminado correctamente.\n";
}

// Modificar prioridad de un proceso por ID
void modificarPrioridad() {
    int id;
    cout << "Ingrese ID del proceso a modificar: ";
    cin >> id;
    cin.ignore();

    Nodo* actual = inicio;
    while (actual != NULL) {
        if (actual->id_Proceso == id) {
            string nuevaPrioridad;
            cout << "Ingrese nueva prioridad: ";
            getline(cin, nuevaPrioridad);
            actual->Prioridad = nuevaPrioridad;
            cout << "Prioridad actualizada correctamente.\n";
            return;
        }
        actual = actual->siguiente;
    }

    cout << "Proceso no encontrado.\n";
}

// Submenú de la opción 1: Gestor de Procesos
void gestorDeProcesos() {
    int opcion;
    do {
        cout << "\n--- Gestor de Procesos ---\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Buscar proceso\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: insertarProceso(); break;
            case 2: eliminarProceso(); break;
            case 3: buscarProceso(); break;
            case 4: modificarPrioridad(); break;
            case 5: cout << "Volviendo al menu principal...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);
}


//Menu principal
int main(){
    int opcion;
    do {
        cout << "\n************\n";
        cout << "         MENU PRINCIPAL      \n";
        cout << "**********\n";
        cout << "1. Gestor de Proceso\n";
        cout << "2. Planificador de CPU \n";
        cout << "3. Gestor de Memoria\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: gestorDeProcesos(); break;
            case 2: /* Planificador de CPU */ break;
            case 3: /* Gestor de Memoria */ break;
            case 4: cout << "Saliendo del programa...\n"; break;
            default: cout << "Error, ingrese una opcion valida\n";
        }

    } while (opcion != 4);

    return 0;
}
