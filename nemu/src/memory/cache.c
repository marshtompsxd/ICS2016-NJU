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
double cache_visit_time=0;

typedef union{
    struct{
        uint32_t block_addr : CL1_BLOCK_WIDTH;
        uint32_t set_num : CL1_SET_WIDTH;
        uint32_t tag_bit : CL1_TAG_WIDTH;
    };
    uint32_t addr;
}cachel1_addr;


void init_CL1(){
    printf("execute init CL1\n");
    int i,j;
    for(i=0;i<CL1_NR_SET;i++){
        for(j=0;j<CL1_NR_WAY;j++){
            CL1.content[i][j].valid=0;
            memset(CL1.content[i][j].data,0,CL1_BLOCK_SIZE);
        }
    }
}


static uint32_t readcl1_miss(uint32_t addr,uint32_t set_num){
    cache_miss_time++;

    cachel1_addr temp;
    temp.addr=addr;
    int line;
    for(line=0;line<CL1_NR_WAY;line++){
        if(!CL1.content[set_num][line].valid)
            break;
    }

    if(line==CL1_NR_WAY){
        line=(rand())%CL1_NR_WAY;
    }

    CL1.content[set_num][line].tag=temp.tag_bit;
    CL1.content[set_num][line].valid=1;

    uint32_t block_begin=((addr>>CL1_BLOCK_WIDTH)<<CL1_BLOCK_WIDTH);

    int i;
    for(i=0;i<CL1_BLOCK_SIZE;i++){
        CL1.content[set_num][line].data[i]=(dram_read(block_begin+i,1)&0xff);
    }

    return line;

}

static void cl1byte4_read(uint32_t addr,void* data){
    cache_visit_time++;
    cachel1_addr temp;
    temp.addr=addr;
    uint32_t block_addr=temp.block_addr;
    uint32_t set_num=temp.set_num;
    uint32_t tag_bit=temp.tag_bit;
    uint32_t block_addr_edge=block_addr&(~CACHEUNIT_MASK);

    int line;
    for(line=0;line<CL1_NR_WAY;line++){
        if(CL1.content[set_num][line].valid&&CL1.content[set_num][line].tag==tag_bit)
            break;
    }

    if(line==CL1_NR_WAY){
        line=readcl1_miss(addr,set_num);
    }

    memcpy(data,CL1.content[set_num][line].data+block_addr_edge,CACHEUNIT_LEN);
}

uint32_t cachel1_read(uint32_t addr,uint32_t len){
    cachel1_addr temp;
    temp.addr=addr;
    uint32_t block_addr=temp.block_addr;

    uint32_t offset=block_addr&CACHEUNIT_MASK;

    uint8_t data_temp[2*CACHEUNIT_LEN];
    memset(data_temp,0,sizeof(data_temp));

    cl1byte4_read(addr,data_temp);

    if(offset+len>CACHEUNIT_LEN){
        cl1byte4_read(addr+4,data_temp+4);
    }

    switch (len) {
        case 1:return unalign_rw(data_temp+offset,1);
        case 2:return unalign_rw(data_temp+offset,2);
        case 4:return unalign_rw(data_temp+offset,4);
        default:Assert(0,"wrong cache len: %d\n",len);
    }

}