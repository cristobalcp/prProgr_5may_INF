 ###### Cristóbal Cenalmor Pérez-Lago
###### Electrónica y Automática
###### UDC

# Enunciado

![[Enunciado.pdf]]

# Implementación

## Funciones
1. FILE* leer_fichero();
2. int** crear_tablero(int n);
3. int* crear_pistas(int n, FILE* archivo);
4. void imprimir_matriz(int n, int **matriz, int* pistas_fila, int* pistas_columna);
5. int menu(int n, int **matriz, int* pistas_fila, int* pistas_columna);
6. void obtener_posicion(int n, int min, int *fila, int *columna);
7. int validar_posicion(int valor, int min, int max);
8. int accion_celda(int fila, int columna, int** matriz, int accion);
9. int validar_tablero(int n, int **matriz, int* pistas_fila, int* pistas_columna);
