#include "cpu/exec/template-start.h"
#include "desc.h"
#define instr movsreg

make_helper(concat(movsreg_rm2r_,SUFFIX)){

    int len=decode_rm2r_w(eip+1);

    cpu.sreg[op_dest->reg].selector=op_src->val;

/*
    SegDesc desc;
    SegDescBase descbase;
    SegDescLimit desclimit;



	uint32_t index=cpu.sreg[op_dest->reg].INDEX;
	desc.content[0]=lnaddr_read(cpu.gdtr.base+index*8,4);
	desc.content[1]=lnaddr_read(cpu.gdtr.base+index*8+4,4);

    Assert(desc.present==1,"the present of segment descriptor is 0\n");

    loadSegDescBase(&desc,&descbase);
    loadSegDescLimit(&desc,&desclimit);
    setsreg(desc, descbase, desclimit, op_dest->reg);
*/

    updateSreg(op_dest->reg);

    printf("sreg no is %d\n",op_dest->reg );
    printf("sreg %d base is 0x%x\n",op_dest->reg,cpu.sregdesc[op_dest->reg].base );
    printf("sreg %d limit is 0x%x\n",op_dest->reg,cpu.sregdesc[op_dest->reg].limit );
	print_asm("movsreg");

    return len+1;
}


#include "cpu/exec/template-end.h"
