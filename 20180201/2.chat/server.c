#include "func.h"
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	printf("sfd=%d  ",sfd);
	int resue=1;
	int ret;
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));
	if(-1==ret)
	{
		perror("setsockopt");
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
	listen(sfd,10);//监听sfd
	int new_fd;
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int len=sizeof(client);
	//接受请求
	new_fd=accept(sfd,(struct sockaddr*)&client,&len);
	printf("new_fd=%d,ip=%s,port=%d\n",new_fd,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	char buf[128]={0};
	//创建一个epoll句柄
	int epfd=epoll_create(1);
	struct epoll_event event,evs[2];
	//监控的是读事件
	event.events=EPOLLIN;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}
	//监控new_fd是否可读
	event.data.fd=new_fd;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}
	int i;
	int ret1;
	while(1)
	{
		bzero(evs,sizeof(evs));
//#ifdef DEBUG
//		printf("before epoll_wait\n");
//#endif
		ret=epoll_wait(epfd,evs,2,-1);
		for(i=0;i<ret;i++)
		{
//			printf("evs[i].data.fd=%d",evs[i].data.fd);
			if(new_fd==evs[i].data.fd)
			{
				memset(buf,0,sizeof(buf));
				ret1=recv(new_fd,buf,sizeof(buf),0);
				if(0==ret1)
				{
					printf("bye bye\n");
					close(sfd);
					close(new_fd);
					break;
				}
				printf("%s\n",buf);
			}
			if(0==evs[i].data.fd)
			{
				memset(buf,0,sizeof(buf));
				ret1=read(0,buf,sizeof(buf));
				if(ret1>0)
				{
					//发送给远端主机
					send(new_fd,buf,strlen(buf)-1,0);
				}else{
					printf("bye bye");
					close(sfd);
					close(new_fd);
					break;
				}
			}
		}
	}
		return 0;	
}

