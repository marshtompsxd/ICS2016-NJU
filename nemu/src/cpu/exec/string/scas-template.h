#include "cpu/exec/template-start.h"

#define instr scas

static void do_execute(){

	if(cpu.eax<cpu.edi)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;

	if((MSB(cpu.eax)^MSB(cpu.eax-cpu.edi))&&(MSB(cpu.edi)^MSB(cpu.eax)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	
	cpu.eflags.SF=!!MSB(cpu.eax-cpu.edi);

	if((cpu.eax-cpu.edi)==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

	int i;
	DATA_TYPE temp=cpu.eax-cpu.edi;
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