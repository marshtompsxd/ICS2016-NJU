#include "cpu/exec/template-start.h"

#define instr movcr2rm

static void do_execute(){
    if(op_src->reg==0)OPERAND_W(op_dest,cpu.cr0.val);
    else panic("please implment movcr2rm\n");

    print_asm_template2();
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
