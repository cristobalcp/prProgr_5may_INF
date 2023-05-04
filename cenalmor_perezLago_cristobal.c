// Práctica de programación: KAKURASU - Cristóbal Cenalmor Pérez-Lago
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN 1

// declaracion de funciones empleadas
FILE* leer_fichero();
int** crear_tablero(int n);
int* crear_pistas(int n, FILE* archivo);
void imprimir_matriz(int n, int **matriz, int* pistas_fila, int* pistas_columna);
int menu(int n, int **matriz, int* pistas_fila, int* pistas_columna);
void obtener_posicion(int n, int min, int *fila, int *columna);
int validar_posicion(int valor, int min, int max);
int accion_celda(int fila, int columna, int** matriz, int accion);
int validar_tablero(int n, int **matriz, int* pistas_fila, int* pistas_columna);

int main()
{
    int n;
    int fin = 0;
    FILE* archivo = leer_fichero();

    // leemos la variable n de nuestra matriz 
    fscanf(archivo, "%i", &n);

    // creamos matriz y pistas tablero
    int** matriz = crear_tablero(n);
    int* pistas_fila = crear_pistas(n, archivo);
    int* pistas_columna = crear_pistas(n, archivo);
    
    // cerramos el archivo
    fclose(archivo);
    printf("Jugando...\n\n");

    // bucle de menu hasta juego completado o opcion salir
    while (fin == 0)
    {
        fin = menu(n, matriz, pistas_fila, pistas_columna);
    }

    // liberamos la memoria de la matriz
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
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
    {   
        // reseteamos las variables path y filename 
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

int* crear_pistas(int n, FILE* archivo){
    int* pistas = malloc(sizeof(int) * n);
    int dato;

    // leemos del archivo las pistas de las filas
    for (int i = 0; i < n; i++) {
        fscanf(archivo, "%i", &dato);
        pistas[i] = dato;
    }
    return pistas;
}

void imprimir_matriz(int n, int **matriz, int* pistas_fila, int* pistas_columna)
{
    printf("\n   ");
    // imprimimos índices de columnas
    for(int i = 0; i < n; i++) {
        printf("%i   ", i+1);
    }

    // separadores
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("_____");
    }
    printf("\n");

    // bucle de iteración sobre las dimensiones matriz
    for (int i = 0; i < n; i++) {
        // Índices de filas
        printf("%i ", i+1);

        // representacion valores matriz
        for (int j = 0; j < n; j++) {
            if(matriz[i][j] == 0){
                printf("|   ");
            }else{
                printf("| # ");
            }
        }

        // pistas de filas
        printf("| %i", pistas_fila[i]);
        printf("\n");
    }

    // separadores
    for(int i = 0; i < n; i++) {
        printf("_____");
    }
    printf("\n");

    // pistas de columnas
    printf("   ");
    for(int i = 0; i < n; i++) {
        printf("%i   ", pistas_columna[i]);
    }
    printf("\n\n");
};

int menu(int n, int **matriz, int* pistas_fila, int* pistas_columna)
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
                // opcion de desmarque de casilla, o error si ya estaba desmarcada
                int fila, columna;
            
                // obtener la posición seleccionada por el usuario
                obtener_posicion(n, MIN, &fila, &columna);

                // accion desmarcar matriz
                if(accion_celda(fila, columna, matriz, accion) == 1){
                    return validar_tablero(n, matriz, pistas_fila, pistas_columna);
                }
                return 0;
            }
            case 2:{
                // opcion de marque de casilla, o error si ya estaba marcada
                int fila, columna;
            
                // obtener la posición seleccionada por el usuario
                obtener_posicion(n, MIN, &fila, &columna);

                // accion marcar matriz
                if(accion_celda(fila, columna, matriz, accion) == 1){
                    return validar_tablero(n, matriz, pistas_fila, pistas_columna);
                }
                return 0;
            }
            case 3:{
                // opcion de terminar el juego
                printf("Saliendo...\n");
                return 1;
            }
            default:
                // opcion default
                printf("Acción no válida!\n");
                return 0;
        }
    }
}

void obtener_posicion(int n, int min, int *fila, int *columna)
{
    printf("Introduzca fila (entre 1 y %i): ", n);
    scanf("%d", fila);
    // validar la entrada del usuario para la fila
    *fila = validar_posicion(*fila, min, n);

    printf("Introduzca columna (entre 1 y %i): ", n);
    scanf("%d", columna);
    // validar la entrada del usuario para la columna
    *columna = validar_posicion(*columna, min, n);
}

int validar_posicion(int valor, int min, int max)
{
    // validar si el valor está dentro del rango permitido
    while (valor < min || valor > max)
    {
        printf("Posicion no valida!.\n");
        printf("Introduce de nuevo el valor (entre 1 y %i): ", max);
        // pedir al usuario el valor hasta que sea correcto
        scanf("%d", &valor);
    }
    return valor;
}

int accion_celda(int fila, int columna, int** matriz, int accion)
{
    // accion marcar o desmarcar matriz
    if((matriz[fila-1][columna-1] == 0 && accion == 1) || (matriz[fila-1][columna-1] == 1 && accion == 2)){
        printf("Error! La celda ya estaba eliminada/ocupada\n");
        return 0;
    }else if(accion == 1){
        matriz[fila-1][columna-1] = 0;
    }else if(accion == 2){
        matriz[fila-1][columna-1] = 1;
    }
    return 1;
}

int validar_tablero(int n, int **matriz, int* pistas_fila, int* pistas_columna) {
    int resultado = 1;

    for (int i = 0; i < n && resultado != 0; i++) {
        int sf = 0, 
            sc = 0, 
            pf = pistas_fila[i], 
            pc = pistas_columna[i];

        for (int j = 0; j < n; j++) {
            sf += matriz[i][j] * (j + 1);
            sc += matriz[j][i] * (j + 1);
        }

        if (sf != pf || sc != pc) {
            resultado = 0;
        }
    }

    if (resultado == 1) {
        printf("HAS LOGRADO LA SOLUCION!!:\n");
        imprimir_matriz(n, matriz, pistas_fila, pistas_columna);
    }
    
    return resultado;
}
