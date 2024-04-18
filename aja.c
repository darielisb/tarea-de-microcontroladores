#include <stdio.h>
#include <stdlib.h>

int main() {
    int longitud;

    do {
        printf("¿Cuántos elementos quieres almacenar? ");
        if (scanf("%d", &longitud) != 1 || longitud <= 0) {
            printf("Error: Entrada no válida. Debes ingresar un número entero positivo.\n");
            // Limpiar el búfer de entrada
            while (getchar() != '\n');
        }
    } while (longitud <= 0);

    float *valores = (float*) malloc(longitud * sizeof(float));
    if (valores == NULL) {
        printf("No tienes tanta memoria.\n");
        return 1;
    }
    
    // Solicitar al usuario que ingrese los valores
    printf("Ingresa %d valores:\n", longitud);
    for (int i = 0; i < longitud; i++) {
        int valor;
        while (1) {
            printf("Valor %d: ", i + 1);
            if (scanf("%d", &valor) == 1) {
                valores[i] = valor;
                break;
            } else {
                printf("Error: Debes ingresar un número entero.\n");
                // Limpiar el búfer de entrada
                while (getchar() != '\n');
            }
        }
    }

    // Abrir el archivo para escribir
    FILE *archivo = fopen("valores.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
    printf("La dirección de memoria donde se almacenan los elementos es: %p\n", (void *)valores);
    
    // Escribir los valores en el archivo
    for (int i = 0; i < longitud; i++) {
        fprintf(archivo, "%.2f\n", valores[i]);
    }

    // Mover el puntero de archivo al final del archivo
    fseek(archivo, 0, SEEK_END);
    // Obtener la posición actual del puntero de archivo
    long fileSize = ftell(archivo);
    
    printf("Se han guardado los valores en el archivo 'valores.txt'.\n");
    printf("El tamaño del archivo generado es %ld bytes.\n", fileSize);
    
    // Cerrar el archivo y liberar la memoria
    fclose(archivo);
    free(valores);
    
    return 0;
}
