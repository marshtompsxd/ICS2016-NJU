#include "cpu/exec/template-start.h"

#define instr call

static void do_execute(){
	uint32_t opeip=cpu.eip;
	uint32_t op=instr_fetch(opeip,1);
	if( op==0x66 ){
		opeip++;
	}
	if( op_src->type==OP_TYPE_IMM ){
		DATA_TYPE_S offs=op_src->val;
		cpu.esp-=DATA_BYTE;
		if(DATA_BYTE==2){
			MEM_W(cpu.esp,(cpu.eip+DATA_BYTE+2)&0xffff,SR_SS);
			cpu.eip=(cpu.eip+offs)&0xffff;
		}
		else if(DATA_BYTE==4){
			MEM_W(cpu.esp,cpu.eip+DATA_BYTE+1,SR_SS);
			cpu.eip+=offs;
		}
	}
	else if( op_src->type==OP_TYPE_REG || op_src->type==OP_TYPE_MEM ){
		cpu.esp-=DATA_BYTE;
		if(DATA_BYTE==2){
			cpu.eip=( op_src->val )&0xffff;
		}
		else if(DATA_BYTE==4){
			cpu.eip=op_src->val;
		}

		int len=concat(decode_rm_,SUFFIX)(opeip+1);
		MEM_W(cpu.esp,opeip+len+1,SR_SS);
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
