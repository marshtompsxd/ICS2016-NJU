#include "cpu/exec/template-start.h"

#define instr lgdt

static void do_execute(){
    if(DATA_BYTE==2){
        panic("please implement lgdt\n");
    }
    else{
        cpu.gdtr.limit=swaddr_read(op_src->addr,2,SR_DS);
        cpu.gdtr.base=swaddr_read(op_src->addr+2,4,SR_DS);
    }

    print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
