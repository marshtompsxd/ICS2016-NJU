#include "cpu/exec/template-start.h"

#define instr jmp



static void do_execute() {


		if( op_src->type==OP_TYPE_REG||op_src->type==OP_TYPE_MEM ){

			if(DATA_BYTE==2)
				cpu.eip=(DATA_TYPE)(op_src->val)&0xffff;
			else
				cpu.eip=(DATA_TYPE)(op_src->val);
		}
		if( op_src->type==OP_TYPE_IMM ){

			if(DATA_BYTE==2){
				cpu.eip=cpu.eip+(DATA_TYPE_S)op_src->val;
				cpu.eip=cpu.eip&0xffff;
			}
			else{
				cpu.eip=cpu.eip+(DATA_TYPE_S)op_src->val;
			}
		}
		else
			panic("please implement jmp");

		print_asm_template1();
}

make_instr_helper(i)

#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(cfrm)
#endif

#if DATA_BYTE==1 || DATA_BYTE==4
make_instr_helper(si)
#endif


#include "cpu/exec/template-end.h"
