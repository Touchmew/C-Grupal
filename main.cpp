#include <iostream>
using namespace std;

struct Nodo {
    int id_Proceso;
    string NombreProceso;
    string Estado;
    string Prioridad;
    Nodo* siguiente;
    
    Nodo(int id, string nomPro, string Es, string Prio) {
        id_Proceso = id;
        NombreProceso = nomPro;
        Estado = Es;
        Prioridad = Prio;
        siguiente = NULL;
    }
};
// Puntero principal para la lista de procesos
Nodo* inicio = NULL;
// Struct para el Gestor de Memoria
struct BloqueMemoria{
	int idProceso;
	double tamano;
	BloqueMemoria* siguiente;
};
// puntero principal para la cima de la pila
BloqueMemoria* cima = NULL;
// -------- FUNCIONES --------

// Insertar un nuevo proceso al final
void insertarProceso() {
    int id;
    string nombre, estado, prioridad;

    cout << "Ingrese ID del proceso: ";
    cin >> id;
    cin.ignore();
    cout << "Ingrese nombre del proceso: ";
    getline(cin, nombre);
    cout << "Ingrese estado del proceso: ";
    getline(cin, estado);
    cout << "Ingrese prioridad del proceso: ";
    getline(cin, prioridad);

    Nodo* nuevo = new Nodo(id, nombre, estado, prioridad);

    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        Nodo* actual = inicio;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    cout << "Proceso insertado correctamente.\n";
}
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
// Buscar proceso por ID o nombre
void buscarProceso() {
    int opcion;
    cout << "Buscar por:\n1. ID\n2. Nombre\nSeleccione una opcion: ";
    cin >> opcion;
    cin.ignore();

    if (opcion == 1) {
        int id;
        cout << "Ingrese ID: ";
        cin >> id;

        Nodo* actual = inicio;
        while (actual != NULL) {
            if (actual->id_Proceso == id) {
                cout << "Proceso encontrado: " << actual->NombreProceso
                     << " | Estado: " << actual->Estado
                     << " | Prioridad: " << actual->Prioridad << endl;
                return;
            }
            actual = actual->siguiente;
        }

    } else if (opcion == 2) {
        string nombre;
        cout << "Ingrese nombre: ";
        getline(cin, nombre);

        Nodo* actual = inicio;
        while (actual != NULL) {
            if (actual->NombreProceso == nombre) {
                cout << "Proceso encontrado: ID " << actual->id_Proceso
                     << " | Estado: " << actual->Estado
                     << " | Prioridad: " << actual->Prioridad << endl;
                return;
            }
            actual = actual->siguiente;
        }

    } else {
        cout << "Opcion invalida.\n";
        return;
    }

    cout << "Proceso no encontrado.\n";
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

//---------Pilas---------------



//---------Colas---------------




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

// Submenú de la opción 2. Planificador de CPU

//Submenú de la opcion 3. Gestor de Memoria
void gestorDeMemoria(){
	    int opcion;
    do {
        cout << "\n--- Gestor de Memoria ---\n";
        cout << "1. Asignacion de memoria a procesos (push)\n";
        cout << "2. Liberacion de memoria (pop)\n";
        cout << "3. Verificacion del estado actual de la memoria\n";
        cout << "4. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion){
 			case 1: AsignarMemoria(); break;
 			case 2: LiberarMemoria(); break;
 			case 3: MostrarMemoria(); break;
 			case 4: cout << "Volviendo al menu principal...\n"; break;
 			default: cout << "Opcion invalida.\n";
		}
    }while (opcion != 4);
}

//Menu principal
int main(){
    int opcion;
    do {
        cout << "\n***************************\n";
        cout << "         MENU PRINCIPAL      \n";
        cout << "*****************************\n";
        cout << "1. Gestor de Proceso\n";
        cout << "2. Planificador de CPU \n";
        cout << "3. Gestor de Memoria\n";
        cout << "4. Salir\n";
        cout <<"------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: gestorDeProcesos(); break;
            case 2: /* Planificador de CPU */ break;
            case 3: gestorDeMemoria(); break;
            case 4: cout << "Saliendo del programa...\n"; break;
            default: cout << "Error, ingrese una opcion valida\n";
        }

    } while (opcion != 4);

    return 0;
}
