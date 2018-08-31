#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args");
		return -1;
	}
	struct stat buf;
	bzero(&buf,sizeof(buf));
	int ret=stat(argv[1],&buf);
	if(-1==ret)
	{
		perror("stat");
		return -1;
	}
	printf("%x,%s,%ld\n",buf.st_mode,getpwuid(buf.st_uid)->pw_name,buf.st_size);
}
