#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**An orphan process is created when the parent process terminates before the child process, leaving the child to be adopted by the init(or systemd) process */

int main () {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        exit(1);

    } else if (pid == 0) {
        printf("Child Process (PID: %d) Parent Process (PID: %d)\n",getpid(),getppid());
        sleep(10);
        printf("Child Process (PID: %d) Parent Process (PID: %d)\n",getpid(),getppid());

    } else {
        printf("Parent Process (PID: %d)\n",getpid());
        printf("Parent Process is running\n");
        printf("Parent Process exiting without child Process existing\n");
        exit(0);
    }
    return 0;
}