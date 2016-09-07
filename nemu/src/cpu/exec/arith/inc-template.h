#include "cpu/exec/template-start.h"

#define instr inc

static void do_execute () {
	DATA_TYPE result = op_src->val + 1;
	OPERAND_W(op_src, result);

	/* TODO: Update EFLAGS. */
	//panic("please implement me");

	if(result==0)
		cpu.eflags.ZF=1;
	else 
		cpu.eflags.ZF=0;

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

	if(MSB(result)!=MSB(op_src->val)&&MSB(op_src->val)==0)
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
