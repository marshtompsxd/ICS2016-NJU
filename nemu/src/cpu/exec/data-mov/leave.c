#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(leave){
	cpu.esp=cpu.ebp;
	if(ops_decoded.is_operand_size_16){
		cpu.ebp=(swaddr_read(cpu.esp,4)&0xffff)&(cpu.esp&0xffff0000);
		cpu.esp+=2;
	}
	else{
		cpu.ebp=swaddr_read(cpu.esp,4);
		cpu.esp+=4;
	}
	print_asm("leave");
	return 0;
}