#include "func.h"

void cd(char buf[128],int new_fd)
{
		printf("in cd =");
		puts(buf);
		chdir(buf);
		train t;
		char path[128]={0};
		strcpy(path,getcwd(NULL,0));
		t.len=strlen(path);
		strcpy(t.buf,path);
		printf("t.buf=%s\n",t.buf);
		sendn(new_fd,(char *)&t,4+t.len);
		t.len=0;
		sendn(new_fd,(char *)&t,4);
		return ;
}
void pwd_s(char buf1[128],int new_fd)
{
		char path[128]={0};
		train t;
		bzero(&t,sizeof(t));
		chdir(buf1);
		strcpy(path,getcwd(NULL,0));
		puts(path);
		t.len=strlen(path);
		strcpy(t.buf,path);
		sendn(new_fd,(char *)&t,4+t.len);
		t.len=0;
		sendn(new_fd,(char *)&t,4);
		return ;
}
