#include "func.h"
void recv_file(int new_fd)
{
	int len;
	int i,j,k;
	char buf[128];
	char buf1[128];
	char buf2[128];
	train t;
	while(1)
	{
		recvn(new_fd,(char*)&len,sizeof(len));
		if(len>0)
		{
			bzero(buf,sizeof(buf));
			recvn(new_fd,buf,len);
		}
		j=strlen(buf);
		char *delim=" \n";
		char *temp;
		temp=strtok(buf,delim);//分割字符串
		printf("buf1=%s\n",temp);//打印结束符之前的字符
		strcpy(buf1,temp);//放入buf1中
		while((temp=strtok(NULL,delim)))
		{
			printf("buf2=%s\n",temp);
			strcpy(buf2,temp);
		}
		if(strcmp(buf1,"cd")==0&&(strlen(buf1)+strlen(buf2)+2)==j)
		{
			cd(buf2,new_fd);
			bzero(buf1,sizeof(buf1));
			bzero(buf2,sizeof(buf2));
		}else if(strcmp(buf1,"ls")==0){
			if((strlen(buf1)+1)==j)
			{
				ls(".",new_fd);
				bzero(buf1,sizeof(buf1));
				bzero(buf2,sizeof(buf2));
				printf("I am ls\n");
			}
			if(strlen(buf2)!=0&&(strlen(buf1)+strlen(buf2)+2)==j)
			{
				ls(buf2,new_fd);
			}
		}else if(strcmp(buf1,"gets")==0&&(strlen(buf1)+strlen(buf2)+2)==j){
			trans_file(new_fd,buf2);
			printf("after gets\n");
			bzero(buf2,sizeof(buf2));
			bzero(buf1,sizeof(buf1));
		}else if(strcmp(buf1,"puts")==0&&(strlen(buf1)+strlen(buf2)+2)==j){
			rec(buf1,buf2,new_fd);
			bzero(buf1,sizeof(buf1));
			bzero(buf2,sizeof(buf2));
		}else if(strcmp(buf1,"remove")==0&&(strlen(buf2))==0){
			rm(buf2,new_fd);
			bzero(buf1,sizeof(buf1));
			bzero(buf2,sizeof(buf2));
		}else if(strcmp(buf1,"pwd")==0&&(strlen(buf2))==0){
			pwd_s(".",new_fd);
			bzero(buf1,sizeof(buf1));
			bzero(buf2,sizeof(buf2));
		}else{
			bzero(buf1,sizeof(buf1));
			bzero(buf2,sizeof(buf2));
		}
					
	}
}
