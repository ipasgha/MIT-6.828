#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argv[1])
    {
        int secs = atoi(argv[1]);
        printf("sleep for %d secs...\n", secs);
        sleep(secs);
        printf("finish\n");
    }
    exit(0);
}