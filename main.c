#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

void free_lines(char **lines, int count) {
    for (int i = 0; i < count; ++i)
        free(lines[i]); // liberar cada línea
    free(lines); // liberar arreglo de punteros
}


int is_file_empty(FILE *file) {
    fseek(file, 0, SEEK_END);   // Mueve el puntero al final del archivo
    long size = ftell(file);    // Obtiene la posición (tamaño en bytes)
    rewind(file);               // Vuelve al inicio del archivo
    return size == 0;
}

int main(int argc, char *argv[]) {
    // Verifica cantidad mínima de argumentos
    if (argc < 2) {
        fprintf(stderr, RED "Uso: %s <archivo_entrada> [-o archivo_salida]\n" RESET, argv[0]);
        return 1;
    }

    char *input_path = argv[1];
    char *output_path = NULL;

    // Verifica si se especificó un archivo de salida
    if (argc == 4 && strcmp(argv[2], "-o") == 0)
        output_path = argv[3];

    // Abre el archivo de entrada en modo lectura
    FILE *input_file = fopen(input_path, "r");
    if (!input_file) {
        fprintf(stderr, RED "✘ Error: No se pudo abrir el archivo de entrada: %s\n" RESET, input_path);
        return 1;
    }

    // Verifica si el archivo está vacío
    if (is_file_empty(input_file)) {
        fprintf(stderr, YELLOW "⚠️  Advertencia: El archivo '%s' está vacío.\n" RESET, input_path);
        fclose(input_file);
        return 1;
    }

    // Preparación para leer líneas
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Arreglo dinámico de líneas con capacidad inicial de 10
    int count = 0, capacity = 10;
    char **lines = malloc(sizeof(char*) * capacity);

    if (!lines) {
        fprintf(stderr, RED "✘ Error: No se pudo asignar memoria.\n" RESET);
        fclose(input_file);
        return 1;
    }

    // Lee línea por línea con getline y almacena en el arreglo
    while ((read = getline(&line, &len, input_file)) != -1) {
        // Aumenta capacidad del arreglo si se llena
        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(lines, sizeof(char*) * capacity);
            if (!temp) {
                fprintf(stderr, RED "✘ Error: Fallo al redimensionar memoria.\n" RESET);
                free(line);
                free_lines(lines, count);
                fclose(input_file);
                return 1;
            }
            lines = temp;
        }
        // Guarda una copia de la línea leída
        lines[count++] = strdup(line);
    }

    free(line); // libera el buffer de getline
    fclose(input_file);

    // Determina si se imprime en pantalla o se guarda en archivo
    FILE *output = output_path ? fopen(output_path, "w") : stdout;
    if (!output) {
        fprintf(stderr, RED "✘ Error: No se pudo abrir el archivo de salida: %s\n" RESET, output_path);
        free_lines(lines, count);
        return 1;
    }

    // Imprime las líneas en orden inverso
    for (int i = count - 1; i >= 0; --i)
        fprintf(output, "%s", lines[i]);

    // Mensaje si se guardó el resultado en archivo
    if (output_path) {
        fclose(output);
        printf(GREEN "✔ Líneas invertidas guardadas en: %s\n" RESET, output_path);
    }

    free_lines(lines, count);
    return 0;
}
