#include <setjmp.h>
#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"
#include "desc.h"

extern jmp_buf jbuf;

static void push(uint32_t data) {
	cpu.esp=cpu.esp-4;
	swaddr_write( cpu.esp, 4, data, SR_SS );
}

void raise_intr(uint8_t ID) {
	push(cpu.eflags.EFLAGS);
	push(cpu.sreg[SR_CS].selector);
	push(cpu.eip);

    cpu.eflags.IF=0;
	cpu.eflags.TF=0;

	GateDesc gatedesc;
	gatedesc.content[0]=lnaddr_read( cpu.idtr.base+ID*8, 4 );
	gatedesc.content[1]=lnaddr_read( cpu.idtr.base+ID*8+4, 4);

	Assert(gatedesc.present==1, "the present of gate descriptor is 0\n");

	cpu.sreg[SR_CS].selector=gatedesc.segment;

/*
    SegDesc segdesc;
    SegDescBase segdescbase;
    SegDescLimit segdesclimit;

	uint32_t index=cpu.sreg[SR_CS].INDEX;
    segdesc.content[0]=lnaddr_read(cpu.gdtr.base+index*8,4);
    segdesc.content[1]=lnaddr_read(cpu.gdtr.base+index*8+4,4);

    Assert(segdesc.present==1,"the present of segment descriptor is 0\n");

    loadSegDescBase(&segdesc,&segdescbase);
    loadSegDescLimit(&segdesc,&segdesclimit);
    setsreg(segdesc, segdescbase, segdesclimit, SR_CS);
*/

    updateSreg(SR_CS);
    
	cpu.eip = gatedesc.offset_15_0+(gatedesc.offset_31_16 << 16);

	longjmp(jbuf, 1);
}
