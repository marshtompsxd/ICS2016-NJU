#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute () {
	OPERAND_W(op_dest,op_src->val);
	print_asm_template2();
}

make_instr_helper(rmzb2r)

#if DATA_BYTE==4
make_instr_helper(rmzw2r)
#endif

#include "cpu/exec/template-end.h"