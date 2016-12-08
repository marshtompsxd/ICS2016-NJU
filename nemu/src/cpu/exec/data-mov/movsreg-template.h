#include "cpu/exec/template-start.h"
#include "desc.h"
#define instr movsreg

make_helper(concat(movsreg_rm2r_,SUFFIX)){

    int len=decode_rm2r_w(eip+1);

    cpu.sreg[op_dest->reg].selector=op_src->val;

    updateSreg(op_dest->reg);

    printf("sreg no is %d\n",op_dest->reg );
    printf("sreg %d base is 0x%x\n",op_dest->reg,cpu.sregdesc[op_dest->reg].base );
    printf("sreg %d limit is 0x%x\n",op_dest->reg,cpu.sregdesc[op_dest->reg].limit );
	print_asm("movsreg");

    return len+1;
}


#include "cpu/exec/template-end.h"
