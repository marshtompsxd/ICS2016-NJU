#include "TLB.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

TLBitem TLB[TLB_NR_ITEM];

hwaddr_t page_walk(lnaddr_t);

extern double TLB_miss_time;
extern double TLB_visit_time;


void init_TLB(){
    printf("execute init TLB\n");
    int i;
    for(i=0;i<TLB_NR_ITEM;i++){
        TLB[i].valid=0;
    }
}


typedef union{
    struct{
        uint32_t offset_bit : TLB_OFFSET_WIDTH;
        uint32_t tag_bit : TLB_TAG_WIDTH;
    };
    uint32_t addr;
}TLB_addr;


static uint32_t readTLB_miss(lnaddr_t addr){
    TLB_miss_time++;

    TLB_addr temp;
    temp.addr = addr;
    uint32_t tag_bit=temp.tag_bit;

    int item;
    for(item=0;item<TLB_NR_ITEM;item++){
        if(!TLB[item].valid){
            break;
        }
    }

    if(item==TLB_NR_ITEM){
        srand(time(NULL));
        item=(rand())%TLB_NR_ITEM;
    }

    TLB[item].valid=1;
    TLB[item].tag=tag_bit;
    TLB[item].phpagenum=(page_walk(addr))>>TLB_OFFSET_WIDTH;

    return item;

}


hwaddr_t TLB_read(lnaddr_t addr){
    TLB_visit_time++;

    TLB_addr temp;
    temp.addr = addr;
    uint32_t offset_bit=temp.offset_bit;
    uint32_t tag_bit=temp.tag_bit;

    int item;
    for(item=0;item<TLB_NR_ITEM;item++){
        if(TLB[item].valid&&(TLB[item].tag==tag_bit)){
            break;
        }
    }

    if(item==TLB_NR_ITEM){
        item=readTLB_miss(addr);
    }

    hwaddr_t hwaddr=(TLB[item].phpagenum<<TLB_OFFSET_WIDTH)+offset_bit;
    return hwaddr;

}
