#include "cpu/exec/helper.h"


make_helper(scas_b){
	uint8_t minuend=cpu.eax&0xff;
	uint8_t subtrahend=cpu.edi&0xff;
	uint8_t result=minuend-subtrahend;
	if(minuend<subtrahend)
		cpu.eflags.CF=1;
	else 
		cpu.eflags.CF=0;
	
	if(result==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

	if(((minuend>>7)!=(result>>7))&&((subtrahend>>7)!=(minuend>>7)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;

	int i;
	int temp=result;
	int count=0;
	for(i=0;i<8;i++){
		if((temp&0x1)==0x1)count++;
		temp=temp>>1;
	}

	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;

	if((result>>7)==1)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;


	if (cpu.eflags.DF == 0)	
		cpu.edi += 1;
	else 
		cpu.edi -= 1;
	print_asm("scasb");
	return 1;
}

make_helper(scas_w){
	uint16_t minuend=cpu.eax&0xffff;
	uint16_t subtrahend=cpu.edi&0xffff;
	uint16_t result=minuend-subtrahend;
	if(minuend<subtrahend)
		cpu.eflags.CF=1;
	else 
		cpu.eflags.CF=0;
	
	if(result==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

	if(((minuend>>15)!=(result>>15))&&((subtrahend>>15)!=(minuend>>15)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;

	int i;
	int temp=result;
	int count=0;
	for(i=0;i<8;i++){
		if((temp&0x1)==0x1)count++;
		temp=temp>>1;
	}

	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;

	if((result>>15)==1)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;





	if(cpu.eflags.DF==0)
		cpu.edi+=2;
	else
		cpu.edi-=2;
	print_asm("scasw");
	return 1;
}

make_helper(scas_l){
	uint32_t minuend=cpu.eax;
	uint32_t subtrahend=cpu.edi;
	uint32_t result=minuend-subtrahend;
	if(minuend<subtrahend)
		cpu.eflags.CF=1;
	else 
		cpu.eflags.CF=0;
	
	if(result==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;

	if(((minuend>>31)!=(result>>31))&&((subtrahend>>31)!=(minuend>>31)))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;

	int i;
	int temp=result;
	int count=0;
	for(i=0;i<8;i++){
		if((temp&0x1)==0x1)count++;
		temp=temp>>1;
	}

	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;

	if((result>>31)==1)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;

	if(cpu.eflags.DF==0)
		cpu.edi+=4;
	else
		cpu.edi-=4;
	print_asm("scasl");
	return 1;
}

make_helper_v(scas)
