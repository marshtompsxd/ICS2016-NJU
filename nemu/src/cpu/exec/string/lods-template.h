#include "cpu/exec/template-start.h"



make_helper( concat(lods_,SUFFIX) ) {

#if DATA_BYTE==1
	REG(R_AL)=swaddr_read(cpu.esi,DATA_BYTE);
	if( cpu.eflags.DF==0 )
		cpu.esi=cpu.esi+1;
	else
		cpu.esi=cpu.esi-1;
#elif DATA_BYTE==2
	REG(R_AX)=swaddr_read(cpu.esi,DATA_BYTE);
	if( cpu.eflags.DF==0 )
		cpu.esi=cpu.esi+2;
	else
		cpu.esi=cpu.esi-2;
#elif DATA_BYTE==4
	REG(R_EAX)=swaddr_read(cpu.esi,DATA_BYTE);
	if( cpu.eflags.DF==0 )
		cpu.esi=cpu.esi+4;
	else
		cpu.esi=cpu.esi-4;
#endif

	print_asm("lods");

	return 1;
}

#include "cpu/exec/template-end.h"
