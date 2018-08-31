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
typedef struct{
	int len;
	char buf[1000];
}train;
void make_child(pData,int);
void child_handle(int pfd);
void send_fd(int pfd,int fd,short);
void recv_fd(int,int*,short*);
void trans_file(int);
int sendn(int ,char*,int);
