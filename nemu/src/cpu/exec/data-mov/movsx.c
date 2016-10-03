#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "movsx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movsx-template.h"
#undef DATA_BYTE

make_helper_v(movsx_msbrm2r)

make_helper(movsx_mswrm2r_v){
	return movsx_mswrm2r_l(eip);
}
