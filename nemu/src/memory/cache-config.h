#ifndef __CACHE_CONFIG_H__
#define __CACHE_CONFIG_H__


#define DIRECT 0
#define FULL 1
#define SET 2

#define FIFO 0
#define LRU 1
#define LFU 2
#define RAND 3

#define THROUGH_ALLOC 0
#define THROUGH_NOALLOC 1
#define BACK 2

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
#define CL2_WRITE_MODE BACK
#define CL2_NR_SET 4096
#define CL2_BLOCK_WIDTH 6
#define CL2_SET_WIDTH 12
#define CL2_TAG_WIDTH (27-CL2_BLOCK_WIDTH-CL2_SET_WIDTH)

#endif