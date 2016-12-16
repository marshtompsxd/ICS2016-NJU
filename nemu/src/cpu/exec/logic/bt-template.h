#include "cpu/exec/template-start.h"

#define instr bt

static void do_execute () {
	if(op_dest->type == OP_TYPE_REG){
		cpu.eflags.CF = ( op_dest->val >> op_src->val )&1;
		print_asm_template2();
	}
	else{
		panic("please implement bt");
	}
}

make_instr_helper(r2rm)
make_instr_helper(si2rm)

#include "cpu/exec/template-end.h"
