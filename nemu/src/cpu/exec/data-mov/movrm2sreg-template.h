#include "cpu/exec/template-start.h"
#include "desc.h"
#define instr movrm2sreg

static void do_execute() {

    SegDesc desc;
    SegDescBase descbase;
    SegDescLimit desclimit;

	cpu.sreg[op_dest->reg].selector.SELECTOR=op_src->val;

	uint32_t index=cpu.sreg[op_dest->reg].selector.INDEX;
	desc.content[0]=lnaddr_read(cpu.gdtr.base+index*8,4);
	desc.content[1]=lnaddr_read(cpu.gdtr.base+index*8+4,4);

    Assert(desc.present==1,"the present of segment descriptor is 0\n");

    loadbase(&desc,&descbase);
    loadlimit(&desc,&desclimit);
    setsreg(desc, descbase, desclimit, op_dest->reg);

    printf("sreg %d base is %x\n",op_dest->reg,cpu.sreg[op_dest->reg].hidden_descriptor.base );
    printf("sreg %d limit is %x\n",op_dest->reg,cpu.sreg[op_dest->reg].hidden_descriptor.limit );
	print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
