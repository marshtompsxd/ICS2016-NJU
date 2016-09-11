#include "cpu/exec/template-start.h"

#define instr scas

static void do_execute(){

	if(DATA_BYTE==1){
		uint8_t minuend=cpu.gpr[0]._8[0];
		uint8_t subtrahend=cpu.gpr[7]._8[0];
		uint8_t result=minuend-subtrahend;
	}
	else if(DATA_BYTE==2){
		uint16_t minuend=cpu.gpr[0]._16;
		uint16_t subtrahend=cpu.gpr[7]._16;
		uint16_t result=minuend-subtrahend;
	}
	else if(DATA_BYTE==4){
		uint32_t minuend=cpu.eax;
		uint32_t subtrahend=cpu.edi;
		uint32_t result=minuend-subtrahend;
	}



	if(minuend<subtrahend)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;

	if((MSB(minuend)^MSB(result))&&(MSB(subtrahend)^MSB(minuend)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	
	cpu.eflags.SF=!!MSB(result);

	if((result)==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

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

	if(cpu.eflags.DF==0)
	{
		cpu.edi+=DATA_BYTE;
	}
	else
	{
		cpu.edi-=DATA_BYTE;
	}

	print_asm_template2();

}

#include "cpu/exec/template-end.h"