#include "kernel/types.h"
#include "user/user.h"

int main(){
	int fwdPipe[2], bkwdPipe[2];
	pipe(fwdPipe);
	pipe(bkwdPipe);
	
	int pid = fork();
	if(pid < 0){
		write(1, "E: fork error.\n", 16);
		exit();
	}
	else if(pid == 0){
		close(fwdPipe[1]);
		close(bkwdPipe[0]);
		
		char buf[30];
		memset(buf, 0, 30);
		read(fwdPipe[0], buf, 30);
		printf("%d: receives %s.\n", getpid(), buf);
		write(bkwdPipe[1], "pong", 6);
		exit();
	}
	else{
		close(fwdPipe[0]);
		close(bkwdPipe[1]);
		write(fwdPipe[1], "ping", 6);
		
		wait();
		char buf[30];
		memset(buf, 0, 30);
		read(bkwdPipe[0], buf, 30);
		printf("%d: receives %s.\n", getpid(), buf);
		exit();
	}
	exit();
}
