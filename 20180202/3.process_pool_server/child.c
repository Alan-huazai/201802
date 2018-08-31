#include "func.h"

void make_child(pData p,int pro_num)
{
	int fds[2];
	int i;
	pid_t pid;
	for(i=0;i<pro_num;i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//初始化一条管道
		pid=fork();
		if(0==pid)
		{
			close(fds[1]);//关闭写
			child_handle(fds[0]);//将管道的一端传过去
		}
		close(fds[0]);//父进程关闭读
		p[i].pid=pid;//初始化子进程
		p[i].pfd=fds[1];//子进程管道的对端
		p[i].busy=0;
		printf("p[i].pfd=%d\n",p[i].pfd);
 	}
}
void child_handle(int pfd)
{
	int new_fd;
	char c=0;
	short flag;//退出标志flag
	while(1)
	{
		recv_fd(pfd,&new_fd,&flag);
		printf("I will send file new_fd=%d\n",new_fd);
	//	sleep(5);
	//	close(new_fd);//客户端断开
		if(0==flag)
		{
			trans_file(new_fd);
		}else{
			exit(0);
		}

		write(pfd,&c,sizeof(c));//通知父进程完成了文件的传送
	}	
}
