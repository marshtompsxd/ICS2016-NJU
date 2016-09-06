#include "cpu/exec/template-start.h"

#define instr movzx
static void do_execute(){
	if(DATA_BYTE==2)
		OPERAND_W(op_dest,((uint16_t)op_src->val<<8)>>8);
	else
		OPERAND_W(op_dest,((uint32_t)op_src->val<<24)>>24);
	print_asm_template2();
}

make_helper(concat(movzx_rm2r_,SUFFIX)){
	return idex(eip,decode_rm2r_b,concat(do_movzx_,SUFFIX));
}
#undef instr


#define instr movzxv
#if DATA_BYTE==4
static void do_execute(){
	OPERAND_W(op_dest,((uint32_t)op_src->val<<24)>>24);
	print_asm_template2();
}

make_helper(movzxv_rm2r_l){
	return idex(eip,decode_rm2r_w,do_movzxv_l);
}

#endif
#undef instr

#include "cpu/exec/template-end.h"