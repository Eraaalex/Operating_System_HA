#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s file_reading file_recording\n", argv[0]);
        return 1;
    }
    FILE *file_1 = fopen(argv[1], "r");
    if (file_1 == NULL) {
        printf("Could not open the file for reading: %s\n", argv[1]);
        return 1;
    }
    FILE *file_2 = fopen(argv[2], "w");
    if (file_2 == NULL) {
        printf("Could not open the file for writing: %s\n", argv[2]);
        fclose(file_1);
        return 1;
    }
    char buffer[BUFFER_SIZE];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), file_1)) > 0) {
        fwrite(buffer, 1, bytes, file_2);
    }
    fclose(file_1);
    fclose(file_2);
    printf("The file has been copied successfully: %s -> %s \n", argv[1], argv[2]);
    return 0;
}
