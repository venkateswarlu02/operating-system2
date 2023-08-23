#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100

// Define a structure for the message
struct Message {
    long type;
    char text[MAX_MESSAGE_SIZE];
};

int main() {
    key_t key;
    int msgqid;
    struct Message message;

    // Generate a key for the message queue
    key = ftok(".", 'm');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or get the message queue
    msgqid = msgget(key, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        perror("msgget");
        exit(1);
    }

    
    if (fork() == 0) {
        message.type = 1;
        strcpy(message.text, "Hello from sender!");

        
        if (msgsnd(msgqid, &message, sizeof(message.text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("Sender: Message sent\n");
        exit(0);
    }

    
    if (fork() == 0) {
       
        if (msgrcv(msgqid, &message, sizeof(message.text), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Receiver: Received message: %s\n", message.text);
        exit(0);
    }

   
    wait(NULL);
    wait(NULL);

   
    if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
