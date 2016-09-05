#include "cpu/exec/template-start.h"

#define instr call 

static void do_execute(){
	cpu.esp-=DATA_BYTE;
	if(DATA_BYTE==2){
		MEM_W(cpu.esp,(cpu.eip&0xffff)+DATA_BYTE+1);
		cpu.eip=(cpu.eip+op_src->val)&0xffff;
	}
	else{
		MEM_W(cpu.esp,cpu.eip+DATA_BYTE+1);
		cpu.eip+=op_src->val;
	}
	print_asm_template1();
}

make_instr_helper(i)




#include "cpu/exec/template-end.h"