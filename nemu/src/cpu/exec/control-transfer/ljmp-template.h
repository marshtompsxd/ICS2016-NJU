#include "cpu/exec/template-start.h"
#include "../../../../../lib-common/x86-inc/mmu.h"

#define instr ljmp

make_helper(concat(ljmp_,SUFFIX)){
    if(DATA_BYTE==2){
        panic("please implment ljmp");
    }
    else{

        union {
            struct {
                uint32_t _0:16;
                uint32_t _1:8;
                uint32_t _2:8;
            };
            uint32_t base;
        } descbase;

        union {
            struct {
                uint32_t _0:16;
                uint32_t _1:4;
            };
            uint32_t limit;
        } desclimit;



        uint32_t address[2];
        memset(address,0,sizeof(address));
        address[0]=instr_fetch(cpu.eip+1,4);
        address[1]=instr_fetch(cpu.eip+5,2);

        cpu.eip=address[0];
        cpu.sreg[SR_CS].selector.SELECTOR=address[1];

        uint32_t index=cpu.sreg[SR_CS].selector.INDEX;

        uint64_t descbuffer[2];
        memset(descbuffer,0,sizeof(descbuffer));
        descbuffer[0]=lnaddr_read(cpu.gdtr.base+index*8,4);
        descbuffer[1]=lnaddr_read(cpu.gdtr.base+index*8+4,4);

        SegDesc desc;
        desc.content[0]=descbuffer[0];
        desc.content[1]=descbuffer[1];

        descbase._0=desc.base_15_0;
        descbase._1=desc.base_23_16;
        descbase._2=desc.base_31_24;

        desclimit._0=desc.limit_15_0;
        desclimit._1=desc.limit_19_16;

        if(desc.granularity==0)cpu.sreg[SR_CS].hidden_descriptor.limit=desclimit.limit;
        else cpu.sreg[SR_CS].hidden_descriptor.limit=((desclimit.limit+1)*(1<<12))-1;
        cpu.sreg[SR_CS].hidden_descriptor.base=descbase.base;

        print_asm("ljmp");
        return 0;
    }
}
#include "cpu/exec/template-end.h"
