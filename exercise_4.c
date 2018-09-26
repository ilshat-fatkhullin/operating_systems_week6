#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigstop_handler()
{
    printf("Received SIGSTOP\n");
}

void sigusr1_handler()
{
    printf("Received SIGUSR1\n");
}

int main()
{
    signal(SIGSTOP, sigstop_handler);
    signal(SIGUSR1, sigusr1_handler);
    while (1)
    {
        sleep(1);
    }
}