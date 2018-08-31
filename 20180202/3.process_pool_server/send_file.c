#include "func.h"

void trans_file(int new_fd)
{
	train t;
	strcpy(t.buf,FILENAME);
	t.len=strlen(t.buf);
	sendn(new_fd,(char*)&t,4+t.len);
	int fd;
	fd=open(FILENAME,O_RDONLY);
	if(-1==fd)
	{
		perror("open");
		return;
	}
	int ret;
	while(bzero(&t,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
	{
		ret=sendn(new_fd,(char *)&t,4+t.len);
		if(-1==ret)
		{
			goto end;
		}
	}
	t.len=0;
	sendn(new_fd,(char *)&t,4);
end:
	close(new_fd);

}

