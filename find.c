#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char*
fmtname(char *path)
{
  //static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  //if(strlen(p) >= DIRSIZ)
    //return p;
  //memmove(buf, p, strlen(p));
  //memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return p;
}

void find(char* dir, const char* fileName){
	int fd;
	char buf[512];
	struct dirent de;
	struct stat st;
	
	if((fd = open(dir, O_RDONLY)) < 0){
		fprintf(2, "E: cannot open %s.\n", dir);
		return;
	}
	
	if(fstat(fd, &st) < 0){
		fprintf(2, "E: cannot stat %s.\n", dir);
		close(fd);
		return;
	}
	
	switch(st.type){
		case T_FILE:
			//printf("%s..\n", fmtname(dir));
			if(strcmp(fmtname(dir), fileName) == 0)
				fprintf(1, "%s\n", dir);
			break;
		case T_DIR:
			
			strcpy(buf, dir);
			char* ptr = buf + strlen(buf);
			*ptr++ = '/';
			//printf("%s...\n", buf);
			
			while(read(fd, &de, sizeof(de)) == sizeof(de)){
				if(de.inum == 0)
					continue;
				
				memmove(ptr, de.name, DIRSIZ);
				ptr[DIRSIZ] = 0;
				if(strcmp(de.name, ".") == 0 
					|| strcmp(de.name, "..") == 0)
					continue;
				
				//printf("%s....\n", buf);
				find(buf, fileName);
			}
			break;
			
	}
	close(fd);
}

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(2, "E: Invalid args.\n");
		exit();
	}
	
	find(argv[1], argv[2]);
	exit();
	
}
