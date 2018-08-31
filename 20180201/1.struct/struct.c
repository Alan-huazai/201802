#include <stdio.h>
#include <stdlib.h>
struct Time{
	int hour;
	int min;
	int sec;
};
struct Date{
	int year;
	int month;
	int day;
	struct Time time;
};
struct Student{
	char *name;
	int age;
	float score;
	struct Date birthday;
};
int main()
{
	struct Student stu1={"xiongda",19,99,{1995,1,1,{6,6,6}}};
	printf("姓名=%s,年龄=%d,年=%d，小时=%d\n",stu1.name,stu1.age,stu1.birthday.year,stu1.birthday.time.hour);

	return 0;
}
