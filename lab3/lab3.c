#include <stdio.h>
#include <stdlib.h>

// A01377263
// Louise Li, Set G

void encrypt_text (char *inputTextFile, char *outputTextFile, int shift) {
    const int minUpperCase = 65;
    const int maxUpperCase = 90;
    const int minLowerCase = 97;
    const int maxLowerCase = 122;

    // Declares array of size 100.
    char c[100];
    char inputChar;

    // Reads input from the specified file.
    FILE *file = fopen(inputTextFile, "r");
    if (file == NULL) {
        // perror("Error opening input file");
        return;
    }
    
    // stores input char into array
    int index = 0;
    while (inputChar != EOF) {
        inputChar = fgetc(file);
        c[index] = inputChar;
        index++;
    }

    while (shift > 26 || shift < -26) {
        if (shift > 26) {
            shift -= 26;
        } else {
            shift += 26;
        }
    }

    char encryptedArray[index + 1];

    // 1 for UC, 0 for LC, 100 for NA.
    int isUpperCase = 1;
    for (int i = 0; i < index - 1; i++) {
        int unicode = (int) c[i];

        // Checks if the current char is in the alphabet and if it's a capital.
        if ((unicode >= minUpperCase) && (unicode <= maxUpperCase)) {
            isUpperCase = 1;
            unicode += shift;
        } else  if ((unicode >= minLowerCase) && (unicode <= maxLowerCase)) {
            isUpperCase = 0;
            unicode += shift;
        } else {
            isUpperCase = 100;
        }

        // Checks if unicode is outside of the alphabet range.
        // Then calculates the shifted unicode.
        if ((unicode < minUpperCase) && (isUpperCase == 1)) {
            unicode = maxUpperCase - (minUpperCase - unicode) + 1;
        } else if ((unicode > maxUpperCase) && (isUpperCase == 1)) {
            unicode = minUpperCase + (unicode - maxUpperCase) - 1;
        } else if ((unicode < minLowerCase) && (isUpperCase == 0)) {
            unicode = maxLowerCase - (minLowerCase - unicode) + 1;
        } else if ((unicode > maxLowerCase) && (isUpperCase == 0)) {
            unicode = minLowerCase + (unicode - maxLowerCase) - 1;
        }

        encryptedArray[i] = (char) unicode;
    }

    // Code below outputs encrypted text to output.txt
    FILE *fileOut = fopen(outputTextFile, "w");
    if (fileOut == NULL) {
        // printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < index - 1; i++) {
        fprintf(fileOut, "%c", encryptedArray[i]);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        // printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    int shift = atoi(argv[3]);

    encrypt_text(inputFileName, outputFileName, shift);

    return 0;
}