#include "desc.h"


void loadbase(SegDesc *desc , SegDescBase *descbase){
    descbase->_15_0=desc->base_15_0;
    descbase->_23_16=desc->base_23_16;
    descbase->_31_24=desc->base_31_24;
}

void loadlimit(SegDesc *desc , SegDescLimit *desclimit){
    desclimit->_15_0=desc->limit_15_0;
    desclimit->_19_16=desc->limit_19_16;
}

void setsreg(SegDesc desc ,SegDescBase descbase, SegDescLimit desclimit, int index){
    if(desc.granularity==0)
        cpu.sreg[index].hidden_descriptor.limit=desclimit.limit;
    else
        cpu.sreg[index].hidden_descriptor.limit=desclimit.limit<<12;

    cpu.sreg[index].hidden_descriptor.base=descbase.base;
}
