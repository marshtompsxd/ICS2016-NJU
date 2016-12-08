#ifndef __DESC_H__
#define __DESC_H__

#include "cpu/reg.h"
#include "../../lib-common/x86-inc/mmu.h"

void loadSegDescBase(SegDesc *desc , SegDescBase *descbase);

void loadSegDescLimit(SegDesc *desc , SegDescLimit *desclimit);

void setHiddenDesc(SegDesc desc ,SegDescBase descbase, SegDescLimit desclimit, int index);

void updateSreg(uint32_t sreg);

#endif
