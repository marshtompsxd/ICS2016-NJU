#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute () {
#if DATA_BYTE==2
	cpu.eip=cpu.eip&0xffff0000;
	cpu.eip+=0xffff&swaddr_read(cpu.esp,2);
	cpu.esp+=2;
	cpu.eip=cpu.eip&0xffff;
#elif DATA_BYTE==4
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
#endif

	op_src->val=( (int)op_src->val )<<16>>16;
	cpu.esp=cpu.esp+op_src->val;

	print_asm_template1();
}


make_instr_helper(cfsi)


make_helper( concat(ret_,SUFFIX) ){
#if DATA_BYTE==2
		cpu.eip=cpu.eip&0xffff0000;
		cpu.eip+=0xffff&MEM_R(cpu.esp);
		cpu.esp+=2;
		cpu.eip=cpu.eip&0xffff;
#elif DATA_BYTE==4
		cpu.eip=MEM_R(cpu.esp);
		cpu.esp+=4;
#endif	
		print_asm("ret");
		return 0;
}


#include "cpu/exec/template-end.h"
