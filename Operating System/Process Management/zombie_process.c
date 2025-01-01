#include <stdio.h> //perror
#include <stdlib.h>
#include <unistd.h> //fork,getpid,getppid,
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

/**A Zombie process is created when a child process exits, but the parent does not immediately call wait() to clean it up
 */
int main () {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror ("Fork Failed");
        exit(1);
    }

    else if (pid == 0) {
        printf("Child Process (PID: %d) is running Parent Process (PID: %d)\n",getpid(),getppid());
        printf("Child Process (PID: %d) is exiting\n",getpid());
        exit(0);
    } else {
        printf("Parent Process (PID: %d) is running\n",getpid());
        printf("Parent Process sleeping to create a zombie process\n");
        sleep(10);
        printf("Child Process (PID: %d)\n",pid);
        wait(NULL);
        printf("Parent process cleaned up the zombie.\n");
    }
    return 0;
}