#include "cpu/exec/template-start.h"

#define instr lgdt

static void do_execute(){
    if(DATA_BYTE==2){
        panic("please implement lgdt\n");
    }
    else{
        //printf("op_src addr is 0x%x\n", op_src->addr);
        cpu.gdtr.limit=lnaddr_read(op_src->addr,2);
        cpu.gdtr.base=lnaddr_read(op_src->addr+2,4);
    }
    //printf("gdtr base is 0x%x\n",cpu.gdtr.base );
    //printf("gdtr limit is 0x%x\n",cpu.gdtr.limit );
    print_asm("lgdt");
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
