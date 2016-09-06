#include "cpu/exec/template-start.h"

#define instr movsx
static void do_execute(){
	OPERAND_W(op_dest,(DATA_TYPE_S)op_src->val);
	print_asm_template2();
}

make_helper(concat(movsx_rm2r_,SUFFIX)){
	return idex(eip,decode_rm2r_b,concat(do_movsx_,SUFFIX));
}
#undef instr


#define instr movsxv
#if DATA_BYTE==4
static void do_execute(){
	OPERAND_W(op_dest,(DATA_TYPE_S)op_src->val);
	print_asm_template2();
}

make_helper(movsxv_rm2r_l){
	return idex(eip,decode_rm2r_w,do_movsxv_l);
}

#endif
#undef instr

#include "cpu/exec/template-end.h"