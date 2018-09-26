#include <stdio.h>
#include <memory.h>
#include <unistd.h>

int main() {
    int pipe_array[2];
    pipe(pipe_array);
    char input_line[] = "Input from parent process";
    int pid = fork();
    if (pid == 0) {
        write(pipe_array[1], input_line, sizeof(input_line) + 1);
    } else {
        sleep(1);
        char output_line[strlen(input_line)];
        read(pipe_array[0], output_line, sizeof(output_line) + 1);
        printf("%s", output_line);
    }
}