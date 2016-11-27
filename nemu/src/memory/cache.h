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



/* cache configuration */
#define DIRECT 0
#define FULL 1
#define SET 2

#define FIFO 0
#define LRU 1
#define LFU 2
#define RAND 3

#define THROUGH_ALLOC 0
#define THROUGH_NOALLOC 1
#define BACK_ALLOC 2
#define BACK_NOALLOC 3

#define CL1_BLOCK_SIZE 64
#define CL1_ALL_SIZE (64<<10)
#define CL1_NR_WAY 8
#define CL1_MAP_MODE SET
#define CL1_REPLACE_MODE RAND
#define CL1_WRITE_MODE THROUGH_NOALLOC
#define CL1_NR_SET 128
#define CL1_BLOCK_WIDTH 6
#define CL1_SET_WIDTH 7
#define CL1_TAG_WIDTH (27-CL1_BLOCK_WIDTH-CL1_SET_WIDTH)

#define CL2_BLOCK_SIZE 64
#define CL2_ALL_SIZE (4<<20)
#define CL2_NR_WAY 16
#define CL2_MAP_MODE SET
#define CL2_REPLACE_MODE RAND
#define CL2_WRITE_MODE BACK_ALLOC
#define CL2_NR_SET 4096
#define CL2_BLOCK_WIDTH 6
#define CL2_SET_WIDTH 12
#define CL2_TAG_WIDTH (27-CL2_BLOCK_WIDTH-CL2_SET_WIDTH)



#endif
