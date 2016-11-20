#ifndef __REG_H__
#define __REG_H__

#include "common.h"
#include "../../../lib-common/x86-inc/cpu.h"

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };
enum { SR_ES, SR_CS, SR_SS, SR_DS};

/* TODO: Re-organize the `CPU_state' structure to match the register
 * encoding scheme in i386 instruction format. For example, if we
 * access cpu.gpr[3]._16, we will get the `bx' register; if we access
 * cpu.gpr[1]._8[1], we will get the 'ch' register. Hint: Use `union'.
 * For more details about the register encoding scheme, see i386 manual.
 */


/* the union is just the gprs in CPU
 * you can visit the registers by gpr[index]._bytewidth
 * or you can just visit eax or ebx or any other registers
 */


typedef struct {

/* General-Purpose Register Set part of the cpu */

	union{
		union {
			uint32_t _32;
			uint16_t _16;
			uint8_t _8[2];
		} gpr[8];

	/* Do NOT change the order of the GPRs' definitions. */

    	struct{
	    	uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
    	};
	};

/* EIP of the cpu */
    swaddr_t eip;

/* EFLAGS part of the cpu  */
    union{
    	struct {
    		unsigned CF:1;
			unsigned SPACE1:1;
    		unsigned PF:1;
			unsigned SPACE0_0:1;
			unsigned AF:1;
			unsigned SPACE0_1:1;
    		unsigned ZF:1;
    		unsigned SF:1;
			unsigned TF:1;
    		unsigned IF:1;
    		unsigned DF:1;
    		unsigned OF:1;
			unsigned IOPL:2;
			unsigned NT:1;
			unsigned SPACE0_2:1;
			unsigned RF:1;
			unsigned VM:1;
			unsigned LSPACE:14;
    	};
    	uint32_t EFLAGS;
	}eflags;

/* Segment Register part of the cpu */
	struct{
		union{
			struct{
				uint16_t RPL:2;
				uint16_t TI:1;
				uint16_t INDEX:13;
			};
			uint16_t SELECTOR;
		}selector;

		union{
			struct{
				uint32_t limit;
				uint32_t base;
			};
			uint64_t HIDDEN_DESCRIPTOR;
		}hidden_descriptor;
	}sreg[4];

/* Global Descriptor Table Register part of the cpu */
	struct{
		uint16_t limit;
		uint32_t base;
	}gdtr;

/* Control Register 0 part of the cpu */
	CR0 cr0;

} CPU_state;

extern CPU_state cpu;

static inline int check_reg_index(int index) {
	assert(index >= 0 && index < 8);
	return index;
}


#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index) & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
