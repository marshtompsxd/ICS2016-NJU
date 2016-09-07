#include "cpu/exec/helper.h"


make_helper(lods_b){
	cpu.gpr[0]._8[0]=cpu.esi&0xff;
	if (cpu.eflags.DF == 0)	
		cpu.esi += 1;
	else 
		cpu.esi -= 1;
	print_asm("stosb");
	return 1;
}

make_helper(lods_w){
	cpu.gpr[0]._16=cpu.esi&0xffff;
	if(cpu.eflags.DF==0)
		cpu.esi+=2;
	else
		cpu.esi-=2;
	print_asm("stosw");
	return 1;
}

make_helper(lods_l){
	cpu.eax=cpu.esi;
	if(cpu.eflags.DF==0)
		cpu.esi+=4;
	else
		cpu.esi-=4;
	print_asm("stosl");
	return 1;
}

make_helper_v(lods)