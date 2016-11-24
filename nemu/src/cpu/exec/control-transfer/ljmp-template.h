#include "cpu/exec/template-start.h"
#include "desc.h"
#define instr ljmp

/*
 * Direct far JMP. Direct JMP instructions that specify a target location
 * outside the current code segment contain a far pointer. This pointer
 * consists of a selector for the new code segment and an offset within the new
 * segment.
 */


make_helper(concat(ljmp_,SUFFIX)){
    if(DATA_BYTE==2){
        panic("please implment ljmp\n");
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

        Assert(desc.present==1,"the present of segment descriptor is 0\n");

        loadbase(&desc,&descbase);
        loadlimit(&desc,&desclimit);
        setsreg(desc, descbase, desclimit, SR_CS);

        printf("sreg %d base is %x\n",SR_CS,cpu.sreg[SR_CS].hidden_descriptor.base );
        printf("sreg %d limit is %x\n",SR_CS,cpu.sreg[SR_CS].hidden_descriptor.limit );

        print_asm("ljmp");
        return 0;
    }
}
#include "cpu/exec/template-end.h"
