#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "movsx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movsx-template.h"
#undef DATA_BYTE

make_helper_v(movsx_rmsb2r)

make_helper(movsx_rmsw2r_v){
	return movsx_rmsw2r_l(eip);
}
