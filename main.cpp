#include <iostream>
#include <string>
#include <string.h>
#include "funciones.hpp"
using namespace std;


int main(int argc, char** argv) {
	Nodo* lista = NULL;
	
	agregarNodo(lista, 1);
	agregarNodo(lista, 10);
	agregarNodo(lista, 25);
	agregarNodo(lista, 50);
	agregarNodo(lista, 100);
	agregarNodo(lista, 500);
	
	//mostrar(lista);
	
	/*Nodo* buscado = buscar(lista,200);
	
	if(buscado == NULL){
		cout << "El valor no esta en la lista" << endl;
	} else {
		cout << "El valor " << buscado->info << " esta en la lista" << endl;
	}
	*/
	
	//eliminar(lista,20);
	/*int valorEliminado = eliminarPrimerNodo(lista);
	cout << "Se elimino el valor " << valorEliminado << endl;
	mostrar(lista);
	*/
	
	/*Nodo* nodoInsertado = insertarOrdenado(lista,15);
	
	cout << "El nro " << nodoInsertado->info << " fue insertado correctamente" << endl;
	
	mostrar(lista);*/
	
	//ordenar(lista);
	//mostrar(lista);
	
	bool enc;
	
	Nodo* nodoBuscado = buscaEInsertaOrdenado(lista,700,enc);
	
	if(enc){
		cout << "El nro " << nodoBuscado->info << " ya estaba en la lista" << endl;
	} else {
		cout << "El nro " << nodoBuscado->info << " fue insertado en la lista" << endl;
	}
	
	mostrar(lista);
	
    return 0;
}