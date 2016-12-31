#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_, SUFFIX)) {

  int len = 1;
 
  if(DATA_BYTE == 2) {
    uint32_t tmp = (uint32_t)swaddr_read(cpu.gpr[R_ESP]._16, DATA_BYTE, SR_SS);
    cpu.eip = (tmp - len) & 0x0000FFFF;
    cpu.gpr[R_ESP]._16 += 2;
  }
  else{
    uint32_t tmp = (uint32_t)swaddr_read(cpu.esp, DATA_BYTE, SR_SS);
    cpu.eip = tmp - len;
    cpu.gpr[R_ESP]._32 += 4;
  }
   print_asm("ret");
  return len;
}

make_helper(concat(ret_i_, SUFFIX)) {
 
  op_src->type = OP_TYPE_IMM;
  op_src->imm = (uint32_t)swaddr_read(cpu.eip + 1, 2, SR_CS);
  op_src->val = op_src->imm;
  
  int len = 3;

  if(DATA_BYTE == 2) {
    uint32_t tmp = (uint32_t)swaddr_read(cpu.gpr[R_ESP]._16, DATA_BYTE, SR_SS);
    cpu.eip = (tmp - len) & 0x0000FFFF;
    cpu.gpr[R_ESP]._16 += 2;
    cpu.gpr[R_ESP]._16 += op_src->val;
  }
  else{
    uint32_t tmp = (uint32_t)swaddr_read(cpu.esp, DATA_BYTE, SR_SS);
    cpu.eip = tmp - len;
    cpu.gpr[R_ESP]._32 += 4;
    cpu.gpr[R_ESP]._32 += op_src->val;
  }

  print_asm("ret imm");

  return len;
}



#include "cpu/exec/template-end.h"
