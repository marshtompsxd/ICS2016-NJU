#include "cpu/exec/template-start.h"


make_helper( concat( scas_,SUFFIX ) ) {


	DATA_TYPE minuend=cpu.eax;
	DATA_TYPE subtrahend=swaddr_read( cpu.edi ,DATA_BYTE);
	DATA_TYPE result=minuend-subtrahend;

	if(minuend<subtrahend)
		cpu.eflags.CF=1;
	else 
		cpu.eflags.CF=0;
	
	if(result==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

	if((MSB(minuend)!=MSB(result))&&(MSB(subtrahend)!=MSB(minuend)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;

	int i;
	DATA_TYPE temp=result;
	int count=0;
	for(i=0;i<8;i++){
		if((temp&0x1)==0x1)count++;
		temp=temp>>1;
	}

	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;

	if(MSB(result)==1)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;

#if DATA_BYTE==1
	if( cpu.eflags.DF==0 )
		cpu.edi+=1;
	else
		cpu.edi-=1;
#elif DATA_BYTE==2
	if( cpu.eflags.DF==0 )
		cpu.edi+=2;
	else
		cpu.edi-=2;
#elif DATA_BYTE==4
	if( cpu.eflags.DF==0 )
		cpu.edi+=4;
	else
		cpu.edi-=4;
#endif


	print_asm("scas");
	return 1;
}

#include "cpu/exec/template-end.h"
