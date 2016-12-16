#include "cpu/exec/template-start.h"


make_helper( concat(cwtltd_,SUFFIX) ) {

	if (DATA_BYTE==2){
		if(((DATA_TYPE_S)(cpu.ax))<0)
			cpu.dx=0xffff;
		else
			cpu.dx=0;
		print_asm("cwtl");
	}
	else if (DATA_BYTE==4){
		if(((DATA_TYPE_S)(cpu.eax))<0)
			cpu.edx=0xffffffff;
		else
			cpu.edx=0;
		print_asm("cltd");
	}

    return 1;
}

#include "cpu/exec/template-end.h"
