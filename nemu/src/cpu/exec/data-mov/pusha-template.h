#include "cpu/exec/template-start.h"

#define instr pusha

make_helper( concat(pusha_,SUFFIX) ) {
    if (DATA_BYTE==2){
        panic("please implement pusha");
    }
    else{
        //printf("\n***execute pusha***\n");

        uint32_t temp=cpu.esp;

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, cpu.eax, SR_SS );

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, cpu.ecx, SR_SS );

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, cpu.edx, SR_SS );

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, cpu.ebx, SR_SS );

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, temp, SR_SS );

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, cpu.ebp, SR_SS );

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, cpu.esi, SR_SS );

        cpu.esp=cpu.esp-4;
    	swaddr_write( cpu.esp, 4, cpu.edi, SR_SS );
    }


	print_asm("pusha");

	return 1;
}

#include "cpu/exec/template-end.h"
