#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "cmovcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmovcc-template.h"
#undef DATA_BYTE


make_helper_v(cmova_rm2r)
make_helper_v(cmovae_rm2r)
make_helper_v(cmovb_rm2r)
make_helper_v(cmovbe_rm2r)
make_helper_v(cmove_rm2r)
make_helper_v(cmovg_rm2r)
make_helper_v(cmovge_rm2r)
make_helper_v(cmovl_rm2r)
make_helper_v(cmovle_rm2r)
make_helper_v(cmovne_rm2r)
make_helper_v(cmovno_rm2r)
make_helper_v(cmovnp_rm2r)
make_helper_v(cmovns_rm2r)
make_helper_v(cmovo_rm2r)
make_helper_v(cmovp_rm2r)
make_helper_v(cmovs_rm2r)
