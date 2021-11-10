#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

static void sighandler(int signo)
{
    // catching signal SIGINT
    if (signo == SIGINT)
    {
        int file = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (file == -1)
        {
            printf("Error: %s\n", strerror(errno));
            return;
        }
        char buffer[] = "Program exited due to SIGINT\n";
        int err = write(file, buffer, sizeof(buffer));
        if (err == -1)
        {
            printf("Error: %s\n", strerror(errno));
            return;
        }
        exit(0);
    }

    // catching signal SIGUSR1
    if (signo == SIGUSR1)
    {
        printf("PPID: %d\n", getppid());
    }
}

int main()
{
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while (1)
    {
        printf("PID: %d\n", getpid());
        sleep(1);
    }
    return 0;
}
