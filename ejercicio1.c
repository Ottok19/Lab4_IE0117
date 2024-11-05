#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Esta función asigna la memoria para la matriz según el tamaño ingresado por el usuario.
// La función recibe un puntero triple de la matriz y el tamaño; primero se le asigna el espacio de memoria
// A las filas de la matriz, y después a las columnas según el tamaño de dato.


void asignar_memoria(int ***matriz, int tamaño) {

	printf("Asigando memoria\n");

	*matriz = (int**) malloc(tamaño * sizeof(int*));

	for (int i = 0; i < tamaño; i++) {

		(*matriz)[i] = (int*) malloc(tamaño * sizeof(int));
	
	}

	if(*matriz == NULL) {
		
		printf("No se pudo asignar memoria\n");
	
	}

}

// Esta función recibe el puntero doble de la matriz y el tamaño ingresado por el usuario, y llena la matriz con
// número aleatorios entre el 0 y el 1 utilizando la biblioteca time y las funciones rand y srand.

void llenar_matriz(int **matriz, int tamaño) {

	srand(time(NULL));  // Inicializa los números aleatorios según la hora
	printf("Llenando matriz\n");
	
	for (int i = 0; i < tamaño; i++) {
		for (int j = 0; j < tamaño; j++) {
			*(*(matriz + i) + j) = rand() %2;
		}
	}
}

// Esta función imprime la matriz para visualización del usuario.

void imprimir_matriz(int **matriz, int tamaño) {

	printf("Matriz %dx%d :\n", tamaño, tamaño);

	for (int i = 0; i < tamaño; i++) {
		printf("[");
                for (int j = 0; j < tamaño; j++) {
			printf(" [%d] ", *(*(matriz + i) + j));
		}
	printf("]\n");
	}
}

// Esta función transpone la matriz previamente generada utilizando punteros y una variable temporal,
// realizando la transposición unicamente cuando i es igual o menor que j para evitar errores.

void transponer_matriz(int **matriz, int tamaño) {
	
	printf("La matriz transpuesta sería\n");	
	
	int temp;

	for (int i = 0; i < tamaño; i++) {
                for (int j = 0; j < tamaño; j++) {
                	if(i == j || i < j) {
				temp = *(*(matriz + i) + j);
				*(*(matriz + i) + j) = *(*(matriz + j) + i);
				*(*(matriz + j) + i) = temp;
			}
		}	
	}

}

// Esta función encuentra la línea de 1s más larga en la matriz recibida y devuelve la longitud de dicha línea.
// Se realiza con dos contadores donde uno encuentra una fila de 1s, la almacena en la segunda variable y limpia la
// Primera, después encuentra otra fila de 1s y compara si es mayor que la almacenada en el segundo contador, si es
// Así la suscribe y si no se reinicia para buscar otra fila nueva de 1s.

int linea_de_1s(int **matriz, int tamaño) {

	int v1 = 0; 
	int v2 = 0;

	for (int i = 0; i < tamaño; i++) {
                for (int j = 0; j < tamaño; j++) {
                        if (*(*(matriz + i) + j) == 1) {
                                v1 = v1 + 1;
                        }
                        if ( *(*(matriz + i) + j) == 0 || (i == tamaño - 1) & (j == tamaño - 1)) {
                                if (v1 > v2) {
                                        v2 = v1;
                                        v1 = 0;
                                }
                                else {
                                        v1 = 0;
                                }

                        }
                }
        }

	return v2;
}

// Esta función se utiliza para liberar la memoria asignada a la matriz una vez que se terminaron las demas tareas.
// Importante notar que así como se pidio memoria pára filas y luego para columnas, ahora se liberan las columnas y
// después las filas.

void liberar_memoria(int **matriz, int tamaño) {

	printf("Liberando memoria\n");

	for (int i = 0; i < tamaño; i++) {
		free(matriz[i]);
	}

	free(matriz);

	printf("Memoria liberada\n");
}

// Función principal donde se inicializan las variables que se pasan a funciones, y se solicita al usuario el tamaño de // La matriz, después se llaman las funciones en el orden necesario para la funcionalidad del programa y se muestran
// Los resultados.

int main() {

	int tamaño, fila_mas_larga;
	int **matriz = NULL;

	printf("Introduzca el tamaño de la matriz: ");
	scanf("%d", &tamaño);

	asignar_memoria(&matriz, tamaño);
	llenar_matriz(matriz, tamaño);
	imprimir_matriz(matriz, tamaño);

	fila_mas_larga = linea_de_1s(matriz, tamaño);
	printf("La línea de 1s más larga de la matriz es de %d\n", fila_mas_larga);

	transponer_matriz(matriz, tamaño);
	imprimir_matriz(matriz, tamaño);
	fila_mas_larga = linea_de_1s(matriz, tamaño);
	printf("La línea de 1s más larga de la matriz transpuesta es de %d\n", fila_mas_larga);

	liberar_memoria(matriz, tamaño);

	return 0;
	
}

