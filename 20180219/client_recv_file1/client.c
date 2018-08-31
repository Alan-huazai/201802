#include "func.h"

int main(int argc,char *argv[])
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
		ser.sin_port=htons(atoi(argv[2]));//涓€瀹氳鐢╤tons
		ser.sin_addr.s_addr=inet_addr(argv[1]);
		int epfd=epoll_create(1);
		struct epoll_event event,evs[2];
		event.events=EPOLLIN;
		event.data.fd=sfd;
		epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
		event.data.fd=0;
		epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
		int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
		if(-1==ret)
		{
				perror("connect");
				return -1;
		}

		//		recvn(sfd,(char*)&len,sizeof(len));//循环接收
		//		recvn(sfd,buf,len);
		//		int fd;
		//		fd=open(buf,O_RDWR|O_CREAT,0666);
		//		if(-1==fd)
		//		{
		//				perror("open");
		//				return -1;
		//		}
		char buf[128];
		char buf1[128];
		char buf2[128];
		int i;
		train t;
		int j;
		while(1)
		{
				ret=epoll_wait(epfd,evs,2,-1);
				for(i=0;i<ret;i++)
				{
						if(evs[i].data.fd==0)
						{
								bzero(buf,sizeof(buf));
								read(0,buf,sizeof(buf));
								printf("befor send len=%ld buf=%s\n",strlen(buf),buf);
								bzero(&t,sizeof(t));
								t.len=strlen(buf);
								strcpy(t.buf,buf);
								char *delim=" \n";
								char *temp;
								temp=strtok(buf,delim);
								printf("buf1=%s\n",temp);
								strcpy(buf1,temp);
								while((temp=strtok(NULL,delim)))
								{printf("buf2=%s\n",temp);
										strcpy(buf2,temp);}
								sendn(sfd,(char *)&t,4+t.len);
								if(strcmp(buf1,"puts")==0)
								{
									send_file(sfd,buf2);
									bzero(buf1,sizeof(buf1));
									bzero(buf2,sizeof(buf2));
								}
						}
						if(evs[i].data.fd==sfd)
						{
								printf("begin recv_file\n");
								recv_file(buf1,buf2,sfd);
								bzero(buf1,sizeof(buf1));
								bzero(buf2,sizeof(buf2));

						}
				}
		}

//		close(fd);
// 		close(sfd);
}

