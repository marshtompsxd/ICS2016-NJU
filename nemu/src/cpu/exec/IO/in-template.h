#include "cpu/exec/template-start.h"

#define instr in

make_helper( concat(in_imm2a_,SUFFIX) ) {
	uint32_t len=decode_i_b(eip+1);
	if(len!=1){
		Log("the imm of in is not imm8!!!");
	}
	REG(R_EAX) = pio_read( op_src->val , DATA_BYTE);
	print_asm("in %%%s,%u",REG_NAME(R_EAX),op_src->val );
	return 1+len;
}

make_helper( concat(in_dx2a_,SUFFIX) ) {
	REG(R_EAX) = pio_read( cpu.edx & 0xffff , DATA_BYTE);
	print_asm("in");
	return 1;
}

#include "cpu/exec/template-end.h"
