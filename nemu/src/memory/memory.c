#include "common.h"
#include "cache.h"
#include "cpu/reg.h"

uint32_t dram_read(hwaddr_t, size_t);

void dram_write(hwaddr_t, size_t, uint32_t);

static lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg);

double cache_miss_time=0;

double cache_visit_time=0;


/* Calculate cache performance parameter */
double calculate_hit_rate(){
	return (cache_visit_time-cache_miss_time)/cache_visit_time;
}

double calculate_visit_time(){
	return cache_miss_time*200+cache_visit_time*2;
}

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
#ifdef USE_CACHE
	return cachel1_read(addr,len)& (~0u >> ((4 - len) << 3));
#else
	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
#endif
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
#ifdef USE_CACHE
	cachel1_write(addr,len,data);
#else
	dram_write(addr, len, data);
#endif
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
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
		uint32_t limit=cpu.sreg[sreg].hidden_descriptor.limit;
		uint32_t base=cpu.sreg[sreg].hidden_descriptor.base;
		Assert(addr<=limit,"address %x + %x is out of the limit.",base,addr);
		return addr+base;
	}
}
