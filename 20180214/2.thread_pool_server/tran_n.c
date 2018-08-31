#include "head.h"

int sendn(int sfd,char *buf,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=send(sfd,buf+total,len-total,0);
		if(-1==ret)
		{
			printf("errno=%d\n",errno);
			return -1;
		}
		total=total+ret;//总共发送的字节数
	}
	return 0;
}

void recvn(int sfd,char *buf,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=recv(sfd,buf+total,len-total,0);
		if(-1==ret)
		{
			printf("errno=%d\n",errno);
			return;
		}
		total=total+ret;
	}
}
