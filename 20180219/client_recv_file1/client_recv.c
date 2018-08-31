#include"func.h"

void recv_file(char buf1[128],char buf2[128],int sfd)
{
		char buf3[1000];
		int len;
		int fd;
		if(strcmp(buf1,"gets")==0)
		{
				bzero(buf3,sizeof(buf3));
				recvn(sfd,(char*)&len,sizeof(len));
				printf("recv_len=%d\n",len);
    			recvn(sfd,buf3,len);
				printf("buf2=%s, len2=%ld\n",buf2,strlen(buf2));
				if(strcmp(buf3,buf2)!=0){printf("buf3=%s,len3=%ld\n",buf3,strlen(buf3));return;}
				fd=open(buf3,O_RDWR|O_CREAT,0666);
				if(-1==fd)
				{
						perror("open");
						return ;
				}
		}

		while(1){
				recvn(sfd,(char*)&len,sizeof(len));//寰幆鎺ユ敹
				if(len>0){
						if(strcmp(buf1,"gets")==0)
						{
							bzero(buf3,sizeof(buf3));		
							recvn(sfd,buf3,len);
							write(fd,buf3,len);
						}else{
							bzero(buf3,sizeof(buf3));
							recvn(sfd,buf3,len);	
							printf("%s\n",buf3);}
				}else{close(fd);printf("finish\n");return;}

		}
}
