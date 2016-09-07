#include "cpu/exec/helper.h"


make_helper(stos_b){
	swaddr_write(cpu.edi,1,cpu.eax);
	if (cpu.eflags.DF == 0)	
		cpu.edi += 1;
	else 
		cpu.edi -= 1;
	print_asm("stosb");
	return 1;
}

make_helper(stos_w){
	swaddr_write(cpu.edi,2,cpu.eax);
	if(cpu.eflags.DF==0)
		cpu.edi+=2;
	else
		cpu.edi-=2;
	print_asm("stosw");
	return 1;
}

make_helper(stos_l){
	swaddr_write(cpu.edi,4,cpu.eax);
	if(cpu.eflags.DF==0)
		cpu.edi+=4;
	else
		cpu.edi-=4;
	print_asm("stosl");
	return 1;
}

make_helper_v(stos)