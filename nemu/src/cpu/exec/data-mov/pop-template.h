#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute(){

	OPERAND_W(op_src,MEM_R(cpu.esp));
	if(DATA_BYTE==2)cpu.esp+=2;
	else cpu.esp+=4;

	print_asm_template1();
}


make_instr_helper(r)
make_instr_helper(rm)



#include "cpu/exec/template-end.h"
