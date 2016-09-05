#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "leave-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "leave-template.h"
#undef DATA_BYTE

make_helper(leave_w)
{
	do_leave_w();
	return 1;
}

make_helper(leave_l)
{
	do_leave_l();
	return 1;
}

make_helper_v(leave)
