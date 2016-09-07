#include "cpu/exec/template-start.h"

#define instr scas

static void do_execute(){

	if(cpu.eflags.DF==0)
	{
		cpu.esi+=DATA_BYTE;
		cpu.edi+=DATA_BYTE;
	}
	else
	{
		cpu.esi-=DATA_BYTE;
		cpu.edi-=DATA_BYTE;
	}

	if(cpu.esi<cpu.edi)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;

	if((MSB(cpu.esi)^MSB(cpu.esi-cpu.edi))&&(MSB(cpu.edi)^MSB(cpu.esi)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	
	cpu.eflags.SF=!!MSB(cpu.esi-cpu.edi);

	if((cpu.esi-cpu.edi)==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

	int count=0;
	if(((cpu.esi-cpu.edi)&0x1)==0x1)
		count++;
	if((((cpu.esi-cpu.edi)>>1)&0x1)==0x1)
		count++;
	if((((cpu.esi-cpu.edi)>>2)&0x1)==0x1)
		count++;
	if((((cpu.esi-cpu.edi)>>3)&0x1)==0x1)
		count++;
	if((((cpu.esi-cpu.edi)>>4)&0x1)==0x1)
		count++;
	if((((cpu.esi-cpu.edi)>>5)&0x1)==0x1)
		count++;
	if((((cpu.esi-cpu.edi)>>6)&0x1)==0x1)
		count++;
	if((((cpu.esi-cpu.edi)>>7)&0x1)==0x1)
		count++;

	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;

	print_asm_template2();

}

#include "cpu/exec/template-end.h"
