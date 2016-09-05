#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute(){
	
	cpu.esp=cpu.ebp;
	if(DATA_BYTE==2){
		reg_w(R_BP)=MEM_R(cpu.esp);
		cpu.esp+=2;
	}
	else{
		cpu.ebp=MEM_R(cpu.esp);
		cpu.esp+=4;
	}
	
	print_asm_template1();
}

make_instr_helper(r)




#include "cpu/exec/template-end.h"