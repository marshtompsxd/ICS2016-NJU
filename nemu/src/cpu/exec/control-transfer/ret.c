#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(ret){
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	if(ops_decoded.is_operand_size_16){
			cpu.eip=cpu.eip&0xffff;
			printf("the operand size is 16 in ret\n");
	}

	print_asm("ret");
	return 0;
}



make_helper(ret_i_w){
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	if(ops_decoded.is_operand_size_16){
			cpu.eip=((cpu.eip+2+1)&0xffff)-3;
			printf("the operand size is 16 in retiw\n");
	}
	cpu.esp+=op_src->val;

	print_asm("ret_i_w");
	return 0;
}