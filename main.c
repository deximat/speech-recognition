#include <stdio.h>
#include <stdlib.h>

typedef struct WAVE {
    char riff[4];
    int fileSize;
    char formatName[4]
} Wave;

/**
* Utility method that swaps two elements
*/
void swap (char * a, char * b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

/**
* This is actually reversing bytes.
*/
void bigToLittleEndian(char* startAddress, int size) {
    int i;
    // reverse
    for (i = 0; i < size / 2; i++) {
        swap(startAddress + i, (startAddress + size - 1 - i));
    }
}

/**
* Read wave file
*/
void readWave(char* path, Wave* wave) {
    FILE* file = fopen(path, "r");

    // read wave string BIG
    fscanf(file, "%4s", &wave->riff);
    // read file length LITTLE
    fscanf(file, "%4s", (char*) &wave->fileSize);
    // read format name
    fscanf(file, "%4s", &wave->formatName);

}

/**
* Print wave file
*/
void printOnScreen(Wave* wave) {
    printf("%4s\n", wave->riff);
    printf("%d\n", wave->fileSize);
    printf("%4s\n", wave->formatName);
}

int main()
{
    Wave wave;
    readWave("test.wav", &wave);
    printOnScreen(&wave);
    return 0;
}
