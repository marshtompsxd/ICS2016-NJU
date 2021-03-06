#include "cpu/exec/template-start.h"

#define instr adc

static void do_execute() {
	DATA_TYPE addend1=op_src->val;
	DATA_TYPE addend2=op_dest->val;
	DATA_TYPE result=addend1+addend2+cpu.eflags.CF;

	if(result==0)
		cpu.eflags.ZF=1;
	else 
		cpu.eflags.ZF=0;

	if(MSB(result)!=MSB(addend2)&&MSB(addend1+cpu.eflags.CF)==MSB(addend2))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	
	if((addend1+cpu.eflags.CF)>result||(addend2+cpu.eflags.CF)>result)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;

	int i;
	DATA_TYPE temp=result;
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

	

	OPERAND_W(op_dest,result);
	

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

