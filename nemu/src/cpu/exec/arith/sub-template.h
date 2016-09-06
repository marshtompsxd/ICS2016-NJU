#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute(){
	DATA_TYPE subtrahend=op_src->val;
	DATA_TYPE minuend=op_dest->val;
	DATA_TYPE result=minuend-subtrahend;
	OPERAND_W(op_dest,result);

	if(minuend<subtrahend)
		cpu.eflags.CF=1;
	else 
		cpu.eflags.CF=0;
	
	if(result==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

	if((MSB(subtrahend)==MSB(result))&&(MSB(subtrahend)!=MSB(minuend)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;

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

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(si2rm)
#endif

#include "cpu/exec/template-end.h"
