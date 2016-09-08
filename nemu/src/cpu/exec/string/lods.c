#include "cpu/exec/helper.h"


make_helper(lods_b){
	cpu.eax=swaddr_read(cpu.esi,1);
	if (cpu.eflags.DF == 0)	
		cpu.esi += 1;
	else 
		cpu.esi -= 1;
	print_asm("lodsb");
	return 1;
}

make_helper(lods_w){
	cpu.eax=swaddr_read(cpu.esi,2);
	if(cpu.eflags.DF==0)
		cpu.esi+=2;
	else
		cpu.esi-=2;
	print_asm("lodsw");
	return 1;
}

make_helper(lods_l){
	cpu.eax=swaddr_read(cpu.esi,4);
	if(cpu.eflags.DF==0)
		cpu.esi+=4;
	else
		cpu.esi-=4;
	print_asm("lodsl");
	return 1;
}

make_helper_v(lods)