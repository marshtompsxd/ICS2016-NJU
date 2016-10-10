#include "cpu/exec/template-start.h"

#define instr leave

make_helper(concat(leave_,SUFFIX)){

	cpu.esp=cpu.ebp;
	if(DATA_BYTE==2)
		reg_w(R_BP)=MEM_R(cpu.esp);

	else if(DATA_BYTE==4)
		cpu.ebp=MEM_R(cpu.esp);


	cpu.esp+=DATA_BYTE;

	print_asm("leave");

	return 1;
}

#include "cpu/exec/template-end.h"
