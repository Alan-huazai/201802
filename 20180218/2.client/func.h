#ifndef __HEAD_H__
#define __HEAD_H__
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/uio.h>
#define FILENAME "file"
typedef struct{
	pid_t pid;
	int pfd;
	short busy;
}Data,*pData;
//定义小火车
typedef struct{
	int len;
	char buf[1000];
}train;

int sendn(int sfd,char *buf,int len);
void recvn(int sfd,char *buf,int len);
void send_file(int new_fd,char buf[128]);//发送命令
void recv_file(char buf1[128],char buf2[128],int sfd);//接受执行命令后的效果
#endif
