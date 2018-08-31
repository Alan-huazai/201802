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
		perror("connect");
		return -1;
	}
	char buf[1000]={0};
	int len;
	recvn(sfd,(char*)&len,sizeof(len));
	recvn(sfd,buf,len);
	int fd;
	fd=open(buf,O_RDWR|O_CREAT,0600);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	
	while(1)
	{
		recvn(sfd,(char*)&len,sizeof(len));
		if(len>0)
		{
			bzero(buf,sizeof(buf));
			recvn(sfd,buf,len);
			write(fd,buf,len);
		}
		else{
				break;
		}
	}
	close(fd);
	close(sfd);
}
