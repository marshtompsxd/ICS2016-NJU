#ifndef __DESC_H__
#define __DESC_H__

#include "cpu/reg.h"
#include "../../lib-common/x86-inc/mmu.h"

void loadbase(SegDesc *desc , SegDescBase *descbase);

void loadlimit(SegDesc *desc , SegDescLimit *desclimit);

void setsreg(SegDesc desc ,SegDescBase descbase, SegDescLimit desclimit, int index);

#endif
