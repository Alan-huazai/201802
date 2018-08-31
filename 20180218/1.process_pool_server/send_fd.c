#include "func.h"

void send_fd(int pfd,int fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct iovec iov[2];
	char buf[10]="hello";//两个缓冲区
	char buf1[10]="world";
	iov[0].iov_base=buf;
	iov[0].iov_len=5;
	iov[1].iov_base=buf1;
	iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	struct cmsghdr *cmsg;//附属数据的缓冲区
	int len=CMSG_LEN(sizeof(int));//宏
	cmsg=(struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	*(int*)CMSG_DATA(cmsg)=fd;
	msg.msg_control=cmsg;//辅助数据的地址
	msg.msg_controllen=len;
	int ret;
	ret=sendmsg(pfd,&msg,0);//成功返回读取的字节数
	if(-1==ret)
	{
		perror("sendmsg");
		return;
	}
}

void recv_fd(int pfd,int *fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct iovec iov[2];
	char buf[10]="hello";//两个缓冲区
	char buf1[10]="world";
	iov[0].iov_base=buf;
	iov[0].iov_len=5;
	iov[1].iov_base=buf1;
	iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	struct cmsghdr *cmsg;//附属数据的缓冲区
	int len=CMSG_LEN(sizeof(int));//宏
	cmsg=(struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	msg.msg_control=cmsg;//辅助数据的地址
	msg.msg_controllen=len;
	int ret;
	ret=recvmsg(pfd,&msg,0);//成功返回读取的字节数
	if(-1==ret)
	{
		perror("sendmsg");
		return;
	}
	*fd=*(int*)CMSG_DATA(cmsg);//接受描述符
}
