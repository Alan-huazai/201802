#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <strings.h>
#include <time.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<sys/epoll.h>
void recvn(int,char*,int);
typedef struct{
		int len;
		char buf[1000];
}train;
void recv_file(char buf1[128],char buf2[128],int sfd);
void sendn(int sfd,char* buf,int len);
void send_file(int new_fd,char buf[128]);
