#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    int shmid;          // Shared memory ID
    char *shm_ptr;      // Pointer to shared memory
    char buffer[100];   // Buffer for data to be written

    // Create a shared memory segment
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        return 1;
    }

    
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
       
        printf("Child process reading from shared memory: %s\n", shm_ptr);

       
        shmdt(shm_ptr);
    } else {
        printf("Parent process writing to shared memory: ");
        fgets(buffer, sizeof(buffer), stdin);
        strncpy(shm_ptr, buffer, SHM_SIZE);

        
        wait(NULL);

        
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
