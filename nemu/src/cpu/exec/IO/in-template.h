#include "cpu/exec/template-start.h"

#define instr in

make_helper( concat(in_imm_,SUFFIX) ) {
	uint32_t len=decode_i_b(eip+1);
    if(DATA_BYTE==1){
        reg_b(R_EAX)=pio_read(op_src->val,DATA_BYTE);
    }
    else if(DATA_BYTE==2){
        reg_w(R_EAX)=pio_read(op_src->val,DATA_BYTE);
    }
    else if(DATA_BYTE==4){
        reg_l(R_EAX)=pio_read(op_src->val,DATA_BYTE);
    }
	print_asm("in");
	return 1+len;
}

make_helper( concat(in_dx_,SUFFIX) ) {
	REG(R_EAX) = pio_read( cpu.edx & 0xffff , DATA_BYTE);
	print_asm("in");
	return 1;
}

#include "cpu/exec/template-end.h"
