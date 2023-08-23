#include <stdio.h>
#include <pthread.h>

void *print_message(void *message) {
    printf("%s\n", (char *)message);
    return NULL;
}

int main() {
    pthread_t thread;
    char *message = "Hello, from the thread!";
    
    pthread_create(&thread, NULL, print_message, (void *)message);
    pthread_join(thread, NULL);
    
    return 0;
}
