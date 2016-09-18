#include "cpu/exec/template-start.h"

#define instr call 

static void do_execute(){
	uint32_t feip=cpu.eip;
	uint32_t op=instr_fetch(feip,1);
	while( op==0x66 )
	{
		feip++;
		op=instr_fetch(feip,1);
	}
	if( op==0xe8 ){
	DATA_TYPE_S off_set=op_src->val;
#if DATA_BYTE==2
	cpu.esp-=2;
	swaddr_write(cpu.esp,2,(cpu.eip+DATA_BYTE+2)&0xffff);
	cpu.eip=(cpu.eip+off_set)&0xffff;
#elif DATA_BYTE==4
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.eip+DATA_BYTE+1);
	cpu.eip+=off_set;
#endif
	}
	else if( op==0xff ){
#if DATA_BYTE==2
	cpu.esp=cpu.esp-2;
	//MEM_W(cpu.esp,(cpu.eip)&0XFFFF);
	cpu.eip=( op_src->val )&0xffff;
#elif DATA_BYTE==4
	cpu.esp-=4;
	//MEM_W(cpu.esp,cpu.eip+DATA_BYTE+1);
	cpu.eip=op_src->val;
#endif
	int len=concat(decode_rm_,SUFFIX)(feip+1);
	swaddr_write(cpu.esp,DATA_BYTE,feip+len+1);
	//Log("%x\n",feip+len+1);
	//do_int3();
	}
	else
		panic("please implement call.");
	print_asm_template1();
}

make_instr_helper(i)

#if DATA_BYTE==2||DATA_BYTE==4

make_instr_helper(cfrm)
#endif



#include "cpu/exec/template-end.h"