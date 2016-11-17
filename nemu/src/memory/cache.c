#include "cache.h"
#include "cache-config.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

uint32_t dram_read(hwaddr_t,size_t);

void dram_write(hwaddr_t,size_t,uint32_t);

uint32_t cachel1_read(uint32_t,uint32_t);

void cachel1_write(uint32_t,uint32_t,uint32_t);

uint32_t cachel2_read(uint32_t,uint32_t);

void cachel2_write(uint32_t,uint32_t,uint32_t);

int rand();

cachel1 CL1;

double cache_miss_time=0;
double cahce_visit_time=0;

typedef union{
    struct{
        uint32_t block_addr : CL1_BLOCK_WIDTH;
        uint32_t set_num : CL1_SET_WIDTH;
        uint32_t tag_bit : CL1_TAG_WIDTH;
    };
    uint32_t addr;
}cachel1_addr;
