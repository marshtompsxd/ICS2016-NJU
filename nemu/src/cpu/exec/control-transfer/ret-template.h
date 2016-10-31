#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute () {
	if (DATA_BYTE==2){
		cpu.eip=cpu.eip&0xffff0000;
		cpu.eip+=0xffff&MEM_R(cpu.esp);
		cpu.eip=cpu.eip&0xffff;
	}
	else if (DATA_BYTE==4){
		cpu.eip=MEM_R(cpu.esp);
	}
	cpu.esp+=DATA_BYTE;
	int offset=((int)op_src->val)<<16>>16;

	cpu.esp=cpu.esp+offset;

	print_asm_template1();
}


make_helper( concat(ret_,SUFFIX) ){
	if (DATA_BYTE==2){
		cpu.eip=cpu.eip&0xffff0000;
		cpu.eip+=0xffff&MEM_R(cpu.esp);
		cpu.eip=cpu.eip&0xffff;
	}
	else if(DATA_BYTE==4){
		cpu.eip=MEM_R(cpu.esp);
	}
	cpu.esp+=DATA_BYTE;
	print_asm("ret");
	return 0;
}


make_instr_helper(cfsi)



#include "cpu/exec/template-end.h"
