#include "cpu/exec/template-start.h"


make_helper( concat(cwtltd_,SUFFIX) ) {

#if DATA_BYTE==2
	if(((DATA_TYPE_S)REG(R_AX))<0)
		REG(R_DX)=0xFFFF;
	else
		REG(R_DX)=0;
	print_asm("cwtl");
#elif DATA_BYTE==4
	if(((DATA_TYPE_S)REG(R_EAX))<0)
		REG(R_EDX)=0xFFFFFFFF;
	else
		REG(R_EDX)=0;
	print_asm("cltd");
#endif

    return 1;
}

#include "cpu/exec/template-end.h"
