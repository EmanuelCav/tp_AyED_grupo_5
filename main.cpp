#include <iostream>
#include <stdio.h>

using namespace std;

struct Vacuna {
	char nombreVacuna[30];
	int fecha;
	char estado; // 'S': aplicado o 'P': pendiente
};

struct NodoVacuna {
    Vacuna info;
    NodoVacuna *sgte;
};

struct Paciente {
    char nombre[30];
    int edad;
    char estadoSalud; // 'S': sano, 'E': enfermo
    NodoVacuna *historialVacunacion;
};

struct NodoPaciente {
    Paciente info;
    NodoPaciente *sgte;
};

struct NodoCola {
    Paciente info;
    NodoCola *sgte;
};

struct Cola {
    NodoCola *p;
    NodoCola *q;
};

// DESPUES PODEMOS CREAR FUNCIONES O USAR LAS FUNCIONES DE LA CÁTEDRA

void agregarNodo(NodoPaciente*& p, Paciente x);

int main() {
	
	FILE* archivo = fopen("PACIENTES.dat", "rb");
	
	Paciente paciente;
	NodoPaciente *lista = NULL;
	
	fread(&paciente, sizeof(struct Paciente), 1, archivo);
	
	while(!feof(archivo)) {
		
		bool pendiente = false;
        NodoVacuna *aux = paciente.historialVacunacion;

        while (aux != NULL && !pendiente) {
            if (aux->info.estado == 'P') {
                pendiente = true;
            }

            aux = aux->sgte;
        }

        if (pendiente) {
            agregarNodo(lista, paciente);
        }
        
        fread(&paciente, sizeof(struct Paciente), 1, archivo);
	}
	
	fclose(archivo);
	
	return 0;
}

void agregarNodo(NodoPaciente*& p, Paciente x) {

    NodoPaciente* nuevo = new NodoPaciente;
    nuevo->info = x;
    nuevo->sgte = NULL;

    if (p == NULL) {
        p = nuevo;
    } else {
    	
        NodoPaciente* aux = p;
        
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        
        aux->sgte = nuevo;
    }
}