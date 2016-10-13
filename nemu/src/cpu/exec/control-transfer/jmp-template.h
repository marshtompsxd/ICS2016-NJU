#include "cpu/exec/template-start.h"

#define instr jmp



static void do_execute() {
		uint32_t opeip=cpu.eip;
		uint32_t op=instr_fetch(cpu.eip,1);
		/*get the opcode after the prefix 66 to tell which jmp it is*/
		while( op==0x66 )
		{
			opeip=opeip+1;
			op=instr_fetch(opeip,1);
		}
		if( op==0xeb || op==0xe9 ){

			cpu.eip=cpu.eip+(DATA_TYPE_S)op_src->val;
			if(DATA_BYTE==2)
				cpu.eip=cpu.eip&0xffff;
		}
		else if( op==0xff ){

			if(DATA_BYTE==2)
				cpu.eip=(DATA_TYPE)(op_src->val)&0xffff;
			else
				cpu.eip=(DATA_TYPE)(op_src->val);
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
