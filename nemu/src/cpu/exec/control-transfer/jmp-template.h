#include "cpu/exec/template-start.h"

#define instr jmp

// static void do_execute() {
// 	if(op_src->type==OP_TYPE_IMM)
// 	{
// 		cpu.eip=cpu.eip+op_src->val;
// 		if(DATA_BYTE==2)
// 			cpu.eip=((cpu.eip+DATA_BYTE+1)&0xffff)-DATA_BYTE-1;
// 	}
// 	else if(op_src->type==OP_TYPE_MEM||op_src->type==OP_TYPE_REG)
// 	{ 
// 		if(DATA_BYTE==2)
// 			cpu.eip=(op_src->val&0x0000ffff)-2;
			
		
// 		else
// 			cpu.eip=op_src->val-2;
			

// 	}

// 	print_asm_template1();
// }


static void do_execute() {
		uint32_t feip=cpu.eip;
		uint32_t op=instr_fetch(cpu.eip,1);
		while( op==0x66 )
		{
			feip=feip+1;
			op=instr_fetch(feip,1);
		}
if( op==0xeb || op==0xe9 ){
		DATA_TYPE_S off_set=op_src->val;
		cpu.eip=cpu.eip+off_set;
#if DATA_BYTE==2
		cpu.eip=cpu.eip&0xffff;
#endif
}
else if( op==0xff ){
		DATA_TYPE dest=op_src->val;
#if DATA_BYTE==2
		cpu.eip=dest&0xffff;
#else
		cpu.eip=dest;
#endif
}
else
	panic("please implement jmp");

	print_asm_template1();
}

make_instr_helper(i)

#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(cfrm)
#endif

#if DATA_BYTE==1 || DATA_BYTE==4
make_instr_helper(si)
#endif


#include "cpu/exec/template-end.h"