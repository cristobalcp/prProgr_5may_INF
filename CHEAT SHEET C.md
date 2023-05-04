# include <stdio.h>
# include <string.h>
# include <stdlib.h>

strcpy(destino, origen)
strcat(cad1, cad2)
strlen(cad)
strupr(cad)
strlwr(cad)
strcmp(cad1, cad2)
stricmp(cad1, cad2)


``` C
int** crear_tablero(int n){
	// creamos matriz de tamaño NxN
	int **matriz = (int **) malloc(n * sizeof(int *));
	
	for (int i = 0; i < n; i++) {
		matriz[i] = malloc(n * sizeof(int));
	}
	return matriz;
} ```



int ** matriz;

matriz = (int **) malloc(n * sizeof(int *));

for(i=0; i < n; i++)
	matriz[n] = (int *) malloc(n *sizeof(int))