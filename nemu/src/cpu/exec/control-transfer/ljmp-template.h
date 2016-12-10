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
        cpu.eip=instr_fetch(eip+1,4);
        cpu.sreg[SR_CS].selector=instr_fetch(eip+5,2);

        updateSreg(SR_CS);

        //printf("sreg %d base is %x\n",SR_CS,cpu.sregdesc[SR_CS].base );
        //printf("sreg %d limit is %x\n",SR_CS,cpu.sregdesc[SR_CS].limit );

        print_asm("ljmp");
        return 0;
    }
}
#include "cpu/exec/template-end.h"
