#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=4)
	{
		printf("./process_pool_server IP PORT process_num\n");
		return -1;
	}
	int pro_num=atoi(argv[3]);
	pData p=(pData)calloc(pro_num,sizeof(Data));
	make_child(p,pro_num);//创造子进程一个是pData数据，另一个是子进程的个数
	
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	printf("sfd=%d\n",sfd);
	int resue=1;
	int ret;
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));
	if(-1==ret)
	{
		perror("setsocket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	int epfd=epoll_create(1);//创建一个epoll句柄
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(pro_num+1,sizeof(struct epoll_event));
	//注册每一个描述符（pro_num+1个)
	event.data.fd=sfd;
	event.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);//注册要监听的事件类型
	
	int i;
	for(i=0;i<pro_num;i++)//循环注册每一个描述符
	{
		event.data.fd=p[i].pfd;
		event.events=EPOLLIN;
		epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].pfd,&event);
	}
	listen(sfd,pro_num);
	int new_fd;
	int nrecv;//需要处理的时间的个数
	int j;
	char flag;
	while(1)
	{
		nrecv=epoll_wait(epfd,evs,pro_num,-1);
		for(i=0;i<nrecv;i++)
		{
			if(sfd==evs[i].data.fd)//如果sfd可读
			{
				new_fd=accept(sfd,NULL,NULL);
				for(i=0;i<pro_num;i++)//遍历所有进程，找到空闲的子进程
				{
					if(0==p[i].busy)
					{
						break;
					}
				}
				send_fd(p[j].pfd,new_fd);//发送空闲的那个描述符给子进程
				p[j].busy=1;//子进程标识为忙
				printf("%d child is busy\n",p[j].pid);
				close(new_fd);
			}
			for(j=0;j<pro_num;j++)
			{
				if(evs[i].data.fd==p[j].pfd)
				{
					read(p[j].pfd,&flag,sizeof(flag));
					p[j].busy=1;
					printf("%d child id not busy\n",p[j].pfd);
				}
			}
		}
	}
}
