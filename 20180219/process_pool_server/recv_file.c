
#include"func.h"

void rec(char buf1[128],char buf2[128],int sfd)
{
		char buf3[1000];
		int len;
		int fd;
		if(strcmp(buf1,"puts")==0)
		{
				recvn(sfd,(char*)&len,sizeof(len));
				recvn(sfd,buf3,len);
				if(strcmp(buf3,buf2)!=0){printf("%s\n",buf3);return;}
				fd=open(buf3,O_RDWR|O_CREAT,0666);
				if(-1==fd)
				{
						perror("open");
						return ;
				}
		}

		while(1){
				recvn(sfd,(char*)&len,sizeof(len));//瀵邦亞骞嗛幒銉︽暪
				if(len>0){
						if(strcmp(buf1,"puts")==0)
						{
								bzero(buf3,sizeof(buf3));		
								recvn(sfd,buf3,len);
								write(fd,buf3,len);
						}
				}else{printf("finish\n");break;close(fd);}

		}
}

