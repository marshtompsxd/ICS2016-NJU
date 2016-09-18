#include "cpu/exec/template-start.h"


make_helper( concat(stos_,SUFFIX) ) {

#if DATA_BYTE==1
	swaddr_write( cpu.edi ,DATA_BYTE, REG(R_AL));
	if( cpu.eflags.DF==0 )
		cpu.edi=cpu.edi+1;
	else
		cpu.edi=cpu.edi-1;
#elif DATA_BYTE==2
	swaddr_write( cpu.edi ,DATA_BYTE, REG(R_AX));
	if( cpu.eflags.DF==0 )
		cpu.edi=cpu.edi+2;
	else
		cpu.edi=cpu.edi-2;
#elif DATA_BYTE==4
	swaddr_write( cpu.edi ,DATA_BYTE, REG(R_EAX));
	if( cpu.eflags.DF==0 )
		cpu.edi=cpu.edi+4;
	else
		cpu.edi=cpu.edi-4;
#endif

	print_asm("stos");

	return 1;
}

#include "cpu/exec/template-end.h"
