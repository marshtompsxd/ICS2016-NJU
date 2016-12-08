#include "cpu/exec/helper.h"

make_helper(cli) {
	cpu.eflags.IF=0;
	print_asm("cli");
	return 1;
}

make_helper(sti) {
	cpu.eflags.IF=1;
	print_asm("sti");
	return 1;
}
