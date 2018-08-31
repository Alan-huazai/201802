#include "stdio.h"
#include "string.h"
int main()
{
	char buf[128]="Hello";
	printf("buf的长度=%ld\n",strlen(buf));
	puts(buf);
	char *delim="\n";
	char *temp;
	temp=strtok(buf,delim);
	puts(temp);
	return 0;
}
