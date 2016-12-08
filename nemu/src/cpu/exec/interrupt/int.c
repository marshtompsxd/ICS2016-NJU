#include "cpu/exec/helper.h"
#include "raise_intr.h"

make_helper(int_b) {
	int len=decode_i_b(eip+1);
	cpu.eip=cpu.eip+len+1;
	print_asm("int 0x%x",op_src->val);
	printf("raise interrupt with ID %d\n",op_src->val );
	raise_intr( op_src->val );
	panic("shouldn't get here");
	return 0;
}
