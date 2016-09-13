#include "cpu/exec/helper.h"

make_helper(cwtltd){
	if(ops_decoded.is_operand_size_16){
		if(((cpu.eax>>15)&0x1)==0x1)
			cpu.edx=cpu.edx|0xffff;
		else
			cpu.edx=cpu.edx&0xffff0000;
	}
	else{
		if(((cpu.eax>>31)&0x1)==0x1)
			cpu.edx=0xffffffff;
		else
			cpu.edx=0;
		
	}
	print_asm("cwtltd");
	return 1;
}