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

	 FLOAT temp1=a;
	FLOAT temp2=b;
	int flag1=0;
	int flag2=0;

	if(temp1<0)
	{
		flag1=1;
		temp1=-a;
	}
	if(temp2<0)
	{
		flag2=1;
		temp2=-b;
	}

	int f=flag1^flag2;
	FLOAT result=temp1/temp2;
	FLOAT temp=temp1-temp2*result;
	FLOAT r=0;
	int count=1;
	do{
		count++;
		temp=temp<<1;
		if(temp>=temp2)
		{
			if(count==1)
				r=1;
			else
				r=(r<<1)+1;
		
			temp-=temp2;
		}
		else
			r=0;
	}while(temp>0&&count<=16);

	if(f==1)
		return -((result<<16)+(r<<(17-count)));
	else
		return (result<<16)+(r<<(17-count));
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


	 // void *uff = &a;
	 // uint32_t fta = *(uint32_t *)uff;
	 typedef union{
	 	float fl;
	 	uint32_t ut;
	 }ua;
	 ua uA;
	 //uint32_t fta= *(uint32_t *)(&a);
	 uA.fl=a;
	 uint32_t fta=uA.ut;
	 uint32_t sign=fta>>31;
	 int exp=(fta>>23)&0xff;
	 uint32_t result=fta&0x7fffff;
	 if(exp!=0)result+=1<<23;
	 exp-=150;
	 if(exp<-16)result>>=-16-exp;
	 if(exp>-16)result<<=exp+16;
	 return sign==0?result:-result;

}

FLOAT Fabs(FLOAT a) {
	// nemu_assert(0);
	// return 0;
	return (a>=0)?a:(-1*a);
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

