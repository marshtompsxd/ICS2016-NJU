#include<stdio.h>
#include "trap.h"
#include<string.h>
int main()
{
	char buf[20];
	int z=-1;
	sprintf(buf,"%d",z);
	//set_bp();
	nemu_assert(strcmp(buf,"-1")==0);
	return 0;
}
