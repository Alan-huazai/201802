#include "func.h"

int main()
{
	int fds[2];
	pipe(fds);//创建一条无名管道
	if(!fork())
	{
		close(fds[1]);
		int fd;
		read(fds[0],&fd,sizeof(fd));
		printf("I am child,fd=%d\n",fd);
		char buf[128]={0};
		read(fds[0],buf,sizeof(buf));
		exit(0);
	}else{
		close(fds[0]);
		int fd;
		fd=open("file",O_RDWR);
		int ret;
		ret=write(fds[1],&fd,sizeof(fd));
		printf("I am parents,fd=%d\n",fd);
		printf("ret=%d\n",ret);
		wait(NULL);
	}
}
