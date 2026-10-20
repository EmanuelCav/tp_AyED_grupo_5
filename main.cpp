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

struct PacienteArchivo {
    char nombre[30];
    int edad;
    char estadoSalud;
    int cantidadVacunas;
};

struct NodoPaciente {
    Paciente info;
    NodoPaciente *sgte;
};

struct NodoCola {
    Paciente info;
    NodoCola *sgte;
};

void agregarNodo(NodoPaciente*& p, Paciente x);
void liberar(NodoPaciente*& p);
void mostrar(NodoPaciente* p);
void agregar(NodoCola *&p, NodoCola *&q, Paciente x);
Paciente suprimir(NodoCola *&p, NodoCola *&q);

int main() {
	
	// PUNTO 1
	
	FILE* archivo = fopen("PACIENTES.dat", "rb");

	Paciente paciente;
	PacienteArchivo pacienteArchivo;
	Vacuna vacuna;

	NodoPaciente *lista = NULL;
	
	fread(&pacienteArchivo, sizeof(PacienteArchivo), 1, archivo);

	while (!feof(archivo)) {

    strcpy(paciente.nombre, pacienteArchivo.nombre);
    paciente.edad = pacienteArchivo.edad;
    paciente.estadoSalud = pacienteArchivo.estadoSalud;
    paciente.historialVacunacion = NULL;

    for (int i = 0; i < pacienteArchivo.cantidadVacunas; i++) {

        	fread(&vacuna, sizeof(Vacuna), 1, archivo);

        	NodoVacuna *nuevo = new NodoVacuna;
        	nuevo->info = vacuna;
        	nuevo->sgte = paciente.historialVacunacion;
        	paciente.historialVacunacion = nuevo;
	    }

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

    	while (paciente.historialVacunacion != NULL) {
        	NodoVacuna *aux = paciente.historialVacunacion;
        	paciente.historialVacunacion = paciente.historialVacunacion->sgte;
        	delete aux;
	    }
	    
	    fread(&pacienteArchivo, sizeof(PacienteArchivo), 1, archivo);
	}

	fclose(archivo);
	
	mostrar(lista);
	liberar(lista);
	
	// PUNTO 2
	
	NodoCola *p = NULL;
    NodoCola *q = NULL;

    char motivo;
    char continuar = 'S';

    int eutanasiasDisponibles = 3;

    while (continuar == 'S') {

        cout<<"Nombre del paciente: ";
        cin>>paciente.nombre;

        cout<<"Edad: ";
        cin>>paciente.edad;

        cout<<"Estado de salud (S/E): ";
        cin>>paciente.estadoSalud;

        paciente.historialVacunacion = NULL;

        cout<<"Motivo de consulta (E: eutanasia): ";
        cin>>motivo;

        if (motivo == 'E') {

            if (eutanasiasDisponibles > 0) {
                agregar(p, q, paciente);
                eutanasiasDisponibles--;
                cout <<"Paciente con pedido de eutanasia agregado a la cola."<<endl;
            } else {
                cout <<"No quedan cupos para eutanasia."<<endl;
            }

        } else {
            agregar(p, q, paciente);
            cout<<"Paciente agregado a la cola."<<endl;
        }

        cout<<"¿Desea ingresar otro paciente? (S/N): ";
        cin>>continuar;
    }


	// PUNTO 3
	
	int pacientesAtendidos = 0;
	
	while (p != NULL) {
        paciente = suprimir(p, q);
        pacientesAtendidos++;
    }

    cout<<"La cantidad de pacientes atendidos durante el dia fue de: "<<pacientesAtendidos<<endl;
	
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

void mostrar(NodoPaciente* p) {
    NodoPaciente* aux = p;

    while (aux != NULL) {
        cout << aux->info.nombre << endl;
        aux = aux->sgte;
    }
}

void liberar(NodoPaciente*& p) {
    NodoPaciente* aux;

    while (p != NULL) {
        aux = p;
        p = p->sgte;
        delete aux;
    }
}

void agregar(NodoCola *&p, NodoCola *&q, Paciente x) {
    NodoCola *nuevo = new NodoCola;
    nuevo->info = x;
    nuevo->sgte = NULL;

    if (p == NULL) {
        p = nuevo;
    } else {
        q->sgte = nuevo;
    }

    q = nuevo;
}

Paciente suprimir(NodoCola *&p, NodoCola *&q) {
    Paciente ret = p->info;
    NodoCola *aux = p;

    p = p->sgte;

    if (p == NULL) {
        q = NULL;
    }

    delete aux;
    return ret;
}