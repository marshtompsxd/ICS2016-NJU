#include "cpu/exec/template-start.h"

#define instr movcr

make_helper(concat(movcr_r2rm_,SUFFIX)){
    int len=decode_r2rm_l(eip+1);

    if(op_src->reg==0)OPERAND_W(op_dest,cpu.cr0.val);
    else panic("please implment movcr2rm\n");

    printf("mov cr%x value is %x to op_dest\n",op_src->reg,op_src->val);

    print_asm("movcr2rm");

    return 1+len;
}

make_helper(concat(movcr_rm2r_,SUFFIX)){
    int len=decode_rm2r_l(eip+1);

    if(op_dest->reg==0)cpu.cr0.val=op_src->val;
    else if(op_dest->reg==3)cpu.cr3.val=op_src->val;
    else panic("please implment movrm2cr\n");

    printf("mov 0x%x to cr%x\n",op_src->val,op_dest->reg);

    print_asm("movrm2cr");

    return 1+len;
}


#include "cpu/exec/template-end.h"
