#include "cpu/exec/template-start.h"



make_helper( concat(lods_,SUFFIX) ) {

	if (DATA_BYTE==1){
		REG(R_AL)=MEM_R(cpu.esi);
		if( cpu.eflags.DF==0 )
			cpu.esi=cpu.esi+1;
		else
			cpu.esi=cpu.esi-1;
	}
	else if (DATA_BYTE==2){
		REG(R_AX)=MEM_R(cpu.esi);
		if( cpu.eflags.DF==0 )
			cpu.esi=cpu.esi+2;
		else
			cpu.esi=cpu.esi-2;
	}
	else if (DATA_BYTE==4){
		REG(R_EAX)=MEM_R(cpu.esi);
		if( cpu.eflags.DF==0 )
			cpu.esi=cpu.esi+4;
		else
			cpu.esi=cpu.esi-4;
	}

	print_asm("lods");

	return 1;
}

#include "cpu/exec/template-end.h"
