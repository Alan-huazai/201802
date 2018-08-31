#include "func.h"
void recv_file(char buf1[128],char buf2[128],int sfd)
{
	char buf3[1000];
	int len;
	int fd;
	if(strcmp(buf1,"gets")==0)
	{
		bzero(buf3,sizeof(buf3));
		recvn(sfd,(char*)&len,sizeof(len));//先拿前4个字节，可以得到小火车中存放的数据的长度
		printf("recv_len=%d\n",len);
		recvn(sfd,buf3,len);//再接受小火车中的真正内容，存到buf3中
		printf("buf2=%s,len2=%ld\n",buf2,strlen(buf2));
		if(strcmp(buf3,buf2)!=0)//buf2和buf3两个命令进行比较
		{
			printf("buf3=%s,len3=%ld\n",buf3,strlen(buf3));
			return;
		}
		fd=open(buf3,O_RDWR|O_CREAT,0666);//open用于打开并创建文件
		if(-1==fd)
		{
			perror("open");
			return ;
		}
	}
	while(1)
	{
		recvn(sfd,(char*)&len,sizeof(len));//取到小火车的长度
		if(len>0)
		{
			if(strcmp(buf1,"gets")==0)
			{
				bzero(buf3,sizeof(buf3));
				recvn(sfd,buf3,len);//接受命令，并且存入buf3中
				write(fd,buf3,len);//将buf3前len个字节写入fd相关联的fd描述符中
			}else{
				bzero(buf3,sizeof(buf3));
				recvn(sfd,buf3,len);
				printf("%s\n",buf3);
				}
		}else{
				close(fd);
				printf("finish\n");
				return;
				}
	}
}
