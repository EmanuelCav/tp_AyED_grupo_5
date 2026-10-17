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

// DESPUES PODEMOS CREAR FUNCIONES O USAR LAS FUNCIONES DE LA CÁTEDRA

void agregarNodo(NodoPaciente*& p, Paciente x);
void liberar(NodoPaciente*& p);
void mostrar(NodoPaciente* p);
void agregar(NodoCola *&p, NodoCola *&q, Paciente x);
Paciente suprimir(NodoCola *&p, NodoCola *&q);

int main() {
	
	// PUNTO 1
	
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
	
	mostrar(lista); // NO OBLIGATORIO
	
	// PUNTO 2
	
	// SI DECIDIMOS NOSOTROS AGREGAR A LOS PACIENTES

	/* 
	NodoCola *p = NULL;
	NodoCola *q = NULL;
	
	Paciente paciente;
	char motivo;
	char continuar = 'S';
	
	int eutanasiasDisponibles = 3;
	int pacientesAtendidos = 0;
	
	while (continuar == 'S') {
		
	    cout<<"Nombre del paciente: ";
	    cin>>paciente.nombre;
	
	    cout<<"Edad: ";
	    cin>>paciente.edad;
	
	    cout<<"Estado de salud (S/E): ";
	    cin>>paciente.estadoSalud;
	
	    cout<<"Motivo (pulsa E si desea realizar una eutanasia): ";
	    cin>>motivo;
	
	    if (motivo == 'E') {
	        if (eutanasiasDisponibles > 0) {
	            agregar(p, q, paciente);
	            eutanasiasDisponibles--;
	        } else {
	            cout<<"No quedan cupos para eutanasia."<<endl;
	        }
	    } else {
	        agregar(p, q, paciente);
	    }
	
	    cout<<"¿Desea ingresar mas pacientes? (pulsa S para continuar): ";
	    cin>>continuar;
	}
	
	while (p != NULL) {
	    paciente = suprimir(p, q);
	    cout << "Paciente atendido: " <<paciente.nombre<<endl;
	    pacientesAtendidos++;
	}
	
	cout << "La cantidad de pacientes atendidos durante el dia fue de: "<<pacientesAtendidos<<endl;
	
	*/
	
	
	
	// SI DECIDIMOS RECORRER LA LISTA DE PACIENTES CON VACUNA PENDIENTE
	
	/*

	NodoCola *p = NULL;
	NodoCola *q = NULL;
	
	NodoPaciente *aux = lista;
	Paciente paciente;
	char motivo;
	
	int eutanasiasDisponibles = 3;
	int pacientesAtendidos = 0;
	
	while (aux != NULL) {
	
	    paciente = aux->info;
	
	    cout<<"Nombre del paciente: "<<paciente.nombre<<endl;
	    cout<<"Motivo (Pulsa E si desea aplicar para eutanasia): ";
	    cin>>motivo;
	
	    if (motivo == 'E') {
	        if (eutanasiasDisponibles > 0) {
	            agregar(p, q, paciente);
	            eutanasiasDisponibles--;
	        } else {
	            cout<<"Ya no quedan cupos para eutanasia."<<endl;
	        }
	    } else {
	        agregar(p, q, paciente);
	    }
	
	    aux = aux->sgte;
	}
	
	while (p != NULL) {
	    paciente = suprimir(p, q);
	
	    cout<<"Paciente atendido: "<<paciente.nombre<<endl;
	    pacientesAtendidos++;
	}
	
	cout<<"La cantidad de pacientes atendidos durante el dia fue de: "<<pacientesAtendidos<<endl;
	
	liberar(lista);
	
	*/
	
	// SI DECIDIMOS RECORRER LA LISTA COMPLETA DE PACIENTES
	
	/*
	
	FILE* archivo = fopen("PACIENTES.dat", "rb");

	NodoCola *p = NULL;
	NodoCola *q = NULL;
	
	Paciente paciente;
	char motivo;
	
	int eutanasiasDisponibles = 3;
	int pacientesAtendidos = 0;
	
	fread(&paciente, sizeof(struct Paciente), 1, archivo);
	
	while (!feof(archivo)) {
	
	    cout << "Paciente: " << paciente.nombre << endl;
	    cout << "Motivo (E: eutanasia, O: otro): ";
	    cin >> motivo;
	
	    if (motivo == 'E') {
	        if (eutanasiasDisponibles > 0) {
	            agregar(p, q, paciente);
	            eutanasiasDisponibles--;
	        } else {
	            cout << "No quedan cupos para eutanasia." << endl;
	        }
	    } else {
	        agregar(p, q, paciente);
	    }
	
	    fread(&paciente, sizeof(struct Paciente), 1, archivo);
	}
	
	fclose(archivo);
	
	while (p != NULL) {
	    paciente = suprimir(p, q);
	
	    cout << "Paciente atendido: " << paciente.nombre << endl;
	    pacientesAtendidos++;
	}
	
	cout << "La cantidad de pacientes atendidos durante el dia fue de: "
	     << pacientesAtendidos << endl;
	     
	     */
	
	return 0;
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