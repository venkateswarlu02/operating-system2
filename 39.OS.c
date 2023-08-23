#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TRACKS 200
#define INITIAL_POSITION 53

// Function to sort an array of integers
void sortArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to perform C-SCAN disk scheduling
void cScan(int requests[], int size, int currentPosition) {
    int seekSequence[size + 3]; // Extra space for head movement to the end and back
    int headMovement = 0;
    int index = 0;

    // Sort the request array
    sortArray(requests, size);

    // Move to the end of the disk
    while (index < size && requests[index] < currentPosition) {
        index++;
    }

    // Service requests in the forward direction
    for (int i = index; i < size; i++) {
        headMovement += abs(currentPosition - requests[i]);
        currentPosition = requests[i];
        seekSequence[i - index] = requests[i];
    }

    // Move to the beginning of the disk
    headMovement += currentPosition; // Move back to the beginning
    currentPosition = 0;
    seekSequence[size - index] = 0;

    // Service requests that were not served in the first pass
    for (int i = 0; i < index; i++) {
        headMovement += abs(currentPosition - requests[i]);
        currentPosition = requests[i];
        seekSequence[size - index + i + 1] = requests[i];
    }

    printf("C-SCAN Seek Sequence: ");
    for (int i = 0; i < size + 1; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Head Movement: %d\n", headMovement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int numRequests = sizeof(requests) / sizeof(requests[0]);

    cScan(requests, numRequests, INITIAL_POSITION);

    return 0;
}
