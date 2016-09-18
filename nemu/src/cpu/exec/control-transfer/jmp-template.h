#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	uint32_t opeip=cpu.eip;
	uint32_t op=instr_fetch(opeip,1);
	while(op==0x66){
		opeip++;
		op=instr_fetch(opeip,1);
	}
	print_asm_template1();
	if(op==0xeb||op==0xe9){
		
		
#if DATA_BYTE==2
		DATA_TYPE_S offs=op_src->val;
		cpu.eip=(cpu.eip+offs)&0xffff;

#elif DATA_BYTE==4
		DATA_TYPE_S offs=op_src->val;
		cpu.eip+=offs;

#endif
	}
	else if(op==0xff){
#if DATA_BYTE==2
			cpu.eip=(op_src->val)&0xffff;

#elif DATA_BYTE==4
			cpu.eip=op_src->val;

#endif
	}
}


make_instr_helper(i)

#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(cfrm)
#endif

#if DATA_BYTE==1 || DATA_BYTE==4
make_instr_helper(si)
#endif



#include "cpu/exec/template-end.h"