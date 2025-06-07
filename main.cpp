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
	string Nombre;
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
    cout << "Buscar por:\n1. ID\n2. Nombre\nSeleccione una opcion: ";//te da un menu pequenio para buscar por id o nombre
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
// asignar la memoria especifica
void AsignarMemoria(){
 	int id;
 	double tamano;
	string Nombre;
    cout << "Ingrese ID del proceso: ";
    cin >> id;

    cout << "Ingrese el nombre del proceso: ";
    cin >> Nombre;

    cout << "Ingrese tamaño de memoria (mg): ";
    cin >> tamano;

    BloqueMemoria* nuevo = new BloqueMemoria;
    nuevo->idProceso = id;
    nuevo->Nombre = Nombre;
    nuevo->tamano = tamano;
    nuevo->siguiente = cima;
    cima = nuevo;

    cout << ">> Memoria asignada al proceso: " <<Nombre<<" Id " << id << " ( con un tamaño de" << tamano << " mg) | ("<< tamano /1000 <<" Gb)\n";
}

void LiberarMemoria(){
    if (cima == NULL) {
        cout << ">> No hay bloques de memoria para liberar.\n";
        return;
    }

    BloqueMemoria* temp = cima;
    cima = cima->siguiente;
    cout << ">> Memoria liberada del proceso " << temp->idProceso <<" " << temp->Nombre << " (" << temp->tamano << " mg)\n";
    delete temp;
}

void MostrarMemoria(){
	if (cima == NULL) {
        cout << ">> La pila de memoria está vacía.\n";
        return;
    }

    cout << ">> Estado actual de la memoria (de mas reciente a mas antigua):\n";
    BloqueMemoria* actual = cima;
    while (actual != NULL) {
      	 cout << "   - Proceso ID: " << actual->idProceso << " Nombre:" << actual->Nombre  <<", tamano: " << actual->tamano << " mg\n";
        actual = actual->siguiente;
    }
}
//---------Colas---------------
struct NodoCola {
    int id_Proceso;
    string NombreProceso;
    string Prioridad;
    int tiempoEjecucion;
    NodoCola* siguiente;
    
    NodoCola(int id, string nomPro, string prio, int tiempo) {
        id_Proceso = id;
        NombreProceso = nomPro;
        Prioridad = prio;
        tiempoEjecucion = tiempo;
        siguiente = NULL;
    }
};
// Punteros para la cola
NodoCola* frente = NULL;
NodoCola* final = NULL;

// Funcion para verifiaar si la cola esta vacia
bool colaVacia() {
    return frente == NULL;
}
// Encolar proceso segun prioridad (Alta, Media, Baja)
void encolarProceso() {
    int id, tiempo;
    string nombre, prioridad;
    
    cout << "Ingrese ID del proceso: ";
    cin >> id;
    cin.ignore();
    cout << "Ingrese nombre del proceso: ";
    getline(cin, nombre);
    cout << "Ingrese prioridad (Alta/Media/Baja): ";
    getline(cin, prioridad);
    cout << "Ingrese tiempo de ejecucion (segundos): ";
    cin >> tiempo;
    
    NodoCola* nuevo = new NodoCola(id, nombre, prioridad, tiempo);
// si la cola esta vacia
    if (colaVacia()) {
        frente = final = nuevo;
    } 
    // insertar segun prioridad
    else {
        // si tiene prioridad alta, insertarlo al frente
        if (prioridad == "Alta") {
            // buscar posicion correcta entre las prioridades altas
            if (frente->Prioridad != "Alta") {
                nuevo->siguiente = frente;
                frente = nuevo;
            } else {
                // insertar entre otros procesos de prioridad alta
                NodoCola* actual = frente;
                NodoCola* anterior = NULL;
                
                while (actual != NULL && actual->Prioridad == "Alta") {
                    anterior = actual;
                    actual = actual->siguiente;
                }
                
                if (anterior == NULL) {
                    nuevo->siguiente = frente;
                    frente = nuevo;
                } else {
                    anterior->siguiente = nuevo;
                    nuevo->siguiente = actual;
                    if (actual == NULL) final = nuevo;
                }
            }
// si tiene prioridad media
        else if (prioridad == "Media") {
            NodoCola* actual = frente;
            NodoCola* anterior = NULL;
            // buscar posición después de prioridades altas
            while (actual != NULL && actual->Prioridad == "Alta") {
                anterior = actual;
                actual = actual->siguiente;
            }
            
            // insertar entre procesos de prioridad media
            while (actual != NULL && actual->Prioridad == "Media") {
                anterior = actual;
                actual = actual->siguiente;
            }
            if (anterior == NULL) {
                nuevo->siguiente = frente;
                frente = nuevo;
            } else {
                anterior->siguiente = nuevo;
                nuevo->siguiente = actual;
                if (actual == NULL) final = nuevo;
            }
        }
// Prioridad baja 
        else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }
    
    cout << "Proceso encolado correctamente.\n";
}

// Desencolar y ejecutar proceso
void desencolarProceso() {
    if (colaVacia()) {
        cout << "No hay procesos en la cola de ejecucion.\n";
        return;
    }
    
    NodoCola* procesoEjecutar = frente;
    
    cout << "\n--- Ejecutando Proceso ---\n";
    cout << "ID: " << procesoEjecutar->id_Proceso << endl;
    cout << "Nombre: " << procesoEjecutar->NombreProceso << endl;
    cout << "Prioridad: " << procesoEjecutar->Prioridad << endl;
    cout << "Tiempo de ejecucion: " << procesoEjecutar->tiempoEjecucion << " segundos\n";
    cout << "Proceso ejecutado exitosamente.\n";
    
    frente = frente->siguiente;
    if (frente == NULL) {
        final = NULL;
    }
    
    delete procesoEjecutar;
}
// *** Visualización de la cola actual ***



// Submenu del Planificador de CPU
void planificadorCPU() {
    int opcion;
    do {
        cout << "\n--- Planificador de CPU ---\n";
        cout << "1. Encolar proceso\n";
        cout << "2. Ejecutar siguiente proceso\n";
        cout << "3. Visualizar cola de procesos\n";
        cout << "4. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: encolarProceso(); break;
            case 2: desencolarProceso(); break;
            case 3: 
                // *** Visualizacion de la cola actual***



		    
                // visualizarCola(); 
                cout << "Funcionalidad pendiente - Falta ";
                break;
            case 4: cout << "Volviendo al menu principal...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}


// Submenu de la opción 1: Gestor de Procesos
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

// Submenu de la opción 2. Planificador de CPU

//Submenu de la opcion 3. Gestor de Memoria
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
            case 2: planificadorCPU(); break;
            case 3: gestorDeMemoria(); break;
            case 4: cout << "Saliendo del programa...\n"; break;
            default: cout << "Error, ingrese una opcion valida\n";
        }

    } while (opcion != 4);

    return 0;
}
