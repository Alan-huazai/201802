#include "func.h"
//创建子进程
void make_child(pData p,int pro_num)
{
	int i;
	int fds[2];
	pid_t pid;
	for(i=0;i<pro_num;i++)//创建子进程
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//创造一对未命名的，相互连接的UNIX套接字(即新建一对socket用来实现通信)
		pid=fork();
		if(0==pid)
		{
			close(fds[1]);//关闭写端
			child_handle(fds[0]);//将套接字一端传过去
		}
		close(fds[0]);//父进程关闭读端
		//初始化子进程信息
		p[i].pid=pid;
		p[i].pfd=fds[1];//子进程管道的对端
		p[i].busy=0;
		printf("p[i].pfd=%d\n",p[i].pfd);//第一个是父进程id,其他是子进程id
	}
}
void child_handle(int pfd)
{
	int new_fd;
	char c=0;
	while(1)//子进程接受描述符
	{
		recv_fd(pfd,&new_fd);
		printf("I will send new_fd=%d\n",new_fd);
		//trans_file(new_fd);//把文件描述符new_fd对应的文件发送给对端
		//write(pfd,&c,sizeof(1));//把一个字节写入pfd对应的文件中
		recv_file(new_fd);
	}
}
