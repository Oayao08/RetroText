#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // para usleep()

#define MAX_LINE_LENGTH 1000

void slow_print(const char *text, useconds_t delay_us) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay_us);
    }
}

void show_title_screen() {
    system("clear");
    slow_print("=== RetroText ===\n", 30000);
    slow_print("Tu máquina de escribir literaria en consola.\n\n", 20000);
    slow_print("Escribe tu texto. Usa /save para guardar, /exit para salir.\n\n", 20000);
}

void write_loop(FILE *output) {
    char line[MAX_LINE_LENGTH];

    while (1) {
        printf("> ");
        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) break;

        if (strncmp(line, "/exit", 5) == 0) {
            break;
        } else if (strncmp(line, "/save", 5) == 0) {
            FILE *file = fopen("manuscrito.txt", "w");
            if (file) {
                fprintf(file, "Texto escrito guardado desde RetroText.\n");
                fclose(file);
                slow_print("Guardado en 'manuscrito.txt'\n", 20000);
            } else {
                printf("Error al guardar el archivo.\n");
            }
        } else {
            fprintf(output, "%s", line);
        }
    }
}

int main() {
    show_title_screen();
    FILE *temp_output = tmpfile(); // Guardamos el texto temporalmente
    if (!temp_output) {
        perror("No se pudo crear archivo temporal");
        return 1;
    }

    write_loop(temp_output);
    fclose(temp_output);
    slow_print("\n¡Gracias por usar RetroText!\n", 30000);
    return 0;
}
