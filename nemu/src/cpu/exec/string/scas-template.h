#include "cpu/exec/template-start.h"


make_helper( concat( scas_,SUFFIX ) ) {

	int incdec=0;
	DATA_TYPE src=cpu.eax;
	DATA_TYPE dest=swaddr_read( cpu.edi ,DATA_BYTE);
	DATA_TYPE result=src-dest;

	cpu.eflags.OF=MSB( (src^result)&(src^dest) );
	cpu.eflags.SF=MSB( result );
	cpu.eflags.ZF=!result;
	cpu.eflags.CF= ( dest>src );
	result^=result>>4;
	result^=result>>2;
	result^=result>>1;
	cpu.eflags.PF=!(result&1);

#if DATA_BYTE==1
	if( cpu.eflags.DF==0 )
		incdec=1;
	else
		incdec=-1;
#elif DATA_BYTE==2
	if( cpu.eflags.DF==0 )
		incdec=2;
	else
		incdec=-2;
#elif DATA_BYTE==4
	if( cpu.eflags.DF==0 )
		incdec=4;
	else
		incdec=-4;
#endif

	
	cpu.edi=cpu.edi+incdec;



	print_asm("scas");
	return 1;
}

#include "cpu/exec/template-end.h"
