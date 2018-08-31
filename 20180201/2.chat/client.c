#include "func.h"
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		printf("socket\n");
		return -1;
	}
	printf("sfd=%d\n",sfd);
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("connect\n");
		return -1;
	}
//	ret=send(sfd,"nihaoshuai",10,0);
//	if(-1==ret)
//	{
//		perror("send\n");
//		return -1;
//	}
//	char buf[128]={0};
//	ret=recv(sfd,buf,sizeof(buf),0);
//	if(-1==ret)
//	{
//		perror("recv\n");
//		return -1;
//	}
//	printf("I am client,%s\n",buf);
	
	char buf[128]={0};
//	ret=recv(new_fd,buf,sizeof(buf),0);
//	if(-1==ret)
//	{
//		perror("recv");
//		return -1;
//	}
//	printf("I am servce,buf=%s\n",buf);
//	ret=send(new_fd,"xiexie",6,0);
//	if(-1==ret)
//	{
//		perror("send");
//		return -1;
//	}

	fd_set rdset;//定义一个集合
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(sfd,&rdset);//监控的是0和fd
		ret=select(sfd+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(sfd,&rdset))//它在集合中，说明可读，如果管道可读就去读管道，如果管道中无数据则阻塞
			{
				memset(buf,0,sizeof(buf));
				ret=recv(sfd,buf,sizeof(buf),0);
				if(0==ret)
				{
					printf("bye bye\n");
					close(sfd);
					break;
				}
				printf("%s\n",buf);
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(ret>0)
				{
					send(sfd,buf,strlen(buf)-1,0);
					
				}else{
					printf("bye bye\n");
					close(sfd);
				}
			}
		}
	}
	close(sfd);
	return 0;
}
