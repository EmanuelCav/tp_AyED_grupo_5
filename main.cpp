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
            NodoPaciente *nuevo = new NodoPaciente;
            nuevo->info = paciente;
            nuevo->sgte = lista;
            lista = nuevo;
        }
        
        fread(&paciente, sizeof(struct Paciente), 1, archivo);
	}
	
	fclose(archivo);
	
	return 0;
}