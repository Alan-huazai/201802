#include "func.h"
void rm(char buf[128],int new_fd)
{
	int fd;
	if((fd=open(buf,O_RDWR))<0)
	{
		printf("erro open\n");
		return;
	}
	int ret=unlink(buf);
	if(ret<0)
	{
		printf("erro unlink\n");
		return;
	}
}
