#include "func.h"
int main()
{
	struct iovec iov[2];
	char buf1[10]={0};
	char buf2[10]={0};
	iov[0].iov_base=buf1;
	iov[0].iov_len=5;
	iov[1].iov_base=buf2;
	iov[1].iov_len=5;
	int fd=open("file1",O_RDWR);
	readv(fd,iov,2);
	printf("buf1=%s,buf2=%s",buf1,buf2);
	close(fd);
	return 0;
}


