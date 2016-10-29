#include "cpu/exec/template-start.h"

#define instr call

static void do_execute(){

	if( op_src->type==OP_TYPE_REG||op_src->type==OP_TYPE_MEM ){
		if(DATA_BYTE==2){
			cpu.esp-=2;
			int rmlen=concat(decode_rm_,SUFFIX)(cpu.eip+2);
			MEM_W(cpu.esp,cpu.eip+rmlen+2);
			cpu.eip=(op_src->val)&0xffff;
		}
		else if(DATA_BYTE==4){
			cpu.esp-=4;
			int rmlen=concat(decode_rm_,SUFFIX)(cpu.eip+1);
			MEM_W(cpu.esp,cpu.eip+rmlen+1);
			cpu.eip=op_src->val;
		}
	}
	else if( op_src->type==OP_TYPE_IMM ){
		if(DATA_BYTE==2){
			cpu.esp-=2;
			MEM_W(cpu.esp,(cpu.eip+DATA_BYTE+2)&0xffff);
			cpu.eip=(cpu.eip+(DATA_TYPE_S)op_src->val)&0xffff;
		}
		else if(DATA_BYTE==4){
			cpu.esp-=4;
			MEM_W(cpu.esp,cpu.eip+DATA_BYTE+1);
			cpu.eip=cpu.eip+(DATA_TYPE_S)op_src->val;
		}
	}
	else
		panic("please implement call.");
	print_asm_template1();
}

make_instr_helper(i)

#if DATA_BYTE==2||DATA_BYTE==4

make_instr_helper(cfrm)
#endif



#include "cpu/exec/template-end.h"
