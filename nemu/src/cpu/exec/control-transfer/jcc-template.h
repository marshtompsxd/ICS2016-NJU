#include "cpu/exec/template-start.h"


#define make_do_execute(condition) \
	static void do_execute(){\
		if(condition){\
			cpu.eip+=(DATA_TYPE_S)op_src->val;\
			if(DATA_BYTE==2)\
				cpu.eip=cpu.eip&0x0000ffff;\
		}\
		print_asm_template1();\
	}



#define instr je
make_do_execute(cpu.eflags.ZF==1)
#if  DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jb
make_do_execute(cpu.eflags.CF==1)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jbe
make_do_execute(cpu.eflags.CF==1||cpu.eflags.ZF==1)
#if  DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr ja
make_do_execute(cpu.eflags.CF==0&&cpu.eflags.ZF==0)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jae
make_do_execute(cpu.eflags.CF==0)
#if  DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jo
make_do_execute(cpu.eflags.OF==1)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jp
make_do_execute(cpu.eflags.PF==1)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr js
make_do_execute(cpu.eflags.SF==1)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jl
make_do_execute(cpu.eflags.SF!=cpu.eflags.OF)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jle
make_do_execute(cpu.eflags.SF!=cpu.eflags.OF||cpu.eflags.ZF==1)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jg
make_do_execute(cpu.eflags.SF==cpu.eflags.OF&&cpu.eflags.ZF==0)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jge
make_do_execute(cpu.eflags.SF==cpu.eflags.OF)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jne
make_do_execute(cpu.eflags.ZF==0)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jno
make_do_execute(cpu.eflags.OF==0)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jnp
make_do_execute(cpu.eflags.PF==0)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jns
make_do_execute(cpu.eflags.SF==0)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr

#define instr jcxz
make_do_execute(cpu.gpr[1]._16==0)
#if DATA_BYTE==1||DATA_BYTE==4
make_instr_helper(si)
#endif
make_instr_helper(i)
#undef instr


#include "cpu/exec/template-end.h"
