#include "cpu/exec/template-start.h"

#define instr in

make_helper( concat(in_imm2a_,SUFFIX) ) {
	decode_i_b(eip+1);
	REG(R_EAX) = pio_read( op_src->val , DATA_BYTE);
	print_asm("in %%%s,%u",REG_NAME(R_EAX),op_src->val );
	return 2;
}
make_helper( concat(in_dx2a_,SUFFIX) ) {
	REG(R_EAX) = pio_read( cpu.edx & 0xffff , DATA_BYTE);
	print_asm("in");
	return 1;
}

#include "cpu/exec/template-end.h"
