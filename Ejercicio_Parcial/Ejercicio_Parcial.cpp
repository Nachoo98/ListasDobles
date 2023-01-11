#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct mediciones { //struct de mediciones
	int in;
	double na;
}mediciones;


typedef struct nodo1 { //lista paara los identificadoes
	int dato;
	struct nodo1* sig;
}nodo1;

typedef struct nodo2 { //lista para los niveles de activacion
	double dato;
	struct nodo2* sig;
}nodo2;


nodo1* insertar_fifo(nodo1* lista, int identificador) 
{
	nodo1* nuevo, * p;
	nuevo = (nodo1*)malloc(sizeof(nodo1));

	nuevo->dato = identificador;
	nuevo->sig = NULL;//Ultimo nodo

	if (lista == NULL)
		return nuevo; // Como la lista no esta vacia la recorro buscando el ultimo nodo
	p = lista;
	while (p->sig != NULL)
		p = p->sig;//Ahora p es el ultimo nodo
	p->sig = nuevo;

	return lista;
}

nodo2* insertar_lifo(nodo2* lista, double nivel) 
{
	nodo2* nuevo;

	nuevo = (nodo2*)malloc(sizeof(nodo2));
	nuevo->dato = nivel;
	nuevo->sig = lista;

	return nuevo;

}
void mostarLista1(nodo1* lista) {
	printf("\nContenido de la lista:\n");
	while (lista != NULL) {
		printf("\nIdentificador: %d\n", lista->dato);
		lista = lista->sig;
	}
}

void mostarLista2(nodo2* lista) {
	printf("\nContenido de la lista:\n");
	while (lista != NULL) {
		printf("\nNivel de Activacion: %.2lf  %\n", (lista->dato)*100);
		lista = lista->sig;
	}
}

void nivelCercanoa1(nodo2* lista) { //encontrar valor maximo de Nivel de Activacion

	double mayor;

	if (lista == NULL) {
		printf("Lista vacia\n");
		return;
	}
	else {
		mayor = lista->dato;
		
		while (lista != NULL) {

			if (lista->dato > mayor) {
				mayor = lista->dato;
			}
		
			lista = lista->sig;
		}

	}
	printf("\nLa mayor velocidad de activacion es %.2lf", mayor*100);
}
/*
nodo1* destruir1(nodo1* lista)
{
	nodo1* aux;

	while (lista != NULL)
	{
		aux = lista;
		lista = lista->sig;
		free(aux);
	}
	printf("Lista destruida. \n");
	return NULL;
}

nodo2* destruir2(nodo2* lista)
{
	nodo2* aux;

	while (lista != NULL)
	{
		aux = lista;
		lista = lista->sig;
		free(aux);
	}
	printf("Lista destruida. \n");
	return NULL;
}
*/

int imprime_menu(void) {
	int op;
	printf("\n1. Leer Archivo y crear dos listas separadas");
	printf("\n2. Verificar nivel de activacion");
	printf("\n3. Intercambiar primero por ultimo");
	printf("\n4. Generar Archivo (ingresando valores a mano)");
	printf("\n5. Mostar datos archivo");
	printf("\n0. Salir");
	printf("\nOpcion:");
	scanf("%d", &op);
	return op;
}

int main() {
	int op;
	FILE* f;
	int n, cant = 0,cont=0, total = 1;
	mediciones m;
	int idn;
	double nac, vector[100];

	nodo1* lista1 = NULL;//inicializo las listas en NULL
	nodo2* lista2 = NULL;

	do {
		op = imprime_menu();
		switch (op) {
		case 1: // Leer Archivo y crear dos listas separadas
			f = fopen("mediciones.dat", "rb");


			if (f == NULL) {
				printf("\nError al abrir el archivo para escritura");
				exit(3);
			}


			n = fread(&m, sizeof(m), 1, f); //leer el archivo

			while (n == 1) {

				lista1 = insertar_fifo(lista1, m.in); //fifo
				lista2 = insertar_lifo(lista2, m.na); //lifo

				n = fread(&m, sizeof(m), 1, f);
				cant++;
			}

			if (fclose(f) != 0) {
				printf("\nError al cerrar"); //cierro porque ya se leyo todo el archivo
				exit(4);
			}

			mostarLista1(lista1);
			mostarLista2(lista2);
			break;

		case 2:// Verificar nivel de activacion
			nivelCercanoa1(lista2);
		
			break;
		case 3://Intercambiar primero por ultimo (como no tengo tiempo lo planteo de la siguiente manera)
			/*
			f = fopen("mediciones.dat", "rb");


			if (f == NULL) {
				printf("\nError al abrir el archivo para escritura");
				exit(3);
			}


			n = fread(vector, sizeof(m.in), 1, f); //leer el archivo

			while (n == 1) {
				n = fread(vector, sizeof(m.in), 1, f);
				cont++;
			}

			if (fclose(f) != 0) {
				printf("\nError al cerrar"); //cierro porque ya se leyo todo el archivo
				exit(4);
			}

			int aux;
			aux = vector[0];
			vector[0] = vector[cont - 1];
			vector[cont - 1] = aux;

			for (int i = 0; i < cont; i++) {
				printf("%d", vector[i]);
			}
			*/
			break;

		case 4:// Generar Archivo (ingresando valores a mano)
			
			f = fopen("mediciones.dat", "wb");

	
			if (f == NULL) {
				printf("\nError al abrir el archivo para escritura");
				exit(1);
			}
			while (total != 0) {
				printf("Ingrese el Identificador de neurona (valor positivo): \n");
				scanf("%d", &idn);
				if (idn > 0) { m.in = idn; }
				else { printf("El valor ingresado es negativo"); exit(4); }
				printf("Ingrese el Nivel de activacion (entre 0 y 1 con 2 digitos de presicion): \n");
				scanf("%lf", &nac);
				if (nac > 0 && nac < 1) { m.na = nac; }
				else { printf("El valor ingresado no es valido"); exit(5); }
				
		
				m.na = nac;

				fwrite(&m, sizeof(m), 1, f);

				printf("\nContinuar? -> 1\n");
				printf("\nSalir? -> 0\n");
				scanf("%d", &total);

				cant++;
			}
	
			printf("\nSe cargaron %d mediciones en el archivo\n", cant);

			if (fclose(f) != 0) {
				printf("\nError al cerrar"); //cierro porque ya se leyo todo el archivo
				exit(2);
			}
			break;

		case 5://Leo y  muestro el contenido del archivo

			f = fopen("mediciones.dat", "rb");


			if (f == NULL) {
				printf("\nError al abrir el archivo para escritura");
				exit(3);
			}

			
			n = fread(&m, sizeof(m), 1, f); //leer el archivo

			while (n == 1) {
				printf("\n -Identificador de neurona: %d\n -Nivel de activacion: %lf \n", m.in, m.na);
				printf("---------------------------------------------");
				n = fread(&m, sizeof(m), 1, f);
			}
			
			if (fclose(f) != 0) {
				printf("\nError al cerrar"); //cierro porque ya se leyo todo el archivo
				exit(4);
			}

			break;

		case 0:
			break;

		default:
			printf("\nOpcion invalida");
			break;

		}
	} while (op != 0);
	/*
	destruir1(lista1);
	destruir2(lista2);
	*/
	return 0;
}
