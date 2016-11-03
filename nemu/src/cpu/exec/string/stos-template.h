#include "cpu/exec/template-start.h"


make_helper( concat(stos_,SUFFIX) ) {

	if(DATA_BYTE==1){
		MEM_W( cpu.edi ,reg_b(R_AL));
		if( cpu.eflags.DF==0 )
			cpu.edi=cpu.edi+1;
		else
			cpu.edi=cpu.edi-1;
	}
	else if (DATA_BYTE==2){
		MEM_W( cpu.edi ,reg_w(R_AX));
		if( cpu.eflags.DF==0 )
			cpu.edi=cpu.edi+2;
		else
			cpu.edi=cpu.edi-2;
	}
	else if (DATA_BYTE==4){
		MEM_W( cpu.edi , reg_l(R_EAX));
		if( cpu.eflags.DF==0 )
			cpu.edi=cpu.edi+4;
		else
			cpu.edi=cpu.edi-4;
	}


	print_asm("stos");

	return 1;
}

#include "cpu/exec/template-end.h"
