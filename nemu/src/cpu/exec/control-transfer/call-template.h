#include "cpu/exec/template-start.h"

#define instr call

static void do_execute(){
	uint32_t opeip=cpu.eip;
	uint32_t op=instr_fetch(opeip,1);
	while( op==0x66 )
	{
		opeip++;
		op=instr_fetch(opeip,1);
	}
	if( op==0xe8 ){
		DATA_TYPE_S offs=op_src->val;
		if(DATA_BYTE==2){
			cpu.esp-=2;
			MEM_W(cpu.esp,(cpu.eip+DATA_BYTE+2)&0xffff);
			cpu.eip=(cpu.eip+offs)&0xffff;
		}
		else if(DATA_BYTE==4){
			cpu.esp-=4;
			MEM_W(cpu.esp,cpu.eip+DATA_BYTE+1);
			cpu.eip+=offs;
		}
	}
	else if( op==0xff ){
		if(DATA_BYTE==2){
			cpu.esp=cpu.esp-2;
			cpu.eip=( op_src->val )&0xffff;
		}
		else if(DATA_BYTE==4){
			cpu.esp-=4;
			cpu.eip=op_src->val;
		}

		int len=concat(decode_rm_,SUFFIX)(opeip+1);
		MEM_W(cpu.esp,opeip+len+1);
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
