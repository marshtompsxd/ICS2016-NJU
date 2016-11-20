#include "cpu/exec/template-start.h"

#define instr movrm2cr

static void do_execute(){
    if(op_dest->reg==0)cpu.cr0.val=op_src->val;
    else panic("please implment movrm2cr\n");

    print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
