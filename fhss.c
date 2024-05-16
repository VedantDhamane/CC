#include <stdio.h>
#include <stdlib.h>

// Function to expand each bit to a 3-bit pattern
void expandBitTo3Bits(int bit, int* expandedBits) {
    if (bit == 1) {
        expandedBits[0] = 0;
        expandedBits[1] = 0;
        expandedBits[2] = 1;
    } else {
        expandedBits[0] = 0;
        expandedBits[1] = 0;
        expandedBits[2] = 0;
    }
}

// Function to get frequency for the corresponding chunk index
int getFrequencyForChunk(int chunkIndex) {
    // Frequencies range from 100 to 900 (step of 100)
    return 100 + (chunkIndex % 9) * 100;
}

// Function to simulate sending a chunk of bits on a specific frequency
void sendChunkOnFrequency(int* chunk, int chunkIndex) {
    int freq = getFrequencyForChunk(chunkIndex);
    printf("Sending bits %d%d%d on frequency %d Hz\n", chunk[0], chunk[1], chunk[2], freq);
}

int main() {
    // Prompt the user to enter the number of bits
    int numBits;
    printf("Enter the number of bits: ");
    scanf("%d", &numBits);

    // Dynamically allocate memory for the input bits and expanded bits
    int* inputBits = (int*)malloc(numBits * sizeof(int));
    int* expandedBits = (int*)malloc(numBits * 3 * sizeof(int));

    // Prompt the user to enter each bit
    printf("Enter the bits (0 or 1):\n");
    for (int i = 0; i < numBits; i++) {
        scanf("%d", &inputBits[i]);
        if (inputBits[i] != 0 && inputBits[i] != 1) {
            printf("Invalid input. Please enter 0 or 1.\n");
            i--;  // Repeat this iteration
        }
    }

    // Expanding each bit to a 3-bit pattern
    for (int i = 0; i < numBits; i++) {
        expandBitTo3Bits(inputBits[i], &expandedBits[i * 3]);
    }

    // Sending the expanded bits in chunks of 3 on different frequencies
    for (int i = 0; i < numBits; i++) {
        sendChunkOnFrequency(&expandedBits[i * 3], i);
    }

    // Free dynamically allocated memory
    free(inputBits);
    free(expandedBits);

    return 0;
}