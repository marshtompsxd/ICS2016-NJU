#include "desc.h"


void loadSegDescBase(SegDesc *desc , SegDescBase *descbase){
    descbase->_15_0=desc->base_15_0;
    descbase->_23_16=desc->base_23_16;
    descbase->_31_24=desc->base_31_24;
}

void loadSegDescLimit(SegDesc *desc , SegDescLimit *desclimit){
    desclimit->_15_0=desc->limit_15_0;
    desclimit->_19_16=desc->limit_19_16;
}

void setsreg(SegDesc desc ,SegDescBase descbase, SegDescLimit desclimit, int index){
    if(desc.granularity==0)
        cpu.sregdesc[index].limit=desclimit.limit;
    else
        cpu.sregdesc[index].limit=((desclimit.limit+1)<<12)-1;

    cpu.sregdesc[index].base=descbase.base;
}
