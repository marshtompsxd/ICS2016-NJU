#include "cpu/exec/template-start.h"
#include "../../../../../lib-common/x86-inc/mmu.h"

#define instr movrm2sreg


static void do_execute() {

    static union {
    	struct {
    		uint32_t _0:16;
    		uint32_t _1:8;
    		uint32_t _2:8;
    	};
    	uint32_t base;
    } descbase;

    static  union {
    	struct {
    		uint32_t _0:16;
    		uint32_t _1:4;
    	};
    	uint32_t limit;
    } desclimit;

    SegDesc desc;

	cpu.sreg[op_dest->reg].selector.SELECTOR=op_src->val;

	uint32_t index=cpu.sreg[op_dest->reg].selector.INDEX;
	desc.content[0]=lnaddr_read(cpu.gdtr.base+index*8,4);
	desc.content[1]=lnaddr_read(cpu.gdtr.base+index*8+4,4);

	descbase._0 = desc.base_15_0;
	descbase._1 = desc.base_23_16;
	descbase._2 = desc.base_31_24;

	desclimit._0 = desc.limit_15_0;
	desclimit._1 = desc.limit_19_16;

	if( desc.granularity==0 )
		cpu.sreg[op_dest->reg].hidden_descriptor.limit=desclimit.limit;
	else
		cpu.sreg[op_dest->reg].hidden_descriptor.limit=( (desclimit.limit+1)*(1<<12) )-1;
	cpu.sreg[op_dest->reg].hidden_descriptor.base=descbase.base;

	print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
