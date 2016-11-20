#include "cpu/exec/template-start.h"

#include "cpu/decode/modrm.h"

/* I write some new decode functions to deal with some special instructions . */


#define decode_r_internal concat3(decode_r_, SUFFIX, _internal)
#define decode_rm_internal concat3(decode_rm_, SUFFIX, _internal)
#define decode_i concat(decode_i_, SUFFIX)
#define decode_a concat(decode_a_, SUFFIX)
#define decode_r2rm concat(decode_r2rm_, SUFFIX)

/* Ib, Iv */
make_helper(concat(decode_i_, SUFFIX)) {
	/* eip here is pointing to the immediate */
	op_src->type = OP_TYPE_IMM;
	op_src->imm = instr_fetch(eip, DATA_BYTE);
	op_src->val = op_src->imm;

#ifdef DEBUG
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", op_src->imm);
#endif
	return DATA_BYTE;
}

#if DATA_BYTE == 1 || DATA_BYTE == 4
/* sign immediate */
make_helper(concat(decode_si_, SUFFIX)) {
	op_src->type = OP_TYPE_IMM;

	/* TODO: Use instr_fetch() to read `DATA_BYTE' bytes of memory pointed
	 * by `eip'. Interpret the result as an signed immediate, and assign
	 * it to op_src->simm.
	 *
	op_src->simm = ???
	 */
	//panic("please implement me");
	op_src->simm=(DATA_TYPE_S)instr_fetch(eip,DATA_BYTE);
	op_src->val = op_src->simm;

#ifdef DEBUG
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", op_src->val);
#endif
	return DATA_BYTE;
}
#endif


#if DATA_BYTE==2 || DATA_BYTE==4
/* special decode method for control transfer instructions . */
make_helper(concat(decode_cfsi_,SUFFIX)){
	op_src->type=OP_TYPE_IMM;
	op_src->simm=(DATA_TYPE_S)instr_fetch(eip,DATA_BYTE);
	op_src->val=op_src->simm;

#ifdef DEBUG
	snprintf(op_src->str,OP_STR_SIZE,"$0x%x",op_src->val);
#endif

	if (DATA_BYTE==2)
		return -2;	//1 for opcode , 1 for prefix
	else if (DATA_BYTE==4)
		return -1;	//1 for opcode
}
#endif


/* eAX */
static int concat(decode_a_, SUFFIX) (swaddr_t eip, Operand *op) {
	op->type = OP_TYPE_REG;
	op->reg = R_EAX;
	op->val = REG(R_EAX);

#ifdef DEBUG
	snprintf(op->str, OP_STR_SIZE, "%%%s", REG_NAME(R_EAX));
#endif
	return 0;
}

/* eXX: eAX, eCX, eDX, eBX, eSP, eBP, eSI, eDI */
static int concat3(decode_r_, SUFFIX, _internal) (swaddr_t eip, Operand *op) {
	op->type = OP_TYPE_REG;
	op->reg = ops_decoded.opcode & 0x7;
	op->val = REG(op->reg);

#ifdef DEBUG
	snprintf(op->str, OP_STR_SIZE, "%%%s", REG_NAME(op->reg));
#endif
	return 0;
}

static int concat3(decode_rm_, SUFFIX, _internal) (swaddr_t eip, Operand *rm, Operand *reg) {
	rm->size = DATA_BYTE;
	int len = read_ModR_M(eip, rm, reg);
	reg->val = REG(reg->reg);

#ifdef DEBUG
	snprintf(reg->str, OP_STR_SIZE, "%%%s", REG_NAME(reg->reg));
#endif
	return len;
}

/* Eb <- Gb
 * Ev <- Gv
 */
make_helper(concat(decode_r2rm_, SUFFIX)) {
	return decode_rm_internal(eip, op_dest, op_src);
}

/* Gb <- Eb
 * Gv <- Ev
 */
make_helper(concat(decode_rm2r_, SUFFIX)) {
	return decode_rm_internal(eip, op_src, op_dest);
}


/* AL <- Ib
 * eAX <- Iv
 */
make_helper(concat(decode_i2a_, SUFFIX)) {
	decode_a(eip, op_dest);
	return decode_i(eip);
}

/* Gv <- EvIb
 * Gv <- EvIv
 * use for imul */
make_helper(concat(decode_i_rm2r_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_src2, op_dest);
	len += decode_i(eip + len);
	return len;
}

/* Eb <- Ib
 * Ev <- Iv
 */
make_helper(concat(decode_i2rm_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_dest, op_src2);		/* op_src2 not use here */
	len += decode_i(eip + len);
	return len;
}

/* XX <- Ib
 * eXX <- Iv
 */
