#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    int parent_fd[2], child_fd[2];
    pid_t pid;
    const char pong[5] = "pong", ping[5] = "ping";
    char childbuf[10], parentbuf[10];

    if(pipe(parent_fd) == -1)
    {
        printf("fail to create pipe for parent\n");
        return -1;
    }

    pid = fork();
    if(pid == -1)
    {
        printf("fail to fork!\n");
        return -1;
    }

    if(pid)//parent
    {
        if(write(parent_fd[1], ping, 5) == -1)
        {
            printf("fail to send pong\n");
            return -1;
        }
        else
            close(parent_fd[1]);
    }
    else//child
    {
        if(read(parent_fd[0], parentbuf, 10) == -1)
        {
            printf("fail to receive pong\n");
            return -1;
        }
        else
        {
            close(parent_fd[0]);
            printf("%d: received %s\n", getpid(), parentbuf);
            return 0;
        }
    }

    if(pipe(child_fd) == -1)
    {
        printf("fail to create pipe for child\n");
        return -1;
    }

    pid = fork();
    if(pid == -1)
    {
        printf("fail to fork\n");
        return -1;
    }

    if(pid)//parent
    {
        if(read(child_fd[0], childbuf, 10) == -1)
        {
            printf("fail to receive ping\n");
            return -1;
        }
        else
        {
            close(child_fd[0]);
            printf("%d: received %s\n", getpid(), childbuf);
            return 0;
        }
    }
    else//child
    {
        if(write(child_fd[1], pong, 5) == -1)
        {
            printf("fail to send pong\n");
            return -1;
        }
        else
        {
            close(child_fd[1]);
            return 0;
        }
    }
    
}