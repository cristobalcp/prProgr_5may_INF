 ###### Cristóbal Cenalmor Pérez-Lago
###### Electrónica y Automática
###### UDC

# Enunciado

![[Enunciado.pdf]]

# Implementación

## Funciones
1. int main()
2. FILE* leer_fichero()
3. int** crear_tablero(int n)
4. int* crear_pistas_fila(int n, FILE* archivo)
5. int* crear_pistas_columna(int n, FILE* archivo)
6. void imprimir_matriz(int n, int **matriz, int pistas_fila[n], int pistas_columna[n])
7. int menu(int n, int **matriz, int pistas_fila[n], int pistas_columna[n])
8. void obtener_posicion(int n, int min, int *fila, int *columna)
9. int validar_posicion(int valor, int min, int max)
10. int accion_celda(int fila, int columna, int** matriz, int accion)
11. int validar_tablero(int n, int **matriz, int pistas_fila[n], int pistas_columna[n])