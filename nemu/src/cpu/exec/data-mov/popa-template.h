#include "cpu/exec/template-start.h"

#define instr popa

make_helper( concat(popa_,SUFFIX) ){
    if(DATA_BYTE==2){
        panic("please implement popa");
    }
    else{
        cpu.edi=swaddr_read(cpu.esp,4,SR_SS);
        cpu.esp=cpu.esp+4;

        cpu.esi=swaddr_read(cpu.esp,4,SR_SS);
        cpu.esp=cpu.esp+4;

        cpu.ebp=swaddr_read(cpu.esp,4,SR_SS);
        cpu.esp=cpu.esp+4;

        /* throwaway ← Pop (); (* Skip ESP *) */
        cpu.esp=cpu.esp+4;

        cpu.ebx=swaddr_read(cpu.esp,4,SR_SS);
        cpu.esp=cpu.esp+4;

        cpu.edx=swaddr_read(cpu.esp,4,SR_SS);
        cpu.esp=cpu.esp+4;

        cpu.ecx=swaddr_read(cpu.esp,4,SR_SS);
        cpu.esp=cpu.esp+4;

        cpu.eax=swaddr_read(cpu.esp,4,SR_SS);
        cpu.esp=cpu.esp+4;

    }

	print_asm("popa");
	return 1;

}

#include "cpu/exec/template-end.h"
