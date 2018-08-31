#include "func.h"
void sig(int signum)//信号处理函数
{
	printf("%d is coming\n",signum);
}
void send_file(int new_fd,char buf[128])
{
	signal(SIGPIPE,sig);
	train t;//小火车
	int fd;
	bzero(&t,sizeof(t));
	fd=open(buf,O_RDONLY);//建立一条文件到设备的访问路径，调用成功返回一个描述符
	if(-1==fd)
	{
		perror("open");
		strcpy(t.buf,"find fail");
		t.len=strlen(t.buf);
		sendn(new_fd,(char*)&t,4+t.len);//将连接失败的信息通过小火车发送过去
		return;
	}
	strcpy(t.buf,buf);//建立成功，就将buf中的数据给小火车
	t.len=strlen(t.buf);
	sendn(new_fd,(char*)&t,4+t.len);//发送
	printf("send_filename%s,len=%ld\n",buf,strlen(buf));
	while(bzero(&t,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
	{
		sendn(new_fd,(char*)&t,4+t.len);
	}
	t.len=0;
	sendn(new_fd,(char*)&t,4);
	printf("sendn finish\n");
	close(fd);
}
