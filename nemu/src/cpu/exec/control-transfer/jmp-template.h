#include "cpu/exec/template-start.h"

#define instr jmp

// static void do_execute(){
// 	if(op_src->type==OP_TYPE_IMM){
// 		cpu.eip+=op_src->val;
// 		if(DATA_BYTE==2)
// 			cpu.eip=((cpu.eip+DATA_BYTE+1)&0xffff)-DATA_BYTE-1;
// 	}
// 	else if(op_src->type==OP_TYPE_REG||op_src->type==OP_TYPE_MEM){
// 		if(DATA_BYTE==2)
// 			cpu.eip=(op_src->val&0xffff)-DATA_BYTE-1;
// 		else
// 			cpu.eip=op_src->val-DATA_BYTE-1;
// 	}
// 	print_asm_template1();
// }
static void do_execute() {
	if(op_src->type==OP_TYPE_IMM)
	{
		cpu.eip=cpu.eip+op_src->val;
		if(DATA_BYTE==2)
			cpu.eip=cpu.eip&0x0000ffff;
	}
	else if(op_src->type==OP_TYPE_MEM||op_src->type==OP_TYPE_REG)
	{ 
		if(DATA_BYTE==2)
			cpu.eip=op_src->val&0x0000ffff;
		else
			cpu.eip=op_src->val-2;
//			cpu.eip=op_src->val;
	}

	print_asm_template1();
}

#if DATA_BYTE==1
make_instr_helper(si)
#endif

#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(i)
make_instr_helper(rm)
#endif


#include "cpu/exec/template-end.h"