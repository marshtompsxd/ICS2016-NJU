#include "cpu/exec/template-start.h"


#define make_do_execute(condition) \
	static void do_execute(){\
		if(condition)\
			OPERAND_W(op_src,1);\
		else\
			OPERAND_W(op_src,0);\
		print_asm_template1();\
	}



#define instr sete
make_do_execute(cpu.eflags.ZF==1)
#if  DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setb
make_do_execute(cpu.eflags.CF==1)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setbe
make_do_execute(cpu.eflags.CF==1||cpu.eflags.ZF==1)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr seta
make_do_execute(cpu.eflags.CF==0&&cpu.eflags.ZF==0)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setae
make_do_execute(cpu.eflags.CF==0)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr


// #define instr setc
// make_do_execute(cpu.eflags.CF==1)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

#define instr seto
make_do_execute(cpu.eflags.OF==1)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setp
make_do_execute(cpu.eflags.PF==1)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr sets
make_do_execute(cpu.eflags.SF==1)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setl
make_do_execute(cpu.eflags.SF!=cpu.eflags.OF)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setle
make_do_execute(cpu.eflags.SF!=cpu.eflags.OF||cpu.eflags.ZF==1)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setg
make_do_execute(cpu.eflags.SF==cpu.eflags.OF&&cpu.eflags.ZF==0)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setge
make_do_execute(cpu.eflags.SF==cpu.eflags.OF)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setne
make_do_execute(cpu.eflags.ZF==0)
#if  DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

// #define instr setnb
// make_do_execute(cpu.eflags.CF==0)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

// #define instr setnbe
// make_do_execute(cpu.eflags.CF==0&&cpu.eflags.ZF==0)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

// #define instr setna
// make_do_execute(cpu.eflags.CF==1||cpu.eflags.ZF==1)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

// #define instr setnae
// make_do_execute(cpu.eflags.CF==1)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr


// #define instr setnc
// make_do_execute(cpu.eflags.CF==0)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

#define instr setno
make_do_execute(cpu.eflags.OF==0)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setnp
make_do_execute(cpu.eflags.PF==0)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

#define instr setns
make_do_execute(cpu.eflags.SF==0)
#if DATA_BYTE==1
make_instr_helper(rm)
#endif
#undef instr

// #define instr setnl
// make_do_execute(cpu.eflags.SF==cpu.eflags.OF)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

// #define instr setnle
// make_do_execute(cpu.eflags.SF!=cpu.eflags.OF&&cpu.eflags.ZF==1)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

// #define instr setng
// make_do_execute(cpu.eflags.SF!=cpu.eflags.OF||cpu.eflags.ZF==1)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr

// #define instr setnge
// make_do_execute(cpu.eflags.SF!=cpu.eflags.OF)
// #if DATA_BYTE==1
// make_instr_helper(rm)
// #endif
// #undef instr


#include "cpu/exec/template-end.h"