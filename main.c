#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COL 5
#define MAX_ACC 3

/* Funciones complementarias */
int marcar_celda(int fila, int columna);
void imprimir_matriz(int matriz[][MAX_COL], int filas, int columnas);

int main()
{
    /* definicion Variables main */
    FILE *archivo;
    char filename[50];
    char path[100] = "pruebas/";
    int n;

    printf("Nombre del fichero con el tablero inicial: ");
    scanf("%49s", filename);

    /* concatenamos las variables de path y filename */
    strcat(path, filename);

    /* apertura del fichero del tablero */
    archivo = fopen(path, "rb");
    
    /* control del error de apertura de tablero */
    while (archivo == NULL)
    {   /* reseteamos la variable filename */
        strcpy(filename, "");

        printf("Error abriendo el fichero!\n");
        printf("Por favor, escribe otro nombre o ruta: ");
        /* pedimos el filename hasta que exista el archivo */
        scanf("%49s", filename);
        /* concatenamos las variables de path y filename */
        strcat(path, filename);
        archivo = fopen(path, "rb");
    }

    /* leemos la variable n de nuestra matriz */
    fscanf(archivo, "%i", &n);
    printf("%i\n", n);

    // /* creamos matriz de tamaño NxN */
    int **matriz = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(n * sizeof(int));
    }

    /* leemos los datos del archivo y llenamos las pistas de filas y columnas */
    int dato;
    int pistas_fila[n];
    int pistas_columna[n];

    /* iteramos n*2 veces sobre el fichero para obtener todas las pistas */
    for (int i = 0; i < n*2; i++) {
        fscanf(archivo, "%i", &dato);
        if(i < n){
            pistas_fila[i] = dato;
        }else{
            pistas_columna[i-n] = dato;
        }
    }

    /* cerramos el archivo */
    fclose(archivo);

    /* verificar que la matriz se haya creado correctamente */
    printf("La matriz es:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%i ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("\nJugando...");
    return 0;
}

int marcar_celda(int fila, int columna)
{
    return fila + columna;
}

void imprimir_matriz(int matriz[][MAX_COL], int filas, int columnas)
{
    int i, k;

    for (i = 1; i < filas; i++)
    {
        for (k = 1; k < columnas; k++)
        {
            printf("%i", matriz[i][k]);
        }
        printf("\n");
    }
};
