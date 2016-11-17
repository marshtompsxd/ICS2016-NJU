#ifndef __CACHE_H__
#define __CACHE_H__

#include "common.h"

#define CACHEUNIT_LEN 4
#define CACHEUNIT_MASK (CACHEUNIT_LEN-1)

typedef struct cachel1block{
    int valid;
    unsigned tag;
    uint8_t data[64];
}cachel1block;

typedef struct cachel1{
    cachel1block content[128][8];
}cachel1;

typedef struct cachel2block{
    int valid;
    int dirty;
    unsigned tag;
    uint8_t data[64];
}cachel2block;

typedef struct cachel2{
    cachel2block content[4096][16];
}cachel2;

extern cachel1 CL1;
extern cachel2 CL2;

extern double cache_miss_time;
extern double cache_visit_time;

uint32_t cachel1_read(uint32_t addr,uint32_t len);

void cachel1_write(uint32_t addr,uint32_t len,uint32_t data);

uint32_t cachel2_read(uint32_t addr,uint32_t len);

void cachel2_write(uint32_t addr,uint32_t len,uint32_t data);


#endif
