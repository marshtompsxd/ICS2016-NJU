#include "cpu/exec/template-start.h"

#define instr test

static void do_execute(){
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;

	DATA_TYPE result=(op_src->val)&(op_dest->val);

	int count=0;
	int temp=result;
	int i;
	for(i=0;i<8;i++){
		if(temp&0x1)count++;
		temp=temp>>1;
	}

	if(count%2==0)cpu.eflags.PF=1;
	else cpu.eflags.PF=0;

	if(result==0)cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;

	if(MSB(result)==1)cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
}


make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"