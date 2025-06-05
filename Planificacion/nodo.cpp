#include <iostream>
using namespace std;
struct Nodo{
	int id_Proceso;
	string NombreProceso;
	string Estado; 
	string Prioridad;
	Nodo * siguiente;
	Nodo (id, nomPro, Es, Prio){
		id_Proceso = id;
		NombreProceso = nomPro;
		Estado = Es;
		Prioridad = Prio;
		siguiente = NULL;
	}	
};



int main (){
	//Listas
	Nodo* inicio = NULL;
	//Pilas
	Nodo* tope = NULL;
	//Colas
	Nodo* frente = NULL;
	Nodo* fin = NULL;
	
	int opcion;
	
	do{
		cout << "\n******************************\n";
        cout << "         MENU PRINCIPAL     \n";
        cout << "******************************\n";
        cout << "1. Gestor de Proceso\n";
        cout << "2. Planificador de CPU \n";
        cout << "3. Gestor de Memoria\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion){
        	case 1:
        		
        		break;
        	case 2:
        		
        		break;
        	case 3:
        		
        		break;
        	case 4:
        		cout << "Saliendo del programa....."<< endl;
        		break;
        	default:
        		cout << "Error, ingrese una opcion valida" << endl;    		
		}
		
	}while(opcion !=4);

	return 0;
}
