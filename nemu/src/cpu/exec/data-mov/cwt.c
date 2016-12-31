#include "cpu/exec/helper.h"

make_helper(cwt_w) {
    reg_w(R_AX) = (int16_t)(int8_t)reg_b(R_AL);

    print_asm("cbw");
    return 1;
}

make_helper(cwt_l) {
    cpu.eax = (int32_t)(int16_t)reg_w(R_AX);

    print_asm("cwde");
    return 1;
}

make_helper_v(cwt);
