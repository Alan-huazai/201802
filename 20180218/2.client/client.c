#include "func.h"
int main(int argc,char*argv[])
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
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int epfd=epoll_create(1);
	struct epoll_event event,evs[2];
	//两个描述符0号描述符和sfd描述符
	event.data.fd=sfd;
	event.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	event.data.fd=0;
	//event.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
	int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	char buf[128];
	char buf1[128];
	char buf2[128];
	int i;
	train t;//小火车
	int j;
	int nrecv;//返回要处理的事件个数
	while(1)
	{
		nrecv=epoll_wait(epfd,evs,2,-1);//返回要处理的事件个数
		for(i=0;i<nrecv;i++)
		{
			if(evs[i].data.fd==0)//0号描述符可读，就读0号描述符
			{
				bzero(buf,sizeof(buf));
				read(0,buf,sizeof(buf));//返回字节个数
				printf("before send len=%ld buf=%s\n",strlen(buf),buf);
				t.len=strlen(buf);
				strcpy(t.buf,buf);//将buf起始地址给t.buf
				char *delim=" \n";
				char *temp;
				temp=strtok(buf,delim);//分割字符串
				printf("buf1 =%s\n",temp);
				strcpy(buf1,temp);//temp中放的是\n之前的字符串（即命令）
				while((temp=strtok(NULL,delim)))//再次使用，先要将buf置为NULL
				{
					printf("buf2=%s\n",temp);
					strcpy(buf2,temp);//buf2中存放的是命令
				}
				sendn(sfd,(char*)&t,4+t.len);//使用sfd描述符发送一列小火车，
				if(strcmp(buf1,"puts")==0)//??
				{
					send_file(sfd,buf2);
					bzero(buf1,sizeof(buf1));
					bzero(buf2,sizeof(buf2));
				}
			}
			if(evs[i].data.fd==sfd)//sfd可读，就读sfd
			{
				printf("begin recv_file\n");
				recv_file(buf1,buf2,sfd);//通过sfd描述符接受，输入命令后显示的内容
				bzero(buf1,sizeof(buf1));
				bzero(buf2,sizeof(buf2));
			}
		}
	}
}
