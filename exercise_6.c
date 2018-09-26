#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>

void sigint_handler() {
    exit(0);
}

int main() {
    int pipe_array[2];

    pipe(pipe_array);

    printf("Parent forks child 1.\n");
    int pid1 = fork();

    if (pid1 == 0) {
        //CHILD 1
        sleep(1);
        int pid2;
        read(pipe_array[0], &pid2, sizeof(int));
        close(pipe_array[0]);
        printf("Child 1 recieved pid. Pid = %d.\n", pid2);
        sleep(3);
        printf("Child 1 stops child 2.\n");
        kill(pid2, SIGSTOP);
        sleep(1);
        printf("Child 1 continues child 2.\n");
        kill(pid2, SIGCONT);
        sleep(1);
        printf("Child 1 terminates child 2.\n");
        kill(pid2, SIGINT);
    } else {
        printf("Parent forks child 2.\n");
        int pid2 = fork();

        if (pid2 == 0) {
            //CHILD 2

            signal(SIGINT, sigint_handler);

            while (1) {
                sleep(1);
            }
        } else {
            //PARENT
            printf("Parent writes pid to child 1. Pid = %d.\n", pid2);
            write(pipe_array[1], &pid2, sizeof(int));
            close(pipe_array[1]);
            printf("Parent starts to wait for to child 2.\n");
            int status = 0;
            waitpid(pid2, &status, 0);
            printf("Parent finished its waiting.\n");
        }
    }
}