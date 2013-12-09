#include <stdio.h>
#include <stdlib.h>

// TODO: check why printf doesn't work well with not null terminated strings if length is specified
typedef struct WaveParameters {
    char subchunk1Id[5];
    int  subchunk1Size;
    short audioFormat;
    short numberOfChannels;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bitsPerSample;
} WaveParameters;

typedef struct Wave {
    char riff[5];
    int fileSize;
    char formatName[5];
    WaveParameters waveParameters;
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
* Read wave parameters
*/
void readWaveParameters(FILE* file, WaveParameters* waveParameters) {
    // read subchunk1 id
    fscanf(file, "%4s", &waveParameters->subchunk1Id);
    // read subchunk1 size
    fscanf(file, "%4s", (char*) &waveParameters->subchunk1Size);
    // read audio format 1 - PCB (other than 1 are compressed)
    fscanf(file, "%2s", (char*) &waveParameters->audioFormat);
    // read number of channels
    fscanf(file, "%2s", &waveParameters->numberOfChannels);
    // read sample rate
    fscanf(file, "%4s", &waveParameters->sampleRate);
    // read byte rate
    fscanf(file, "%4s", &waveParameters->byteRate);
    // read block align
    fscanf(file, "%2s", &waveParameters->blockAlign);
    // read bits per sample
    fscanf(file, "%2s", &waveParameters->bitsPerSample);
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

    // read wave parameters
    readWaveParameters(file, &wave->waveParameters);
}

/**
* Print wave parameters.
*/
void printWaveParameters(WaveParameters* waveParameters) {
    printf("************ WAVE PARAMETERS **************\n");
    printf("Subchunk1Id: %4s\n", waveParameters->subchunk1Id);
    printf("Subchunk1Size: %d\n", waveParameters->subchunk1Size);
    printf("Audio format: %d\n", waveParameters->audioFormat);
    printf("Number of channels: %d\n", waveParameters->numberOfChannels);
    printf("Sample rate: %d\n", waveParameters->sampleRate);
    printf("Byte rate: %d\n", waveParameters->byteRate);
    printf("Block align: %d\n", waveParameters->blockAlign);
    printf("Bits per sample: %d\n", waveParameters->bitsPerSample);
}

/**
* Print wave file
*/
void printOnScreen(Wave* wave) {
    printf("%4s\n", wave->riff);
    printf("%d\n", wave->fileSize);
    printf("%4s\n", wave->formatName);
    printWaveParameters(&wave->waveParameters);
}

int main()
{
    Wave wave;
    readWave("test2.wav", &wave);
    printOnScreen(&wave);
    return 0;
}
