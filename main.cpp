#include <iostream>
#include <fstream> //se utiliza para crear, abrir, leer y escribir datos en archivos
#include <sstream> // permite tratar una cadena como flujo
#include <string> // permite declarar variables tipo std::string
#include <ctime> // acceder a funciones que manipulan la fecha y la hora local
#include <clocale>        

// ==== Prototipos de funciones ====
void guardarProcesos();

using namespace std;
//----Nodo de la lista -- 

struct Nodo {
    int id_Proceso;
    string NombreProceso;
    string Estado;
    string Prioridad;
    string fechaCreacion;
    Nodo* siguiente;
    
    Nodo(int id, string nomPro, string Es, string Prio) {
        id_Proceso = id;
        NombreProceso = nomPro;
        Estado = Es;
        Prioridad = Prio;
        siguiente = NULL;
	// Obtener fecha y hora actual
        time_t now = time(NULL);
        fechaCreacion = ctime(&now);
        // Elimina salto de línea final
	if (!fechaCreacion.empty() && fechaCreacion[fechaCreacion.length() - 1] == '\n') {
    		fechaCreacion.erase(fechaCreacion.length() - 1);
	}
    }
};

// Puntero principal para la lista de procesos

Nodo* inicio = NULL;

// --------------------- Funciones de Persistencia de listas  ---------------------

void guardarProcesos() {
    ofstream archivo("procesos.txt"); //crea un flijo de salida para escribir en un archivo txt
    if (!archivo) {  //verifica si el archivo se abre correctamente
		cerr << "Error al abrir procesos.txt.\n"; 
		return; 
	}
    //recorre las listas enlazadas comenzando desde el nodo inicio
    for (Nodo* act = inicio; act; act = act->siguiente) {
        // Escribimos los datos de cada proceso en el archivo, separados por '|' 
        archivo << act->id_Proceso        << '|'
                << act->NombreProceso     << '|'
                << act->Estado            << '|'
                << act->Prioridad         << '|'
                << act->fechaCreacion     << '\n';
    }
  // Cerramos el archivo una vez que todos los procesos han sido guardados
    archivo.close();
    cout << "Procesos guardados correctamente.\n";
}
//carga los procesos guardados en el archivo txt
void cargarProcesos() {
    ifstream archivo("procesos.txt");//abre el archivo txt
    if (!archivo.good()) {
	cout << "(Primera ejecución) No se encontraron procesos guardados.\n";
	return; //sale de la funcion si no encuentra el archico a leer
    }
    string linea;
	//lee el archivo linea por linea
    while (getline(archivo, linea)) {
    	
        if (linea.empty()) continue;
	// Se utiliza un stringstream para dividir la línea en campos separados por '|'
        stringstream ss(linea);
        string idStr, nombre, estado, prioridad, fecha;
	 // Extraemos cada campo individualmente
        getline(ss, idStr,     '|');
        getline(ss, nombre,    '|');
        getline(ss, estado,    '|');
        getline(ss, prioridad, '|');
        getline(ss, fecha);                // puede estar vacía en archivos antiguos
	// Convertimos el ID de string a entero
        int id;
		stringstream ss_id(idStr);
		ss_id >> id;

        Nodo* nuevo = new Nodo(id, nombre, estado, prioridad);
        if (!fecha.empty()) nuevo->fechaCreacion = fecha;   // conserva la fecha de creacion

        /* inserta al final de la lista */
        if (!inicio) {
		inicio = nuevo;
	}else {
		// Si ya hay elementos, recorremos hasta el final para insertar
		Nodo* a = inicio; 
		while (a->siguiente) a = a->siguiente; 
		a->siguiente = nuevo; 
    	}
    }

    archivo.close();
    cout << "Procesos cargados correctamente.\n";
}

// -------- FUNCIONES DE LISTAS --------

// Insertar un nuevo proceso al final

