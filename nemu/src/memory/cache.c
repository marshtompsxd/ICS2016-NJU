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
cachel2 CL2;

extern double cache_miss_time;
extern double cache_visit_time;

typedef union{
    struct{
        uint32_t block_addr : CL1_BLOCK_WIDTH;
        uint32_t set_num : CL1_SET_WIDTH;
        uint32_t tag_bit : CL1_TAG_WIDTH;
    };
    uint32_t addr;
}cachel1_addr;

typedef union{
    struct{
        uint32_t block_addr : CL2_BLOCK_WIDTH;
        uint32_t set_num : CL2_SET_WIDTH;
        uint32_t tag_bit : CL2_TAG_WIDTH;
    };
    uint32_t addr;
}cachel2_addr;

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

void init_CL2(){
    printf("execute init CL2\n");
    int i,j;
    for(i=0;i<CL2_NR_SET;i++){
        for(j=0;j<CL2_NR_WAY;j++){
            CL2.content[i][j].valid=0;
            CL2.content[i][j].dirty=0;
            memset(CL2.content[i][j].data,0,CL2_BLOCK_SIZE);
        }
    }
}


/* cache level 1 */
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
        CL1.content[set_num][line].data[i]=(cachel2_read(block_begin+i,1)&0xff);
    }

    return line;

}

static void cl1unit_read(uint32_t addr,void* data){
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

    cl1unit_read(addr,data_temp);

    if(offset+len>CACHEUNIT_LEN){
        cl1unit_read(addr+4,data_temp+4);
    }

    return unalign_rw(data_temp+offset,4);

}

static void cl1unit_write(uint32_t addr,uint8_t*data,uint8_t*mask){
    cache_visit_time++;

    cachel1_addr temp;
    temp.addr=addr;
    uint32_t block_addr=temp.block_addr;
    uint32_t set_num=temp.set_num;
    uint32_t tag_bit=temp.tag_bit;
    uint32_t block_addr_edge=block_addr&(~CACHEUNIT_MASK);

    uint32_t len=0,offset=0;
    int k;
    for(k=0;k<4;k++){
        if(mask[k]==1)len++;
    }
    for(k=0;k<4;k++){
        if(mask[k]==1){
            offset=k;
            break;
        }
    }

    int line;
    for(line=0;line<CL1_NR_WAY;line++){
        if((CL1.content[set_num][line].valid)&&(CL1.content[set_num][line].tag==tag_bit))
            break;
    }

    if(line==CL1_NR_WAY){
        //cachel2_write((addr&(~CACHEUNIT_MASK))+offset, len, unalign_rw(data+offset,4));
        cachel2_write(addr, len, unalign_rw(data+offset,4));
        readcl1_miss(addr,set_num);
    }
    else{
        int i;
        for(i=0;i<4;i++){
            if(mask[i]){
                CL1.content[set_num][line].data[block_addr_edge+i]=data[i];
            }
        }
        cachel2_write((addr&(~CACHEUNIT_MASK))+offset,len,unalign_rw(data+offset,4));
    }
}

void cachel1_write(uint32_t addr,uint32_t len,uint32_t data){
    uint32_t offset=addr&CACHEUNIT_MASK;
    uint8_t temp[2*CACHEUNIT_LEN];
    uint8_t mask[2*CACHEUNIT_LEN];

    memset(mask,0,2*CACHEUNIT_LEN);

    *(uint32_t *)(temp+offset)=data;
    memset(mask+offset,1,len);

    cl1unit_write(addr,temp,mask);

    if((offset+len)>CACHEUNIT_LEN){
        cl1unit_write(addr+CACHEUNIT_LEN,temp+CACHEUNIT_LEN,mask+CACHEUNIT_LEN);
    }

}

/* cache level 2 */

