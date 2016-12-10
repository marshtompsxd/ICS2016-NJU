#include "common.h"
#include "cache.h"
#include "TLB.h"
#include "cpu/reg.h"
#include "device/mmio.h"

uint32_t dram_read(hwaddr_t, size_t);

void dram_write(hwaddr_t, size_t, uint32_t);

static lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg);

static hwaddr_t page_translate(lnaddr_t addr);

static bool data_cross_the_page_boundary(lnaddr_t addr,size_t len);

double cache_miss_time=0;

double cache_visit_time=0;

double TLB_miss_time=0;

double TLB_visit_time=0;

/* Calculate cache performance parameter */
double calculate_cache_hit_rate(){
	return (cache_visit_time-cache_miss_time)/cache_visit_time;
}

double calculate_cache_visit_time(){
	return cache_miss_time*200+cache_visit_time*2;
}


/* Calculate TLB performance parameter */
double calculate_TLB_hit_rate(){
	return (TLB_visit_time-TLB_miss_time)/TLB_visit_time;
}

double calculate_TLB_visit_time(){
	return TLB_miss_time*200+TLB_visit_time*2;
}



/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	int map_num=is_mmio(addr);
	if(map_num==-1){
		#ifdef USE_CACHE
			return cachel1_read(addr,len)& (~0u >> ((4 - len) << 3));
		#else
			return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
		#endif
	}
	else{
		return mmio_read(addr,len,map_num);
	}

}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	int map_num=is_mmio(addr);
	if(map_num==-1){
		#ifdef USE_CACHE
			cachel1_write(addr,len,data);
		#else
			dram_write(addr, len, data);
		#endif
	}
	else{
		mmio_write(addr,len,data,map_num);
	}

}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	if(data_cross_the_page_boundary(addr,len)){
		Assert(0,"data cross the page boundary , addr is 0x%x and len is 0x%x.", addr,len);
	}
	else{
		hwaddr_t hwaddr=page_translate(addr);
		return hwaddr_read(hwaddr,len);
	}
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	if(data_cross_the_page_boundary(addr,len)){
		Assert(0,"data cross the page boundary , addr is 0x%x and len is 0x%x.", addr,len);
	}
	else{
		hwaddr_t hwaddr=page_translate(addr);
		hwaddr_write(hwaddr, len, data);
	}
}

uint32_t swaddr_read(swaddr_t addr, size_t len, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr=seg_translate(addr,len,sreg);
	return lnaddr_read(lnaddr,len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr=seg_translate(addr,len,sreg);
	lnaddr_write(lnaddr, len, data);
}

static lnaddr_t seg_translate(swaddr_t addr,size_t len,uint8_t sreg){
	if(cpu.cr0.protect_enable==0){
		return addr;
	}
	else{
		uint32_t limit=cpu.sregdesc[sreg].limit;
		uint32_t base=cpu.sregdesc[sreg].base;
		Assert(len-1<=limit-addr,"addr 0x%x with length %d exceeds the limit.",addr,len);
		return addr+base;
	}
}

static bool data_cross_the_page_boundary(lnaddr_t addr,size_t len){
	uint32_t offset=addr&PAGE_MASK;
	if(len-1>PAGE_SIZE-offset){
		return true;
	}
	else{
		return false;
	}
}


hwaddr_t page_walk(lnaddr_t addr){
	page_addr temp;
	temp.addr=addr;
	uint32_t DIR=temp.DIR;
	uint32_t PAGE=temp.PAGE;
	uint32_t OFFSET=temp.OFFSET;

	PDE pde;
	pde.val=hwaddr_read((cpu.cr3.page_directory_base<<12)+DIR*4,4);
	Assert(pde.present,"null directory entry in address 0x%x.",addr);

	PTE pte;
	pte.val=hwaddr_read((pde.page_frame<<12)+PAGE*4,4);
	Assert(pte.present,"null page table entry in address 0x%x.",addr);

	return (pte.page_frame<<12)+OFFSET;
}

static hwaddr_t page_translate(lnaddr_t addr){
	if(cpu.cr0.paging==0 || cpu.cr0.protect_enable==0){
		return addr;
	}
	else{
#ifdef USE_TLB
		return TLB_read(addr);
#else
		return page_walk(addr);
#endif
	}
}
