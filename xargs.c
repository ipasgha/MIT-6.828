#include "kernel/types.h"
#include "user/user.h"

char args[10][64];
int fillArgs();

int main(int argc, char** argv){
	int num = fillArgs();
	
	char *xArgs[32];
	for(int i = 1; i < argc; ++i)
		xArgs[i-1] = argv[i];
	for(int i = 0; i < num; ++i)
		xArgs[argc-1+i] = args[i];
		
	int pid = fork();
	if(pid < 0){
		fprintf(2, "E: fork error.\n");
		exit();
	}
	else if(pid == 0){
		exec(argv[1], xArgs);
		fprintf(2, "exec failed!\n");
		exit();
	}
	else{
		wait();
	}
	
	exit(); 
	
}

int fillArgs(){
	for(int i = 0; i < 10; ++i)
		memset(args[i], 0, 64);	
	
	char buf[64];
	memset(buf, 0, 64);
	
	char temp;
	int pos = 0;
	char* ptr = buf;
	while(read(0, &temp, sizeof(temp)) == sizeof(temp)){
		switch(temp){
			case '\n':
				*ptr = '\0';
				strcpy(args[pos], buf);
				return strlen(args[pos]) == 0 ? pos : pos+1;
			case ' ':
				*ptr = '\0';
				strcpy(args[pos], buf);
				++pos;
				memset(buf, 0, 64);
				ptr = buf;
				break;
			default:
				*ptr = temp;
				++ptr;
				break;
		}
	}
	return strlen(args[pos]) == 0 ? pos : pos+1;
}








