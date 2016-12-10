#include "raise_intr.h"

extern jmp_buf jbuf;



void raise_intr(uint8_t ID) {
	//printf("raise interrupt with ID %d\n",ID );

	//printf("push eflags %d\n",cpu.eflags.EFLAGS );
	cpu.esp=cpu.esp-4;
	swaddr_write( cpu.esp, 4, cpu.eflags.EFLAGS, SR_SS );

	//printf("push cs selector %d\n",cpu.sreg[SR_CS].selector );
	cpu.esp=cpu.esp-4;
	swaddr_write( cpu.esp, 4, cpu.sreg[SR_CS].selector, SR_SS );

	//printf("push eip %d\n", cpu.eip);
	cpu.esp=cpu.esp-4;
	swaddr_write( cpu.esp, 4, cpu.eip, SR_SS );

    cpu.eflags.IF=0;
	cpu.eflags.TF=0;

	GateDesc gatedesc;
	gatedesc.content[0]=lnaddr_read( cpu.idtr.base+ID*8, 4 );
	gatedesc.content[1]=lnaddr_read( cpu.idtr.base+ID*8+4, 4);

	Assert(gatedesc.present==1, "the present of gate descriptor is 0\n");

	cpu.eip = gatedesc.offset_15_0+(gatedesc.offset_31_16 << 16);
	cpu.sreg[SR_CS].selector=gatedesc.segment;

    updateSreg(SR_CS);
	//printf("sreg %d base is %x\n",SR_CS,cpu.sregdesc[SR_CS].base );
	//printf("sreg %d limit is %x\n",SR_CS,cpu.sregdesc[SR_CS].limit );



	longjmp(jbuf, 1);
}
