#include "cpu/exec/template-start.h"

#define instr add

static void do_execute() {
	DATA_TYPE addend1=op_src->val;
	DATA_TYPE addend2=op_dest->val;
	DATA_TYPE result=addend1+addend2;

	if(result=0)
		cpu.eflags.ZF=1;
	else 
		cpu.eflags.ZF=0;

	if(addend1>result||addend2>result)
		cpu.eflags.CF=1;
	else
		cpi.eflags.CF=0;

	int i;
	int temp=result;
	int count=0;
	for(i=0;i<8;i++){
		if((temp&0x1)==0x1)count++;
		temp=temp>>1;
	}

	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;

	if(MSB(result)==1)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;
	

	print_asm_template2();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
