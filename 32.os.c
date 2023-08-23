#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int main() {
    int reference_string[MAX_PAGES] = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2}; // Example reference string
    int page_frames[MAX_FRAMES] = {-1, -1, -1}; // -1 indicates an empty frame
    int last_used[MAX_FRAMES] = {-1, -1, -1}; // To store the last usage index of each page in the frames

    int page_faults = 0;

    printf("Reference String: ");
    for (int i = 0; i < MAX_PAGES; i++) {
        printf("%d ", reference_string[i]);
    }
    printf("\n");

    for (int i = 0; i < MAX_PAGES; i++) {
        int page = reference_string[i];
        int found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (page_frames[j] == page) {
                found = 1;
                last_used[j] = i; // Update the last usage index
                break;
            }
        }

        if (!found) {
            page_faults++;

            // Find the least recently used page frame to replace
            int min_index = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (last_used[j] < last_used[min_index]) {
                    min_index = j;
                }
            }

            // Replace the least recently used page with the new page
            page_frames[min_index] = page;
            last_used[min_index] = i;
        }

        printf("Page %d -> Page Frames: ", page);
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (page_frames[j] == -1) {
                printf(" - ");
            } else {
                printf("%d ", page_frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
