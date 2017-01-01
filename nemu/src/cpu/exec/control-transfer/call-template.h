#include "cpu/exec/template-start.h"

#define instr call

make_helper(concat(call_i_, SUFFIX)){
  int len=concat(decode_i_,SUFFIX)(eip+1);

  if(DATA_BYTE==2){
      //panic("call DATA_BYTE 2");
      cpu.esp-=2;
      MEM_W(cpu.esp,(eip+len+1)&0xffff,SR_SS);
      cpu.eip=(cpu.eip+op_src->val)&0xffff;
      cpu.eip++;
  }
  else{
      cpu.esp-=4;
      MEM_W(cpu.esp,eip+len+1,SR_SS);
      cpu.eip+=op_src->val;
  }
  print_asm_template1();
  return len+1;
}

make_helper(concat(call_rm_, SUFFIX)){
  int len=concat(decode_rm_,SUFFIX)(eip+1);

  if(DATA_BYTE==2){
      //panic("call DATA_BYTE 2");
      cpu.esp-=2;
      MEM_W(cpu.esp,(eip+len+1)&0xffff,SR_SS);
      cpu.eip=(op_src->val)&0xffff;
  }
  else{
      cpu.esp-=4;
      MEM_W(cpu.esp,eip+len+1,SR_SS);
      cpu.eip=op_src->val;
  }
  print_asm_template1();
  return 0;
}


#include "cpu/exec/template-end.h"
