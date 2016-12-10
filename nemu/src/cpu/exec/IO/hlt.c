#include "cpu/exec/helper.h"

make_helper(hlt) {
	if( cpu.INTR & cpu.eflags.IF ){
		print_asm("hlt");
		return 1;
	}
	else return 0;
}
