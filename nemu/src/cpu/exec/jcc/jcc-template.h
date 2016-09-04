#include "cpu/exec/template-start.h"


#define make_do_execute(condition) \
	static void do_execute(){\
		if(condition){\
			cpu.eip+=(DATA_TYPE_S)op_src->val;\
			if(DATA_BYTE==2)\
				cpu.eip=cpu.eip&0xffff;\
		}\
		print_asm_template1();\
	}



#define instr je
make_do_execute(cpu.eflags.ZF==1)
#if  DATA_BYTE==1
make_instr_helper(si)
#elif DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(i)
#endif
#undef instr




#include "cpu/exec/template-end.h"