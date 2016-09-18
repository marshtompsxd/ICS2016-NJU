#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute () {
	OPERAND_W(op_dest,op_src->val);
	print_asm_template2();
}

make_instr_helper(rmsb2r)

#if DATA_BYTE==4
make_instr_helper(rmsw2r)
#endif

#include "cpu/exec/template-end.h"