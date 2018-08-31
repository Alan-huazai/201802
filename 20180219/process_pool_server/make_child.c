#include "func.h"

void make_child(pData p,int pro_num)
{
		int i;
		int fds[2];
		pid_t pid;
		for(i=0;i<pro_num;i++)
		{
				socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
				pid=fork();
				if(0==pid)
				{
						close(fds[1]);
						child_handle(fds[0]);
				}
				close(fds[0]);
				p[i].pid=pid;
				p[i].pfd=fds[1];///将管道对端给出，从而父进程才能知道是否可读，从而连接
				p[i].busy=0;
				printf("p[i].pfd=%d\n",p[i].pfd);////第一个是父进程id，其他的是子进程id
		}
}

void child_handle(int pfd) 
{
		int new_fd;
		char c=0;
		while(1)
		{
				recv_fd(pfd,&new_fd);
				printf("I will send file new_fd=%d\n",new_fd);
//				trans_file(new_fd);		
				recv_file(new_fd);
//				write(pfd,&c,sizeof(c));//閫氱煡鐖惰繘绋嬫垜瀹屾垚浜嗘枃浠跺彂閫?	}
}
}
