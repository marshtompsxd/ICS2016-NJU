#include "FLOAT.h"

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	//nemu_assert(0);
	//return 0;
	long long la=a;
	long long lb=b;
	long long lresult=la*lb;
	FLOAT result=lresult>>16;
	return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	/* Dividing two 64-bit integers needs the support of another library
	 * `libgcc', other than newlib. It is a dirty work to port `libgcc'
	 * to NEMU. In fact, it is unnecessary to perform a "64/64" division
	 * here. A "64/32" division is enough.
	 *
	 * To perform a "64/32" division, you can use the x86 instruction
	 * `div' or `idiv' by inline assembly. We provide a template for you
	 * to prevent you from uncessary details.
	 *
	 *     asm volatile ("??? %2" : "=a"(???), "=d"(???) : "r"(???), "a"(???), "d"(???));
	 *
	 * If you want to use the template above, you should fill the "???"
	 * correctly. For more information, please read the i386 manual for
	 * division instructions, and search the Internet about "inline assembly".
	 * It is OK not to use the template above, but you should figure
	 * out another way to perform the division.
	 */

	// nemu_assert(0);
	// return 0;

	 int sign=1;
	 int ta,tb;

	 /*calculate the sign of result by checkout a and b . */
	 if(a<0){
	 	sign*=-1;
	 	ta=-a;
	 }
	 else{
	 	ta=a;
	}
	 if(b<0){
	 	sign*=-1;
	 	tb=-b;
	 }
	 else{
	 	tb=b;
	}

	/* calculate the integer part of result . */
	 int result=ta/tb;
	 int remainder=ta%tb;

	 /* calculate the fraction part of result . */
	 int i;
	 for(i=0;i<16;i++){
	 	remainder<<=1;
	 	result<<=1;
	 	if(remainder>=tb){
	 		remainder-=tb;
	 		result++;
	 	}
	 }

	 return result*sign;
}

FLOAT f2F(float a) {
	/* You should figure out how to convert `a' into FLOAT without
	 * introducing x87 floating point instructions. Else you can
	 * not run this code in NEMU before implementing x87 floating
	 * point instructions, which is contrary to our expectation.
	 *
	 * Hint: The bit representation of `a' is already on the
	 * stack. How do you retrieve it to another variable without
	 * performing arithmetic operations on it directly?
	 */

	// nemu_assert(0);
	// return 0;


	/*use union to transfer the float to uint32_t type, which is also FLOAT type. */
	 typedef union{
	 	float fl;
	 	uint32_t ut;
	 }ua;
	 ua uA;

	 uA.fl=a;
	 uint32_t fta=uA.ut;

	 /*split and extract the sign , exp and tail part of the float . */
	 uint32_t sign=fta>>31;
	 int exponential=(fta>>23)&0xff;
	 uint32_t result=fta&0x7fffff;

	 /*supplement the 1 of integer part of result. */
	 if(exponential!=0)
	 	result+=(1<<23);

	 /*move the radix point to the right place by checkout the exp part . */
	 exponential-=127;
	 if(exponential<7)
	  	 result>>=(7-exponential);
	 else if(exponential>7)
	 	 result<<=(exponential-7);

	 /*determine the sign of result by sign part . */
	 if(sign==0)
	 	 return result;
	 else
	 	 return -result;

}

FLOAT Fabs(FLOAT a) {
	// nemu_assert(0);
	// return 0;
	return (a>=0)?a:-a;
}

/* Functions below are already implemented */

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}
