#include "cpu/exec/template-start.h"

#define instr call 

static void do_execute(){
	uint32_t opeip=cpu.eip;
	uint32_t op=instr_fetch(opeip,1);
	while(op==0x66){
		opeip++;
		op=instr_fetch(opeip,1);
	}
	if(op==0xe8){
		DATA_TYPE_S offs=op_src->val;
		cpu.esp-=DATA_BYTE;

#if DATA_BYTE==2
		
		swaddr_write(cpu.esp,2,(cpu.eip+DATA_BYTE+2)&0xffff);
		cpu.eip=(cpu.eip+offs)&0xffff;

#elif DATA_BYTE==4

		swaddr_write(cpu.esp,4,cpu.eip+DATA_BYTE+1);
		cpu.eip+=offs;
#endif
		}
		else if(op==0xff){
			cpu.esp-=DATA_BYTE;

#if DATA_BYTE==2
			cpu.eip=(op_src->val)&0xffff;

#elif DATA_BYTE==4
			cpu.eip=op_src->val;

#endif
			int len=concat(decode_rm_,SUFFIX)(opeip+1);
			swaddr_write(cpu.esp,DATA_BYTE,opeip+len+1);

		}
		else
			panic("call is not right");
	print_asm_template1();
}

make_instr_helper(i)

#if DATA_BYTE==2||DATA_BYTE==4

make_instr_helper(cfrm)
#endif



#include "cpu/exec/template-end.h"