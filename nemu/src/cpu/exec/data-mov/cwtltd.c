#include "cpu/exec/helper.h"

make_helper(cwtltd){
	if(((cpu.eax>>31)&0x1)==0x1)
		cpu.edx=0xffffffff;
	else
		cpu.edx=0;
	print_asm("cwtltd");
	return 1;
}