make_helper(concat(decode_i2r_, SUFFIX)) {
	decode_r_internal(eip, op_dest);
	return decode_i(eip);
}

/* used by unary operations */
make_helper(concat(decode_rm_, SUFFIX)) {
	return decode_rm_internal(eip, op_src, op_src2);		/* op_src2 not use here */
}

make_helper(concat(decode_r_, SUFFIX)) {
	return decode_r_internal(eip, op_src);
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_helper(concat(decode_si2rm_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_dest, op_src2);	/* op_src2 not use here */
	len += decode_si_b(eip + len);
	return len;
}

make_helper(concat(decode_si_rm2r_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_src2, op_dest);
	len += decode_si_b(eip + len);
	return len;
}
#endif

/* used by shift instructions */
make_helper(concat(decode_rm_1_, SUFFIX)) {
	int len = decode_r2rm(eip);
	op_src->type = OP_TYPE_IMM;
	op_src->imm = 1;
	op_src->val = 1;
#ifdef DEBUG
	sprintf(op_src->str, "$1");
#endif
	return len;
}

make_helper(concat(decode_rm_cl_, SUFFIX)) {
	int len = decode_r2rm(eip);
	op_src->type = OP_TYPE_REG;
	op_src->reg = R_CL;
	op_src->val = reg_b(R_CL);
#ifdef DEBUG
	sprintf(op_src->str, "%%cl");
#endif
	return len;
}

make_helper(concat(decode_rm_imm_, SUFFIX)) {
	int len = decode_r2rm(eip);
	len += decode_i_b(eip + len);
	return len;
}

void concat(write_operand_, SUFFIX) (Operand *op, DATA_TYPE src) {
	if(op->type == OP_TYPE_REG) { REG(op->reg) = src; }
	else if(op->type == OP_TYPE_MEM) { swaddr_write(op->addr, op->size, src, op->sreg); }
	else { assert(0); }
}


#if DATA_BYTE==2 || DATA_BYTE==4
/* special decode method for control transfer instructions . */
make_helper(concat(decode_cfrm_,SUFFIX)){
	decode_rm_internal(eip,op_src,op_src2);

	if (DATA_BYTE==2)
		return -2;	//1 for opcode , 1 for prefix
	else if (DATA_BYTE==4)
		return -1;	//1 for opcode
}

#endif


#if DATA_BYTE==2 || DATA_BYTE==4
/* special decode method for mov 8 byte src to 16 or 32 byte dest with sign extended. */
make_helper( concat(decode_msbrm2r_,SUFFIX) ){
	op_src->size=1;		// 8 byte , so op_src is 1 size.
	int len=read_ModR_M(eip,op_src,op_dest);
	int sv=(((int)(op_src->val))<<24>>24);	//sign extended
	op_src->val=sv;
	op_dest->val=REG(op_dest->reg);	//set dest reg
#ifdef DEBUG
	snprintf(op_dest->str,OP_STR_SIZE,"%%%s",REG_NAME(op_dest->reg));
#endif
	return len;
}

/* special decode method for mov 8 byte src to 16 or 32 byte dest with zero extended. */
make_helper( concat(decode_mzbrm2r_,SUFFIX) ){
	op_src->size=1;		// 8 byte , so op_src is 1 size.
	int len=read_ModR_M(eip,op_src,op_dest);
	op_dest->val=REG(op_dest->reg);	//set dest reg
#ifdef DEBUG
	snprintf(op_dest->str,OP_STR_SIZE,"%%%s",REG_NAME(op_dest->reg));
#endif
	return len;
}

#endif

#if DATA_BYTE==4
/* special decode method for mov 16 byte src to 32 byte dest with sign extended. */
make_helper( concat(decode_mswrm2r_,SUFFIX) ){
	op_src->size=2;		// 16 byte , so op_src is 2 size.
	int len=read_ModR_M(eip,op_src,op_dest);
	int sv=(((int)(op_src->val))<<16>>16);	//sign extended
	op_src->val=sv;
	op_dest->val=REG(op_dest->reg);	//set dest reg
#ifdef DEBUG
	snprintf(op_dest->str,OP_STR_SIZE,"%%%s",REG_NAME(op_dest->reg));
#endif
	return len;
}

/* special decode method for mov 16 byte src to 32 byte dest with zero extended. */
make_helper( concat(decode_mzwrm2r_,SUFFIX) ){
	op_src->size=2;		// 16 byte , so op_src is 2 size.
	int len=read_ModR_M(eip,op_src,op_dest);
	op_dest->val=REG(op_dest->reg);	//set dest reg
#ifdef DEBUG
	snprintf(op_dest->str,OP_STR_SIZE,"%%%s",REG_NAME(op_dest->reg));
#endif
	return len;
}

#endif




#include "cpu/exec/template-end.h"
