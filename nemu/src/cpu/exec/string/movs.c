#include "cpu/exec/helper.h"

make_helper(movs_b){
	swaddr_write(cpu.edi,1,swaddr_read(cpu.esi,1));
	if(cpu.eflags.DF==0){
		cpu.esi+=1;
		cpu.edi+=1;
	}
	else{
		cpu.esi-=1;
		cpu.edi-=1;
	}

	print_asm("movsb");
	return 1;
}

make_helper(movs_w){
	swaddr_write(cpu.edi,2,swaddr_read(cpu.esi,2));
	if(cpu.eflags.DF==0){
		cpu.esi+=2;
		cpu.edi+=2;
	}
	else{
		cpu.esi-=2;
		cpu.edi-=2;
	}

	print_asm("movsw");
	return 1;
}

make_helper(movs_l){
	swaddr_write(cpu.edi,4,swaddr_read(cpu.esi,4));
	if(cpu.eflags.DF==0){
		cpu.esi+=4;
		cpu.edi+=4;
	}
	else{
		cpu.esi-=4;
		cpu.edi-=4;
	}

	print_asm("movsl");
	return 1;
}

make_helper_v(movs)