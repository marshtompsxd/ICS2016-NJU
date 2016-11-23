#include "cpu/exec/template-start.h"
#include "../../../../../lib-common/x86-inc/mmu.h"

#define instr ljmp

/*
 * Direct far JMP. Direct JMP instructions that specify a target location
 * outside the current code segment contain a far pointer. This pointer
 * consists of a selector for the new code segment and an offset within the new
 * segment.
 */


SegDesc desc;
SegDescBase descbase;
SegDescLimit desclimit;

void loadbase(){
    descbase._15_0=desc.base_15_0;
    descbase._23_16=desc.base_23_16;
    descbase._31_24=desc.base_31_24;
}

void loadlimit(){
    desclimit._15_0=desc.limit_15_0;
    desclimit._19_16=desc.limit_19_16;
}

void setsreg(int index){
    if(desc.granularity==0)
        cpu.sreg[index].hidden_descriptor.limit=desclimit.limit;
    else
        cpu.sreg[index].hidden_descriptor.limit=desclimit.limit<<12;

    cpu.sreg[index].hidden_descriptor.base=descbase.base;
}

make_helper(concat(ljmp_,SUFFIX)){
    if(DATA_BYTE==2){
        panic("please implment ljmp");
    }
    else{
        cpu.sreg[SR_CS].selector.SELECTOR=instr_fetch(eip+5,2);
        cpu.eip=instr_fetch(eip+1,4);

        uint32_t index=cpu.sreg[SR_CS].selector.INDEX;
        desc.content[0]=lnaddr_read(cpu.gdtr.base+index*8,4);
        desc.content[1]=lnaddr_read(cpu.gdtr.base+index*8+4,4);

        loadbase();
        loadlimit();
        setsreg(SR_CS);

        print_asm("ljmp");
        return 0;
    }
}
#include "cpu/exec/template-end.h"
