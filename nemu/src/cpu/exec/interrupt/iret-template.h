#include "cpu/exec/template-start.h"
#include "desc.h"

#define instr iret
make_helper(concat(iret_,SUFFIX)) {
    if(DATA_BYTE==2){
        panic("please implement iret");
    }
    else{
        printf("\n***execute iret***\n");


        cpu.eip=swaddr_read( cpu.esp,4,SR_SS );
    	cpu.esp=cpu.esp+4;
        printf("pop eip %d\n",cpu.eip);


    	cpu.sreg[SR_CS].selector=swaddr_read( cpu.esp,4,SR_SS );
    	cpu.esp=cpu.esp+4;
        printf("pop cs selector %d\n",cpu.sreg[SR_CS].selector);
    	updateSreg(SR_CS);
        printf("sreg %d base is %x\n",SR_CS,cpu.sregdesc[SR_CS].base );
    	printf("sreg %d limit is %x\n",SR_CS,cpu.sregdesc[SR_CS].limit );


    	cpu.eflags.EFLAGS=swaddr_read( cpu.esp,4,SR_SS );
    	cpu.esp=cpu.esp+4;
        printf("pop eflags %d\n", cpu.eflags.EFLAGS);
    }
	print_asm("iret");
	return 0;
}

#include "cpu/exec/template-end.h"
