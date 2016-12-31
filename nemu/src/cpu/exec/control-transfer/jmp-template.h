#include "cpu/exec/template-start.h"

#define instr jmp

#if DATA_BYTE == 1
make_helper(concat(jmp_si_,SUFFIX)){

  int len=concat(decode_si_,SUFFIX)(eip+1);

  cpu.eip+=op_src->val;
  print_asm_template1();

  return len+1;
}
#endif



#if DATA_BYTE == 2 || DATA_BYTE == 4
make_helper(concat(jmp_i_,SUFFIX)){

  int len=concat(decode_i_,SUFFIX)(eip+1);
  if(DATA_BYTE==2){
    panic("jmp DATA_BYTE 2");
  }
  else if(DATA_BYTE==4){
    cpu.eip+=op_src->val;

  }
  print_asm_template1();

  return len+1;

}

make_helper(concat(jmp_rm_,SUFFIX)){
  concat(decode_rm_,SUFFIX)(eip+1);

  if(DATA_BYTE==2){
    panic("jmp DATA_BYTE 2");
  }
  else if(DATA_BYTE==4){
    cpu.eip=op_src->val;
  }
  print_asm_template1();

  return 0;
}
#endif


#include "cpu/exec/template-end.h"
