#include "cpu/exec/template-start.h"


make_helper( concat(movs_,SUFFIX) ) {
	
#if DATA_BYTE==1
	DATA_TYPE data=swaddr_read(cpu.esi,DATA_BYTE);
	swaddr_write(cpu.edi,DATA_BYTE,data);
	if( cpu.eflags.DF==0 ){
		cpu.esi+=1;
		cpu.edi+=1;
	}
	else{
		cpu.esi-=1;
		cpu.edi-=1;
	}
#elif DATA_BYTE==2
	DATA_TYPE data=swaddr_read(cpu.esi,DATA_BYTE);
	swaddr_write(cpu.edi,DATA_BYTE,data);
	if( cpu.eflags.DF==0 ){
		cpu.esi+=2;
		cpu.edi+=2;
	}
	else{
		cpu.esi-=2;
		cpu.edi-=2;
	}
#elif DATA_BYTE==4
	DATA_TYPE data=swaddr_read(cpu.esi,DATA_BYTE);
	swaddr_write(cpu.edi,DATA_BYTE,data);
	if( cpu.eflags.DF==0 ){
		cpu.esi+=4;
		cpu.edi+=4;
	}
	else{
		cpu.esi-=4;
		cpu.edi-=4;
	}
#endif

	print_asm("movs");

	return 1;
}

#include "cpu/exec/template-end.h"
