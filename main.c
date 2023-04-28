#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN 1

// declaracion de funciones
FILE* leer_fichero();
int** crear_tablero(int n);
int* crear_pistas_fila(int n, FILE* archivo);
int* crear_pistas_columna(int n, FILE* archivo);
void imprimir_matriz(int n, int **matriz, int pistas_fila[n], int pistas_columna[n]);
int menu(int n, int **matriz, int pistas_fila[n], int pistas_columna[n]);
void obtener_posicion(int n, int min, int *fila, int *columna);
int validar_posicion(int valor, int min, int max);
void accion_celda(int fila, int columna, int** matriz, int accion);
int validar_tablero(int n, int **matriz, int pistas_fila[n], int pistas_columna[n]);

int main()
{
    int n;
    int fin = 0;
    FILE* archivo = leer_fichero();

    // leemos la variable n de nuestra matriz 
    fscanf(archivo, "%i", &n);

    int** matriz = crear_tablero(n);
    int* pistas_fila = crear_pistas_fila(n, archivo);
    int* pistas_columna = crear_pistas_columna(n, archivo);
    
    // cerramos el archivo
    fclose(archivo);

    printf("Jugando...\n\n");

    while (fin == 0)
    {
        fin = menu(n, matriz, pistas_fila, pistas_columna);
    }
    
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

void imprimir_matriz(int n, int **matriz, int pistas_fila[n], int pistas_columna[n])
{
    printf("\n   ");
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

int menu(int n, int **matriz, int pistas_fila[n], int pistas_columna[n])
{
    int accion;

    imprimir_matriz(n, matriz, pistas_fila, pistas_columna);
    printf("Operaciones:\n-----------\n");
    printf("1) Desmarcar un cuadrado\n");
    printf("2) Marcar un cuadrado\n");
    printf("3) Salir del juego\n");

    while (1) {
        printf("\nIntroduzca la accion (1-3): ");
        scanf("%d", &accion);

        switch (accion) {
            case 1:{
                // La primera opcion del menu debera pedir al usuario por teclado la posicion del cuadrado a
                // desmarcar (fila y columna) y controlara que dicha posicion este dentro de los lımites del tablero
                // (entre 1 y N). A continuacion desmarcara el cuadrado, si estaba marcado, o mostrara un mensaje
                // de error por pantalla indicando que no es un cuadrado marcado se ha terminado el juego.
                int fila, columna;
            
                // Obtener la posición del usuario
                obtener_posicion(n, MIN, &fila, &columna);

                // accion desmarcar matriz
                accion_celda(fila, columna, matriz, accion);
                return 0;
            }
            case 2:{
                // La segunda opcion debera pedir igualmente al usuario por teclado la posicion del cuadrado
                // a marcar (fila y columna) y controlara que dicha posicion este dentro de los lımites del tablero
                // (entre 1 y N). A continuacion marcara el cuadrado sin comprobar si ya estaba marcado.
                int fila, columna;
            
                // Obtener la posición del usuario
                obtener_posicion(n, MIN, &fila, &columna);

                // accion marcar matriz
                accion_celda(fila, columna, matriz, accion);
                return 0;
            }
            case 3:{
                // La tercera opcion del menu saldra del programa con un mensaje de que se ha terminado el juego
                printf("Saliendo...\n");
                return 1;
            }
            default:
                printf("Acción no válida!\n");
        }
    }
}

void obtener_posicion(int n, int min, int *fila, int *columna)
{
    printf("Introduzca fila (entre 1 y %i): ", n);
    scanf("%d", fila);
    // Validar la entrada del usuario para la fila
    *fila = validar_posicion(*fila, min, n);

    printf("Introduzca columna (entre 1 y %i): ", n);
    scanf("%d", columna);
    // Validar la entrada del usuario para la columna
    *columna = validar_posicion(*columna, min, n);
}

int validar_posicion(int valor, int min, int max)
{
    // Validar si el valor está dentro del rango permitido
    while (valor < min || valor > max)
    {
        printf("Posicion no valida!.\n");
        printf("Introduce de nuevo el valor (entre 1 y %i): ", max);
        // pedir al usuario el valor hasta que sea correcto
        scanf("%d", &valor);
    }
    return valor;
}

void accion_celda(int fila, int columna, int** matriz, int accion)
{
    // accion marcar o desmarcar matriz
    if((matriz[fila-1][columna-1] == 0 && accion == 1) || (matriz[fila-1][columna-1] == 1 && accion == 2)){
        printf("Error! La celda ya estaba eliminada/ocupada\n");
    }else if(accion == 1){
        matriz[fila-1][columna-1] = 0;
    }else if(accion == 2){
        matriz[fila-1][columna-1] = 1;
    }
}

int validar_tablero(int n, int **matriz, int pistas_fila[n], int pistas_columna[n])
{
    // Para cada una de las pistas, check if valores matriz suma == pista
    // On 1º pista no se cumple, STOP
    
    return 0;
}