#include "cpu/exec/template-start.h"

#define instr and

static void do_execute () {
	DATA_TYPE result = op_dest->val & op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	//panic("please implement me");

	cpu.eflags.CF=0;
	cpu.eflags.OF=0;

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

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
