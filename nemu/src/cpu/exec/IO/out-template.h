#include "cpu/exec/template-start.h"

#define instr out

make_helper( concat(out_imm_,SUFFIX) ) {
	decode_i_b(eip+1);
	pio_write( op_src->val, DATA_BYTE, REG(R_EAX) );
    print_asm("out 	%u,%%%s",op_src->val,REG_NAME(R_EAX) );
	return 2;
}

make_helper( concat(out_dx_,SUFFIX) ) {
	pio_write( cpu.edx & 0xffff, DATA_BYTE, REG(R_EAX) );
	print_asm("out");
	return 1;
}

#include "cpu/exec/template-end.h"