void insertarProceso() {
    int id;
    string nombre, estado, prioridad;
    // Solicita al usuario que ingrese el ID del nuevo proceso
    cout << "Ingrese ID del proceso: ";
    cin >> id;
    cin.ignore(); // Limpia el buffer

    // Verificar si el ID ya existe
    Nodo* actual = inicio;
    while (actual != NULL) {
        if (actual->id_Proceso == id) {
            cout << "Error: Ya existe un proceso con ese ID.\n";
            return;
        }
        actual = actual->siguiente; // Avanza al siguiente nodo
    }

    cout << "Ingrese nombre del proceso: ";
    getline(cin, nombre);
    cout << "Ingrese estado del proceso(Activo/Inactivo/Terminado): ";
    getline(cin, estado);
    cout << "Ingrese prioridad del proceso(Baja/Media/Alta): ";
    getline(cin, prioridad);
	
   // Crea un nuevo nodo con los datos ingresados
    Nodo* nuevo = new Nodo(id, nombre, estado, prioridad);
	
// Inserta el nodo en la lista enlazada
    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        actual = inicio;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente; // Conecta el último nodo al nuevo
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
	//te da un menu pequenio para buscar por id o nombre
    cin >> opcion;
    cin.ignore();

    if (opcion == 1) {
        int id;
        cout << "Ingrese ID: ";
        cin >> id;

        Nodo* actual = inicio;
        while (actual != NULL) {
            if (actual->id_Proceso == id) {
		    // Si encuentra el ID, muestra los detalles del proceso
                cout << "Proceso encontrado: " << actual->NombreProceso
                     << " | Estado: " << actual->Estado
                     << " | Prioridad: " << actual->Prioridad << endl;
                return;
            }
            actual = actual->siguiente; // Continúa con el siguiente nodo
        }

    } else if (opcion == 2) {
        string nombre;
        cout << "Ingrese nombre: ";
        getline(cin, nombre);

        Nodo* actual = inicio;
        while (actual != NULL) {
		 // Si encuentra el nombre, muestra los detalles del proceso
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
//---- Mostrar proceso con la fecha de registro
void mostrarProcesosConFecha() {
    if (inicio == NULL) {
        cout << "No hay procesos registrados.\n";
        return;
    }

    Nodo* actual = inicio;
    cout << "\n--- Lista de Procesos con Fecha de Creación ---\n";
    while (actual != NULL) {
        cout << "ID: " << actual->id_Proceso
             << " | Nombre: " << actual->NombreProceso
             << " | Estado: " << actual->Estado
             << " | Prioridad: " << actual->Prioridad
             << " | Fecha de creación: " << actual->fechaCreacion << endl;
        actual = actual->siguiente;
    }
}

void cambiarEstadoProcesoPorID() {
    int id;
    cout << "Ingrese el ID del proceso que desea cambiar de estado: ";
    cin >> id;

    Nodo* actual = inicio;

    while (actual != NULL) {
        if (actual->id_Proceso == id) {
            cout << "Estado actual del proceso '" << actual->NombreProceso
                 << "' (ID: " << actual->id_Proceso << "): "
                 << actual->Estado << endl;

            cout << "Ingrese el nuevo estado (Activo / Inactivo / Terminado): ";
            string nuevoEstado;
            cin.ignore(); // limpiar buffer
            getline(cin, nuevoEstado);

            actual->Estado = nuevoEstado;

            guardarProcesos(); // Se guarda el cambio en el archivo

            cout << "El estado del proceso ha sido actualizado a '" << nuevoEstado << "' correctamente." << endl;
            return;
        }
        actual = actual->siguiente;
    }

    cout << "No se encontró un proceso con el ID proporcionado." << endl;
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

// Persistencia --------------

void guardarCola() {
    ofstream archivo("cola.txt");
    if (archivo.is_open()) {
        NodoCola* actual = frente;
	// Recorre todos los nodos de la cola    
        while (actual != NULL) {
            archivo << actual->id_Proceso << "|"
                    << actual->NombreProceso << "|"
                    << actual->Prioridad << "|"
                    << actual->tiempoEjecucion << "\n";
            actual = actual->siguiente; // Avanza al siguiente nodo
        }
        archivo.close();
        cout << "Cola guardada  exitosamente.\n";
    } else {
        cerr << "Error al abrir archivo para guardar cola.\n";
    }
}

void cargarCola() {
    ifstream archivo("cola.txt");
    
    if (archivo.is_open()) {
        string linea;
	// Lee el archivo línea por línea
        while (getline(archivo, linea)){
		stringstream ss(linea);
		string idStr, nombre, prioridad, tiempoStr;
		getline(ss, idStr, '|');
		getline(ss, nombre, '|');
		getline(ss, prioridad, '|');
		getline(ss, tiempoStr, '|');
		// Convierte los campos numéricos de string a int
		int id;
		stringstream ssId(idStr);
		ssId >> id;
		
		int tiempo;
		stringstream ssTiempo(tiempoStr);
		ssTiempo >> tiempo;
	    // Inserta el nodo en la cola
            NodoCola* nuevo = new NodoCola(id, nombre, prioridad, tiempo);
            nuevo->siguiente = NULL;

            if (frente == NULL) {
                frente = final = nuevo; // Si la cola está vacía, este nodo es el primero y el último
            } else {
                final->siguiente = nuevo; // Lo enlaza al final
                final = nuevo;		// Actualiza el final
            }
        }
        archivo.close();
        cout << "Cola cargada exitosamente \n";
    } else {
        cerr << "No se pudo abrir para cargar.\n";
    }
}

void verificarArchivoCola() {
    ifstream archivo("cola.txt");
    if (!archivo.is_open()) {
        ofstream nuevo("cola.txt");
        if (nuevo.is_open()) {
            cout << "Archivo 'cola.txt' creado.\n";
            nuevo.close();
        } else {
            cerr << "No se pudo crear 'cola.txt'.\n";
        }
    } else {
        archivo.close();
    }
}


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
// ----- Visualización de la cola actual ------

void visualizarCola() {
    if (colaVacia()) {
        cout << "No hay procesos en la cola.\n";
        return;
    }
    NodoCola* actual = frente;
    cout << "ID: " << actual->id_Proceso
             << " | Nombre: " << actual->NombreProceso
             << " | Prioridad: " << actual->Prioridad
             << " | Tiempo: " << actual->tiempoEjecucion << " s\n";
        actual = actual->siguiente; 
}

//---------Pilas---------------

// Struct para el Gestor de Memoria
struct BloqueMemoria{
	int idProceso;
	double tamano;
	string Nombre;
	BloqueMemoria* siguiente;
};
// puntero principal para la cima de la pila
BloqueMemoria* cima = NULL;

// --------Persistencia de datos---------------
// Función para guardar la pila en un archivo
void guardarPila() {
    ofstream archivo("pila.txt");// Abre el archivo para escritura
    if (!archivo) { cerr << "Error al abrir pila.txt.\n"; return; }

    BloqueMemoria* actual = cima;// Comienza desde la cima de la pila
    while (actual) {
        archivo << actual->idProceso << '|'
                << actual->Nombre << '|'
                << actual->tamano << '\n';
        actual = actual->siguiente;
    }
    cout << "Pila guardada.\n";
}
// Función para cargar la pila desde un archivo
void cargarPila() {
    ifstream archivo("pila.txt"); // Abre el archivo para lectura
    if (!archivo.good()) {
        cout << "Sin datos en la pila guardados.\n";
        return;
    }

    // Vaciar pila actual si hay
    while (cima) {
        BloqueMemoria* aux = cima;
        cima = cima->siguiente;
        delete aux;
    }

    BloqueMemoria* base = NULL; // último nodo de la pila cargada
    BloqueMemoria* ultimo = NULL; // puntero para insertar al final

    string linea;
    while (getline(archivo, linea)) {
	    if (linea.empty()) continue;
	    stringstream ss(linea);
	    string idStr, nombre, tamanoStr;
	    getline(ss, idStr, '|');
	    getline(ss, nombre, '|');
	    getline(ss, tamanoStr);
	    
	    if (idStr.empty() || tamanoStr.empty()) {
	            cout << "Línea malformada: " << linea << endl;
		    continue;  // salta esta línea 
	    }
	    int id;
	    stringstream ssId(idStr);
	    ssId >> id;
	    double tamano;
	    stringstream ssTam(tamanoStr);
	    ssTam >> tamano;
	    // Crea un nuevo nodo de memoria con los datos leídos
	    BloqueMemoria* nodo = new BloqueMemoria;
	    nodo->idProceso = id;
	    nodo->Nombre = nombre;
	    nodo->tamano = tamano;
	    nodo->siguiente = NULL;
	    // Inserta el nodo al final de la lista temporal
	    if (base == NULL) { 
		    base = nodo;       
	            ultimo = nodo;
	    } else {
	            ultimo->siguiente = nodo;
	            ultimo = nodo;
	    }
    }
	// Revertir la lista para convertirla en pila
	BloqueMemoria* prev = NULL;
	BloqueMemoria* current = base;
	BloqueMemoria* next = NULL;
	// Invierte los punteros de la lista
	while (current != NULL) {
		next = current->siguiente;
		current->siguiente = prev;
		prev = current;
		current = next;
	}
	cima = prev; // ahora cima apunta a la cima real de la pila
    	archivo.close();
	cout << "Pila cargada correctamente.\n";
}

// asignar la memoria especifica
int siguienteID = 1;
const double MEMORIA = 32000;// Memoria total disponible (en mg)
double memoriaUtilizada = 0;
// Función para asignar memoria a un proceso
void AsignarMemoria(){
 	double tamano;
	string Nombre;
 	int id = siguienteID++;

    cout << "Ingrese el nombre del proceso: ";
    cin >> Nombre;

    cout << "Ingrese tamaño de memoria (mg): ";
    cin >> tamano;
// Verifica si hay suficiente memoria disponible
    if (memoriaUtilizada + tamano > MEMORIA) {
        cout << ">> No hay suficiente memoria disponible para asignar " << tamano << " MB.\n";
        return;
    }

  // Crea un nuevo bloque de memoria
    BloqueMemoria* nuevo = new BloqueMemoria;
    nuevo->idProceso = id; // Asigna el ID al nuevo bloque
    nuevo->Nombre = Nombre;
    nuevo->tamano = tamano;
    nuevo->siguiente = cima;// Enlaza el nuevo bloque a la cima actual
    cima = nuevo; // Actualiza la cima

    memoriaUtilizada += tamano; // Actualizar memoria utilizada
    double memoriaRestante = MEMORIA - memoriaUtilizada;// Calcula la memoria restante
    double porcentajeRestante = (memoriaRestante / MEMORIA) * 100;// Porcentaje de memoria restante
    
    cout << ">> Memoria asignada al proceso: " << Nombre << " Id " << id << " (con un tamano de " << tamano << " mg) | (" << tamano / 1000 << " Gb)\n";
    cout << ">> Quedan " << porcentajeRestante << "% de memoria disponible.\n";
}
// Función para liberar memoria de un proceso
void LiberarMemoria(){
    if (cima == NULL) {// Verifica si la pila está vacía
        cout << ">> No hay bloques de memoria para liberar.\n";
        return;
    }

    BloqueMemoria* temp = cima;// Almacena el bloque a liberar
    cima = cima->siguiente;
	siguienteID--;// Decrementa el ID para la próxima asignación
    memoriaUtilizada -= temp->tamano;
    cout << ">> Memoria liberada del proceso " << temp->idProceso <<" " << temp->Nombre << " (" << temp->tamano << " mg)\n";
    delete temp;// Libera la memoria del bloque
}
// Función para mostrar el estado actual de la memoria
void MostrarMemoria(){
	if (cima == NULL) { // Verifica si la pila está vacía
        cout << ">> La pila de memoria esta vacia.\n";
        return;
    }

    cout << ">> Estado actual de la memoria (de mas reciente a mas antigua):\n";
    BloqueMemoria* actual = cima;// Comienza desde la cima de la pila
    while (actual != NULL) {// Recorre todos los bloques de memoria
      	 cout << "   - Proceso ID: " << actual->idProceso << " Nombre:" << actual->Nombre  <<", tamano: " << actual->tamano << " mg\n";
        actual = actual->siguiente;// Avanza al siguiente bloque
    }
    double memoriaRestante = MEMORIA - memoriaUtilizada;
    double porcentajeRestante = (memoriaRestante / MEMORIA) * 100;
    cout << ">> Quedan " << porcentajeRestante << "% de memoria disponible.\n";
}



//--------- SUB MENUS --------------------------

// Submenu de la opción 1: Gestor de Procesos

void gestorDeProcesos() {
    int opcion;
    do {
	cout << "\n======================================\n";
        cout << "\n--- Gestor de Procesos ---\n";
        cout << "|    1. Insertar proceso\n";
        cout << "|    2. Eliminar proceso\n";
        cout << "|    3. Buscar proceso\n";
        cout << "|    4. Modificar prioridad\n";
	cout << "|    5. Mostrar procesos con fecha\n";
        cout << "|    6. Cambiar estado de un proceso\n";
        cout << "|    7. Volver al menu principal\n";
        cout << "|    Seleccione una opcion: ";
	cout << "\n======================================\n";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: insertarProceso(); break;
            case 2: eliminarProceso(); break;
            case 3: buscarProceso(); break;
            case 4: modificarPrioridad(); break;
	    case 5: mostrarProcesosConFecha(); break;
	    case 6: cambiarEstadoProcesoPorID();break;
	    case 7 : cout << "Volviendo al menu principal...\n"; break; 
	    default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 7);
}

// Submenu de la opción 2. Planificador de CPU
void planificadorCPU() {
    int opcion;
    do {
	cout << "\n======================================\n";
        cout << "\n--- Planificador de CPU ---\n";
        cout << "|    1. Encolar proceso\n";
        cout << "|    2. Ejecutar siguiente proceso\n";
        cout << "|    3. Visualizar cola de procesos\n";
        cout << "|    4. Volver al menu principal\n";
        cout << "|    Seleccione una opcion: ";
	cout << "\n======================================\n";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: encolarProceso(); break;
            case 2: desencolarProceso(); break;
            case 3: visualizarCola(); break;
            case 4: cout << "Volviendo al menu principal...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}
//Submenu de la opcion 3. Gestor de Memoria
void gestorDeMemoria(){
	    int opcion;
    do {
        cout << "\n+--------------------------------------------+\n";
	cout << "¦             Gestor de Memoria              ¦\n";
	cout << "¦--------------------------------------------¦\n";
	cout << "¦  1. Asignación de memoria a procesos (push)¦\n";
	cout << "¦  2. Liberación de memoria (pop)            ¦\n";
	cout << "¦  3. Ver estado actual de la memoria        ¦\n";
	cout << "¦  4. Volver al menú principal               ¦\n";
	cout << "+--------------------------------------------+\n";
	cout << "Seleccione una opción: ";
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
	setlocale(LC_CTYPE, "Spanish");
	cargarProcesos();      // <- lee procesos.txt (si existe) y reconstruye la lista
	cargarPila();     // Cargar pila de memoria
	verificarArchivoCola();
	cargarCola();
    int opcion;
    do {
        cout << "\n======================================\n";
        cout << "         MENU PRINCIPAL      \n";
        cout << "\n======================================\n";
        cout << "|    1. Gestor de Proceso\n";
        cout << "|    2. Planificador de CPU \n";
        cout << "|    3. Gestor de Memoria\n";
        cout << "|    4. Salir\n";
        cout << "\n======================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: gestorDeProcesos(); break;
            case 2: planificadorCPU(); break;
            case 3: gestorDeMemoria(); break;
            case 4: 
		    guardarProcesos();
		    guardarPila();
		    guardarCola();
		    cout << endl;
                cout << "|==============================================================|" << endl;
                cout << "|                                                              |" << endl;
                cout << "|                      Saliendo...                             |" << endl;
                cout << "|                                                              |" << endl;
                cout << "|           Gracias por usar Nuestro Programa                  |" << endl;
                cout << "|                                                              |" << endl;
                cout << "|==============================================================|" << endl;
                cout << endl;
                break;
            default: 
                cout << "✗ Error: Ingrese una opción válida (1-4)" << endl;
        }

    } while (opcion != 4);

    return 0;
}
