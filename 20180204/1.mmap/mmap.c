#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
int main(int argc,char*argv[])
{
	if(argc!=2)
	{
		perror("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	char *p;
	p=(char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1==p)
	{
		perror("mmap");
		return -1;
	}
	printf("%s\n",p);
	p[0]='w';
	p[1]='o';
	p[2]='r';
	p[3]='l';
	p[4]='d';
	int ret=munmap(p,4096);
	if(-1==ret)
	{
		perror("munmap");
		return -1;
	}
	return 0;
}
