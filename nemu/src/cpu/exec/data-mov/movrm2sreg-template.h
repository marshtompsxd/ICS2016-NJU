#include "cpu/exec/template-start.h"
#include "../../../../../lib-common/x86-inc/mmu.h"
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

    loadbase(&desc,&descbase);
    loadlimit(&desc,&desclimit);
    setsreg(desc, descbase, desclimit, op_dest->reg);
    printf("base is %d",descbase.base);
    panic("hahahah");

	print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
