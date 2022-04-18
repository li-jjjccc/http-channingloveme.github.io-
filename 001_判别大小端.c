#include <stdio.h>
int test()
{	// 判断电脑存储数据是大小端的判别方法
	int i=1;
	int temp;
	temp=*(char*)(&i);
	if(1==temp)
	{
		printf("小端");
		return 1;
	}
	else
	{
		printf("大端");
		return 0;
	}
}
int main()
{
  test();
   return 0;
}