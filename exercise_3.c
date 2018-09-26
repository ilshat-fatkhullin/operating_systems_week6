#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler()
{
    printf("Received SIGINT\n");
}

int main()
{
    signal(SIGINT, handler);
    while (1)
    {
        sleep(1);
    }
}