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
