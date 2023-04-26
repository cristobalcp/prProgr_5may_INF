#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COL 5
#define MAX_ACC 3

// declaracion de funciones
FILE* leer_fichero();
int** crear_tablero(int n);
int* crear_pistas_fila(int n, FILE* archivo);
int* crear_pistas_columna(int n, FILE* archivo);
int marcar_celda(int fila, int columna);
void imprimir_matriz(int **matriz, int n, int pistas_fila[n], int pistas_columna[n]);
void imprimir_menu();

int main()
{
    int n;

    FILE* archivo = leer_fichero();

    // leemos la variable n de nuestra matriz 
    fscanf(archivo, "%i", &n);

    int** matriz = crear_tablero(n);
    int* pistas_fila = crear_pistas_fila(n, archivo);
    int* pistas_columna = crear_pistas_columna(n, archivo);
    
    // cerramos el archivo
    fclose(archivo);

    printf("Jugando...\n\n");
    imprimir_matriz(matriz, n, pistas_fila, pistas_columna);
    imprimir_menu();
    return 0;
}

FILE* leer_fichero(){
 FILE *archivo;
    char filename[50];
    char path[100] = "pruebas/";

    printf("Nombre del fichero con el tablero inicial: ");
    scanf("%49s", filename);

    // concatenamos las variables de path y filename 
    strcat(path, filename);

    // apertura del fichero del tablero 
    archivo = fopen(path, "rb");

    // control del error de apertura de tablero 
    while (archivo == NULL)
    {   // reseteamos las variables path y filename 
        strcpy(path, "pruebas/");
        strcpy(filename, "");

        printf("Error abriendo el fichero!\n");
        printf("Por favor, escribe otro nombre o ruta: ");
        // pedimos el filename hasta que exista el archivo 
        scanf("%49s", filename);
        // concatenamos las variables de path y filename 
        strcat(path, filename);
        archivo = fopen(path, "rb");
    }

    return archivo;
}

int** crear_tablero(int n){
    // creamos matriz de tamaño NxN 
    int **matriz = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(n * sizeof(int));
    }
    return matriz;
}

int* crear_pistas_fila(int n, FILE* archivo){
    int* pistas_fila = malloc(sizeof(int) * n);
    int dato;

    for (int i = 0; i < n; i++) {
        fscanf(archivo, "%i", &dato);
        pistas_fila[i] = dato;
    }
    return pistas_fila;
}

int* crear_pistas_columna(int n, FILE* archivo){
    int* pistas_columna = malloc(sizeof(int) * n);
    int dato;

    for (int i = 0; i < n; i++) {
        fscanf(archivo, "%i", &dato);
        pistas_columna[i] = dato;
    }
    return pistas_columna;
}

void imprimir_matriz(int **matriz, int n, int pistas_fila[n], int pistas_columna[n])
{
    printf("   ");
    // Imprimimos índices de columnas
    for(int i = 0; i < n; i++) {
        printf("%i   ", i+1);
    }

    // Separadores
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("_____");
    }
    printf("\n");

    // Bucle de iteración sobre las dimensiones matriz
    for (int i = 0; i < n; i++) {
        // Índices de filas
        printf("%i ", i+1);

        // Representacion valores matriz
        for (int j = 0; j < n; j++) {
            if(matriz[i][j] == 0){
                printf("|   ");
            }else{
                printf("| # ");
            }
        }

        // Pistas de filas
        printf("| %i", pistas_fila[i]);
        printf("\n");
    }

    // Separadores
    for(int i = 0; i < n; i++) {
        printf("_____");
    }
    printf("\n");

    // Pistas de columnas
    printf("   ");
    for(int i = 0; i < n; i++) {
        printf("%i   ", pistas_columna[i]);
    }
    printf("\n\n");
};

void imprimir_menu(){
    int accion;

    printf("Operaciones:\n-----------\n");
    printf("1) Desmarcar un cuadrado\n");
    printf("2) Marcar un cuadrado\n");
    printf("3) Salir del juego\n");

    while (1) {
        printf("\nIntroduzca la accion (1-3): ");
        scanf("%d", &accion);
        switch (accion) {
            case 1:
                printf("DESMARCAR\n");
                break;
            case 2:
                printf("MARCAR\n");
                break;
            case 3:
                printf("Saliendo...\n");
                return;
            default:
                printf("Acción no válida!\n");
        }
    }
}

int marcar_celda(int fila, int columna)
{
    return fila + columna;
}
