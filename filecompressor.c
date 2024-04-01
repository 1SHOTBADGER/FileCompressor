#include<stdio.h>
#include<stdlib.h>

void compressFile(const char *inputFilename, const char *outputFilename){
FILE *input, *output;
int count;
char ch, currentChar;

input = fopen(inputFilename, "rb");
    if (input == NULL) {
        perror("Cannot open input file");
        exit(EXIT_FAILURE);
    }

    output = fopen(outputFilename, "wb");
    if (output == NULL) {
        perror("Cannot open output file");
        fclose(input);
        exit(EXIT_FAILURE);
    }

    currentChar = fgetc(input);
    while (currentChar != EOF) {
        count = 1;
        while ((ch = fgetc(input)) == currentChar && ch != EOF) {
            count++;
        }
        fwrite(&currentChar, sizeof(char), 1, output);
        fwrite(&count, sizeof(int), 1, output); 
        currentChar = ch;
    }

    fclose(input);
    fclose(output);
}

void decompressFile(const char *inputFilename, const char *outputFilename) {
    FILE *input, *output;
    int count;
    char ch;

    input = fopen(inputFilename, "rb");
    if (input == NULL) {
        perror("Cannot open input file");
        exit(EXIT_FAILURE);
    }

    output = fopen(outputFilename, "wb");
    if (output == NULL) {
        perror("Cannot open output file");
        fclose(input);
        exit(EXIT_FAILURE);
    }

    while (fread(&ch, sizeof(char), 1, input)) { 
        if (fread(&count, sizeof(int), 1, input)) { 
            for (int i = 0; i < count; i++) {
                fputc(ch, output); 
            }
        }
    }

    fclose(input);
    fclose(output);
}



int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <compress/decompress> <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "compress") == 0) {
        compressFile(argv[2], argv[3]);
    } else if (strcmp(argv[1], "decompress") == 0) {
        decompressFile(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Invalid operation. Use 'compress' or 'decompress'.\n");
        return EXIT_FAILURE;
    }

    return 0;
}
