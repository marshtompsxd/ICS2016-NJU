#include "cpu/exec/template-start.h"
#include "../../../../../lib-common/x86-inc/mmu.h"

#define instr ljmp

make_helper(concat(ljmp_,SUFFIX)){
    if(DATA_BYTE==2){
        panic("please implment ljmp");
    }
    else{
        SegDesc desc;
        SegDescBase descbase;
        SegDescLimit desclimit;

        cpu.sreg[SR_CS].selector.SELECTOR=instr_fetch(eip+5,2);
        cpu.eip=instr_fetch(eip+1,4);


        uint32_t index=cpu.sreg[SR_CS].selector.INDEX;
        desc.content[0]=lnaddr_read(cpu.gdtr.base+index*8,4);
        desc.content[1]=lnaddr_read(cpu.gdtr.base+index*8+4,4);

        descbase._15_0=desc.base_15_0;
        descbase._23_16=desc.base_23_16;
        descbase._31_24=desc.base_31_24;

        desclimit._15_0=desc.limit_15_0;
        desclimit._19_16=desc.limit_19_16;

        if(desc.granularity==0)
            cpu.sreg[SR_CS].hidden_descriptor.limit=desclimit.limit;
        else
            cpu.sreg[SR_CS].hidden_descriptor.limit=((desclimit.limit+1)*(1<<12))-1;
        cpu.sreg[SR_CS].hidden_descriptor.base=descbase.base;

        print_asm("ljmp");
        return 0;
    }
}
#include "cpu/exec/template-end.h"
