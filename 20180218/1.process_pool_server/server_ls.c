#include "func.h"
void ls(char buf[128],int new_fd)
{
	char path[128]={0};
	chdir(buf);
	strcpy(path,getcwd(NULL,0));//将当前的工作路径复制到path中
	puts(path);
	DIR *dir;
	dir=opendir(path);//用于打开一个目录
	train t;
	if(NULL==dir)
	{
		perror("opendir");
		return;
	}
	struct dirent *p;
	while((p=readdir(dir))!=NULL)//迭代读取文件的内容，返回一个结构体指针
	{
		if(strcmp(p->d_name,"..")!=0&&strcmp(p->d_name,".")!=0)
		{
			printf("d_name=%s\n",p->d_name);
			t.len=strlen(p->d_name);
			strcpy(t.buf,p->d_name);//
			sendn(new_fd,(char*)&t,4+t.len);
		}
	}
	t.len=0;
	sendn(new_fd,(char*)&t,4);
	closedir(dir);
	return;
}
