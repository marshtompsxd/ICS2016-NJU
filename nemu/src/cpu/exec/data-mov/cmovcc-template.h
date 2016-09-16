#include "cpu/exec/template-start.h"

#define make_do_execute(condition) \
	static void do_execute(){\
		if(condition)\
		{\
			OPERAND_W(op_dest,op_src->val);\
		}\
		print_asm_template2();\
	}

#define instr cmova
make_do_execute(cpu.eflags.CF==0&&cpu.eflags.ZF==0)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovae
make_do_execute(cpu.eflags.CF==0)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)        
#endif
#undef instr

#define instr cmovb
make_do_execute(cpu.eflags.CF==1)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovbe
make_do_execute(cpu.eflags.CF==1||cpu.eflags.ZF==1)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmove
make_do_execute(cpu.eflags.ZF==1)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovg
make_do_execute(cpu.eflags.ZF==0||cpu.eflags.SF==cpu.eflags.OF)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovge
make_do_execute(cpu.eflags.SF==cpu.eflags.OF)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovl
make_do_execute(cpu.eflags.SF!=cpu.eflags.OF)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovle
make_do_execute(cpu.eflags.ZF==1||cpu.eflags.SF!=cpu.eflags.OF)
#if DATA_BYTE==2||DATA_BYTE==4
 make_instr_helper(rm2r)
#endif
#undef instr


#define instr cmovne
make_do_execute(cpu.eflags.ZF==0)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif 
#undef instr

#define instr cmovno
make_do_execute(cpu.eflags.OF==0)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovnp
make_do_execute(cpu.eflags.PF==0)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovns
make_do_execute(cpu.eflags.SF==0)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovo
make_do_execute(cpu.eflags.OF==1)
#if DATA_BYTE==2||DATA_BYTE==4 
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovp
make_do_execute(cpu.eflags.PF==1)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif
#undef instr

#define instr cmovs
make_do_execute(cpu.eflags.SF==1)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(rm2r)
#endif 
#undef instr

#include "cpu/exec/template-end.h"
