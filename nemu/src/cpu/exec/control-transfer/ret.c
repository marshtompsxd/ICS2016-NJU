#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(ret){
	//printf("ret\n");
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	if(ops_decoded.is_operand_size_16){
			cpu.eip=((cpu.eip+1)&0xffff)-1;
			assert(0);
	}

	print_asm("ret");
	return 0;
}



make_helper(ret_i_w){
	//printf("ret\n");
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	if(ops_decoded.is_operand_size_16){
			cpu.eip=((cpu.eip+2+1)&0xffff)-3;
			assert(0);
	}
	cpu.esp+=op_src->val;

	print_asm("ret_i_w");
	return 0;
}