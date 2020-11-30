#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

static void signalhandler(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    if (signo == SIGINT)
    {
        int file = open("log.txt", O_APPEND | O_CREAT | O_WRONLY, 0664);
        if (file == -1)
        {
            printf("errno: %d: %s", errno, strerror(errno));
            exit(1);
        }

        char m[] = "Recieved SIGINT, exiting...\n";
        write(file, m, sizeof(m) - 1);
        close(file);
        exit(0);
    }
}

int main()
{
    signal(SIGINT, signalhandler);
    signal(SIGUSR1, signalhandler);

    while (1)
    {
        printf("My PID is: %d\n", getpid());
        sleep(1);
    }
    //should never reach this
    return 0;
}