static uint32_t readcl2_miss(uint32_t addr,uint32_t set_num){
    cache_miss_time++;

    cachel2_addr temp;
    temp.addr=addr;
    int line;
    for(line=0;line<CL2_NR_WAY;line++){
        if(!CL2.content[set_num][line].valid)
            break;
    }

    if(line==CL2_NR_WAY){
        line=(rand())%CL2_NR_WAY;

        if(CL2.content[set_num][line].dirty){
            int i;
            uint32_t addr_begin=((CL2.content[set_num][line].tag)<<(CL2_BLOCK_WIDTH+CL2_SET_WIDTH))+(set_num<<(CL2_BLOCK_WIDTH));
            for(i=0;i<CL2_BLOCK_SIZE;i++){
                dram_write(addr_begin+i,1,CL2.content[set_num][line].data[i]);
            }
        }

        CL2.content[set_num][line].dirty=0;
    }

    CL2.content[set_num][line].tag=temp.tag_bit;
    CL2.content[set_num][line].valid=1;

    uint32_t block_begin=((addr>>CL2_BLOCK_WIDTH)<<CL2_BLOCK_WIDTH);

    int i;
    for(i=0;i<CL2_BLOCK_SIZE;i++){
        CL2.content[set_num][line].data[i]=(dram_read(block_begin+i,1)&0xff);
    }

    return line;

}

static void cl2unit_read(uint32_t addr,void* data){
    cache_visit_time++;
    cachel2_addr temp;
    temp.addr=addr;
    uint32_t block_addr=temp.block_addr;
    uint32_t set_num=temp.set_num;
    uint32_t tag_bit=temp.tag_bit;
    uint32_t block_addr_edge=block_addr&(~CACHEUNIT_MASK);

    int line;
    for(line=0;line<CL2_NR_WAY;line++){
        if(CL2.content[set_num][line].valid&&CL2.content[set_num][line].tag==tag_bit)
            break;
    }

    if(line==CL2_NR_WAY){
        line=readcl2_miss(addr,set_num);
    }

    memcpy(data,CL2.content[set_num][line].data+block_addr_edge,CACHEUNIT_LEN);
}

uint32_t cachel2_read(uint32_t addr,uint32_t len){
    cachel2_addr temp;
    temp.addr=addr;
    uint32_t block_addr=temp.block_addr;

    uint32_t offset=block_addr&CACHEUNIT_MASK;

    uint8_t data_temp[2*CACHEUNIT_LEN];
    memset(data_temp,0,sizeof(data_temp));

    cl2unit_read(addr,data_temp);

    if(offset+len>CACHEUNIT_LEN){
        cl2unit_read(addr+4,data_temp+4);
    }

    return unalign_rw(data_temp+offset,4);

}

static void cl2unit_write(uint32_t addr,uint8_t*data,uint8_t*mask){
    cache_visit_time++;

    cachel2_addr temp;
    temp.addr=addr;
    uint32_t block_addr=temp.block_addr;
    uint32_t set_num=temp.set_num;
    uint32_t tag_bit=temp.tag_bit;
    uint32_t block_addr_edge=block_addr&(~CACHEUNIT_MASK);

    uint32_t len=0,offset=0;
    int k;
    for(k=0;k<4;k++){
        if(mask[k]==1)len++;
    }
    for(k=0;k<4;k++){
        if(mask[k]==1){
            offset=k;
            break;
        }
    }

    int line;
    for(line=0;line<CL2_NR_WAY;line++){
        if((CL2.content[set_num][line].valid)&&(CL2.content[set_num][line].tag==tag_bit))
            break;
    }

    if(line==CL2_NR_WAY){
        dram_write((addr&(~CACHEUNIT_MASK))+offset, len, unalign_rw(data+offset,4));
        readcl2_miss(addr,set_num);
    }
    else{
        int i;
        for(i=0;i<4;i++){
            if(mask[i]){
                CL2.content[set_num][line].data[block_addr_edge+i]=data[i];
            }
        }
        CL2.content[set_num][line].dirty=1;
    }
}

void cachel2_write(uint32_t addr,uint32_t len,uint32_t data){
    uint32_t offset=addr&CACHEUNIT_MASK;
    uint8_t temp[2*CACHEUNIT_LEN];
    uint8_t mask[2*CACHEUNIT_LEN];

    memset(mask,0,2*CACHEUNIT_LEN);

    *(uint32_t *)(temp+offset)=data;
    memset(mask+offset,1,len);

    cl2unit_write(addr,temp,mask);

    if((offset+len)>CACHEUNIT_LEN){
        cl2unit_write(addr+CACHEUNIT_LEN,temp+CACHEUNIT_LEN,mask+CACHEUNIT_LEN);
    }

}
