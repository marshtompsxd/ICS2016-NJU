#include "cpu/exec/template-start.h"

#define instr call 

static void do_execute(){
	if(op_src->type==OP_TYPE_IMM){
		if(DATA_BYTE==2){
			cpu.esp-=DATA_BYTE;
			swaddr_write(cpu.esp,DATA_BYTE,(cpu.eip+DATA_BYTE+1)&0x0000ffff);	
			cpu.eip=((cpu.eip+DATA_BYTE+1+op_src->val)&0x0000ffff)-DATA_BYTE-1;
		}
		else{

			cpu.esp-=DATA_BYTE;
			swaddr_write(cpu.esp,DATA_BYTE,cpu.eip+DATA_BYTE+1);
			//printf("now is %x\n", cpu.eip);
			//printf("store%x\n",cpu.eip+DATA_BYTE+1 );
			cpu.eip+=op_src->val;
			//printf("call %x\n", cpu.eip);

		}
		//printf("call \n");

	}
else if(op_src->type==OP_TYPE_REG||op_src->type==OP_TYPE_MEM){
	if(DATA_BYTE==2){
		cpu.esp-=DATA_BYTE;

		swaddr_write(cpu.esp,DATA_BYTE,(cpu.eip+2)&0x0000ffff);

		cpu.eip=((op_src->val)&0x0000ffff)-2;
 	}
	else{ 
		cpu.esp-=DATA_BYTE;
		swaddr_write(cpu.esp,DATA_BYTE,cpu.eip+2);
		cpu.eip=op_src->val-DATA_BYTE-2;
 	}
}
	print_asm_template1();
}

make_instr_helper(i)
make_instr_helper(rm)




#include "cpu/exec/template-end.h"