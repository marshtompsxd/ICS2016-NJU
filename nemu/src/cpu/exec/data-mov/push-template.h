#include "cpu/exec/template-start.h"

#define instr push

static void do_execute(){
	if(DATA_BYTE==2){
		cpu.esp-=2;
		swaddr_write(cpu.esp,2,op_src->val);
	}	
	else {
		cpu.esp-=4;
		swaddr_write(cpu.esp,4,(DATA_TYPE)op_src->val);
	}
	print_asm_template1();
}



make_instr_helper(i)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(r)
make_instr_helper(rm)
#endif


#include "cpu/exec/template-end.h"
