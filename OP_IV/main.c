#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   // open()
#include <unistd.h>  // read(), write(), close()
#include <string.h>  // strlen()

int main() {
    int fd;  
    char buffer[200];  
    char input[200];  
    char nombreArchivo[100];

    // 1. Pedir nombre del archivo
    printf("Ingrese el nombre del archivo (ej: archivo.txt): ");
    scanf("%s", nombreArchivo);
    getchar(); // limpiar el salto de línea pendiente en el buffer

    // 2. Pedir al usuario un texto
    printf("Escribe el texto que deseas guardar en '%s':\n> ", nombreArchivo);
    fgets(input, sizeof(input), stdin);  // Lee toda la línea que escriba el usuario

    // 3. Crear o abrir archivo
    fd = open(nombreArchivo, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error al crear/abrir archivo");
        exit(1);
    }

    // 4. Escribir en el archivo
    write(fd, input, strlen(input));
    close(fd);

    // 5. Leer el archivo
    fd = open(nombreArchivo, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir archivo para leer");
        exit(1);
    }

    int bytesLeidos = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesLeidos >= 0) {
        buffer[bytesLeidos] = '\0';
        // 6. Imprimir en pantalla
        printf("\nContenido de '%s':\n%s", nombreArchivo, buffer);
    }

    close(fd);
    return 0;
}
