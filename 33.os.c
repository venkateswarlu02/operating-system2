#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int main() {
    int reference_string[MAX_PAGES] = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2}; // Example reference string
    int page_frames[MAX_FRAMES] = {-1, -1, -1}; // -1 indicates an empty frame

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
                break;
            }
        }

        if (!found) {
            page_faults++;

            // Find the page that will be used furthest in the future
            int max_future_index = -1;
            int max_future_page = -1;
            for (int j = 0; j < MAX_FRAMES; j++) {
                int future_index = INT_MAX;
                for (int k = i + 1; k < MAX_PAGES; k++) {
                    if (reference_string[k] == page_frames[j]) {
                        future_index = k;
                        break;
                    }
                }
                if (future_index > max_future_index) {
                    max_future_index = future_index;
                    max_future_page = page_frames[j];
                }
            }

            // Replace the page that will be used furthest in the future
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (page_frames[j] == max_future_page) {
                    page_frames[j] = page;
                    break;
                }
            }
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
