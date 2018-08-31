#include "func.h"

void sig(int signum)
{
		printf("%d is coming\n",signum);
}

void send_file(int new_fd,char buf[128])
{
		signal(SIGPIPE,sig);
		train t;
		int fd;
		bzero(&t,sizeof(t));
		fd=open(buf,O_RDONLY);
		if(-1==fd)
		{
				perror("open");
				strcpy(t.buf,"find fail");
				t.len=strlen(t.buf);
				sendn(new_fd,(char *)&t,4+t.len);
				return ;
		}
		strcpy(t.buf,buf);//鎶婃枃浠跺悕鏀惧叆buf
		t.len=strlen(t.buf);
		sendn(new_fd,(char*)&t,4+t.len);//鍙戦€佹枃浠跺悕鐏溅缁欏绔?
		printf("send_filename=%s, len=%ld\n",buf,strlen(buf));
		while(bzero(&t,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
		{
				sendn(new_fd,(char*)&t,4+t.len);
		}
		t.len=0;
		sendn(new_fd,(char*)&t,4);//浠ｈ〃鏂囦欢缁撴潫
		printf("sendn finish\n");
		close(fd);
		//	close(new_fd);
}

