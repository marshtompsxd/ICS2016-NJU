#include "cpu/exec/template-start.h"

#define instr lidt

static void do_execute(){
    if(DATA_BYTE==2){
        panic("please implement lidt\n");
    }
    else{
        printf("op_src addr is 0x%x\n", op_src->addr);
        cpu.idtr.limit=lnaddr_read(op_src->addr,2);
        cpu.idtr.base=lnaddr_read(op_src->addr+2,4);
    }
    printf("idtr base is 0x%x\n",cpu.idtr.base );
    printf("idtr limit is 0x%x\n",cpu.idtr.limit );
    print_asm("lidt");
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
