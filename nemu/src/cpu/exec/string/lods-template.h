#include "cpu/exec/template-start.h"



make_helper( concat(lods_,SUFFIX) ) {
	if (DATA_BYTE==1){
		reg_b(R_AL)=MEM_R(cpu.esi,SR_DS);
		if( cpu.eflags.DF==0 )
			cpu.esi=cpu.esi+1;
		else
			cpu.esi=cpu.esi-1;
	}
	else if (DATA_BYTE==2){
		reg_w(R_AX)=MEM_R(cpu.esi,SR_DS);
		if( cpu.eflags.DF==0 )
			cpu.esi=cpu.esi+2;
		else
			cpu.esi=cpu.esi-2;
	}
	else if (DATA_BYTE==4){
		reg_l(R_EAX)=MEM_R(cpu.esi,SR_DS);
		if( cpu.eflags.DF==0 )
			cpu.esi=cpu.esi+4;
		else
			cpu.esi=cpu.esi-4;
	}

	print_asm("lods");

	return 1;
}

#include "cpu/exec/template-end.h"
