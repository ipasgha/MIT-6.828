#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char** argv){
	if(argc != 2){
		write(1, "Invalid args.\n", 15);
		exit();
	}
	
	int ticks = atoi(argv[1]);
	sleep(ticks);
	exit();
	
}
