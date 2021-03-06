#ifndef __TLB_H__
#define __TLB_H__

#include "common.h"

#define TLB_NR_ITEM 64

#define TLB_TAG_WIDTH 20
#define TLB_OFFSET_WIDTH 12


typedef struct TLBitem{
    bool valid;
    uint32_t tag;
    uint32_t phpagenum;
}TLBitem;

extern TLBitem TLB[TLB_NR_ITEM];

extern double TLB_miss_time;
extern double TLB_visit_time;

void init_TLB();

hwaddr_t TLB_read(lnaddr_t addr);

#endif
