#include <stdio.h>
#include <stdint.h>
#include "FLOAT.h"
//#include <sys/mman.h>

extern char _vfprintf_internal;
extern char _fpmaxtostr;
extern char _ppfs_setargs;
extern int __stdio_fwrite(char *buf, int len, FILE *stream);

__attribute__((used)) static int format_FLOAT(FILE *stream, FLOAT f) {
	/* TODO: Format a FLOAT argument `f' and write the formating
	 * result to `stream'. Keep the precision of the formating
	 * result with 6 by truncating. For example:
	 *              f          result
	 *         0x00010000    "1.000000"
	 *         0x00013333    "1.199996"
	 */

	/*
	char buf[80];
	int len = sprintf(buf, "0x%08x", f);
	return __stdio_fwrite(buf, len, stream);
	*/

	char buf[80];
	int integer;
	int fraction;
	int ilen, flen;
	int negflag;
	if(f<0){
		f=-f;
		negflag=1;
	}
	else{
		negflag=0;
	}

	integer=(f&0x7fffffff)>>16;	//extract the integer
	fraction=(((long long)f&0xffff)*1000000)>>16;	//extract the fraction

	/*output differs with the sign*/
	if(negflag){
		ilen = sprintf(buf, "-%d.", integer);
	}
	else{
		ilen = sprintf(buf, "%d.", integer);
	}
	flen = sprintf(buf+ilen, "%d", fraction);

	/*implement with 0 if len < 6*/
	while (flen<6) {
		buf[ilen+flen]='0';
		flen++;
	}

	buf[ilen+flen]='\0';//don't forget the '\0'!!!
	return __stdio_fwrite(buf, ilen+flen, stream);
}

static void modify_vfprintf() {
	/* TODO: Implement this function to hijack the formating of "%f"
	 * argument during the execution of `_vfprintf_internal'. Below
	 * is the code section in _vfprintf_internal() relative to the
	 * hijack.
	 */

	 /*
 	08048bee <_vfprintf_internal>:

 						   ............

 	8048ed2:	db 2a                	fldt   (%edx)
 	8048ed4:	eb 02                	jmp    8048ed8 <_vfprintf_internal+0x2ea>
 	8048ed6:	dd 02                	fldl   (%edx)
 	8048ed8:	53                   	push   %ebx
 	8048ed9:	53                   	push   %ebx
 	8048eda:	68 87 8b 04 08       	push   $0x8048b87
 	8048edf:	8d 84 24 a4 00 00 00 	lea    0xa4(%esp),%eax
 	8048ee6:	50                   	push   %eax
 	8048ee7:	83 ec 0c             	sub    $0xc,%esp
 	8048eea:	db 3c 24             	fstpt  (%esp)
 	8048eed:	ff b4 24 8c 01 00 00 	pushl  0x18c(%esp)
 	8048ef4:	e8 66 f6 ff ff       	call   804855f <_fpmaxtostr>
 	8048ef9:	83 c4 20             	add    $0x20,%esp
 	*/


	 //mprotect((void	*)(((int)&_vfprintf_internal+775-100)&0xfffff000), 4096*2, PROT_READ | PROT_WRITE | PROT_EXEC);

	 int *addr=(int*)(&_vfprintf_internal+775);
	 *addr+=(int)((unsigned)&format_FLOAT-(unsigned)&_fpmaxtostr);	//call format_FLOAT


	 *(char*)(&_vfprintf_internal+0x2e4)=0x90;	//fldt to nop
	 *(char*)(&_vfprintf_internal+0x2e5)=0x90;	//fldt to nop
	 *(char*)(&_vfprintf_internal+0x2e8)=0x90;	//fldl to nop
	 *(char*)(&_vfprintf_internal+0x2e9)=0x90;	//fldl to nop
	 *(char*)(&_vfprintf_internal+0x2fb)=0x08;	//esp minus 8 because the stack depth has changed.
	 *(char*)(&_vfprintf_internal+0x2fc)=0xff;	//fstpt to push (%edx)
	 *(char*)(&_vfprintf_internal+0x2fd)=0x32;
	 *(char*)(&_vfprintf_internal+0x2fe)=0x90;	//implement with nop




#if 0
	else if (ppfs->conv_num <= CONV_A) {  /* floating point */
		ssize_t nf;
		nf = _fpmaxtostr(stream,
				(__fpmax_t)
				(PRINT_INFO_FLAG_VAL(&(ppfs->info),is_long_double)
				 ? *(long double *) *argptr
				 : (long double) (* (double *) *argptr)),
				&ppfs->info, FP_OUT );
		if (nf < 0) {
			return -1;
		}
		*count += nf;

		return 0;
	} else if (ppfs->conv_num <= CONV_S) {  /* wide char or string */
#endif

	/* You should modify the run-time binary to let the code above
	 * call `format_FLOAT' defined in this source file, instead of
	 * `_fpmaxtostr'. When this function returns, the action of the
	 * code above should do the following:
	 */

#if 0
	else if (ppfs->conv_num <= CONV_A) {  /* floating point */
		ssize_t nf;
		nf = format_FLOAT(stream, *(FLOAT *) *argptr);
		if (nf < 0) {
			return -1;
		}
		*count += nf;

		return 0;
	} else if (ppfs->conv_num <= CONV_S) {  /* wide char or string */
#endif

}

static void modify_ppfs_setargs() {
	/* TODO: Implement this function to modify the action of preparing
	 * "%f" arguments for _vfprintf_internal() in _ppfs_setargs().
	 * Below is the code section in _vfprintf_internal() relative to
	 * the modification.
	 */

	 /*
	 0804910e <_ppfs_setargs>:

	 					............

	804917d:       75 44                   jne    80491c3 <_ppfs_setargs+0xb5>
    804917f:       8d 5a 08                lea    0x8(%edx),%ebx
    8049182:       dd 02                   fldl   (%edx)

	*/


	/*jump to longlong*/
	 *(char*)(&_ppfs_setargs+0x71)=0xeb;
	 *(char*)(&_ppfs_setargs+0x72)=0x30;
	 *(char*)(&_ppfs_setargs+0x73)=0x90;

#if 0
	enum {                          /* C type: */
		PA_INT,                       /* int */
		PA_CHAR,                      /* int, cast to char */
		PA_WCHAR,                     /* wide char */
		PA_STRING,                    /* const char *, a '\0'-terminated string */
		PA_WSTRING,                   /* const wchar_t *, wide character string */
		PA_POINTER,                   /* void * */
		PA_FLOAT,                     /* float */
		PA_DOUBLE,                    /* double */
		__PA_NOARG,                   /* non-glibc -- signals non-arg width or prec */
		PA_LAST
	};

	/* Flag bits that can be set in a type returned by `parse_printf_format'.  */
	/* WARNING -- These differ in value from what glibc uses. */
#define PA_FLAG_MASK		(0xff00)
#define __PA_FLAG_CHAR		(0x0100) /* non-gnu -- to deal with hh */
#define PA_FLAG_SHORT		(0x0200)
#define PA_FLAG_LONG		(0x0400)
#define PA_FLAG_LONG_LONG	(0x0800)
#define PA_FLAG_LONG_DOUBLE	PA_FLAG_LONG_LONG
#define PA_FLAG_PTR		(0x1000) /* TODO -- make dynamic??? */

	while (i < ppfs->num_data_args) {
		switch(ppfs->argtype[i++]) {
			case (PA_INT|PA_FLAG_LONG_LONG):
				GET_VA_ARG(p,ull,unsigned long long,ppfs->arg);
				break;
			case (PA_INT|PA_FLAG_LONG):
				GET_VA_ARG(p,ul,unsigned long,ppfs->arg);
				break;
			case PA_CHAR:	/* TODO - be careful */
				/* ... users could use above and really want below!! */
			case (PA_INT|__PA_FLAG_CHAR):/* TODO -- translate this!!! */
			case (PA_INT|PA_FLAG_SHORT):
			case PA_INT:
				GET_VA_ARG(p,u,unsigned int,ppfs->arg);
				break;
			case PA_WCHAR:	/* TODO -- assume int? */
				/* we're assuming wchar_t is at least an int */
				GET_VA_ARG(p,wc,wchar_t,ppfs->arg);
				break;
				/* PA_FLOAT */
			case PA_DOUBLE:
				GET_VA_ARG(p,d,double,ppfs->arg);
				break;
			case (PA_DOUBLE|PA_FLAG_LONG_DOUBLE):
				GET_VA_ARG(p,ld,long double,ppfs->arg);
				break;
			default:
				/* TODO -- really need to ensure this can't happen */
				assert(ppfs->argtype[i-1] & PA_FLAG_PTR);
			case PA_POINTER:
			case PA_STRING:
			case PA_WSTRING:
				GET_VA_ARG(p,p,void *,ppfs->arg);
				break;
			case __PA_NOARG:
				continue;
		}
		++p;
	}
#endif

	/* You should modify the run-time binary to let the `PA_DOUBLE'
	 * branch execute the code in the `(PA_INT|PA_FLAG_LONG_LONG)'
	 * branch. Comparing to the original `PA_DOUBLE' branch, the
	 * target branch will also prepare a 64-bit argument, without
	 * introducing floating point instructions. When this function
	 * returns, the action of the code above should do the following:
	 */

#if 0
	while (i < ppfs->num_data_args) {
		switch(ppfs->argtype[i++]) {
			case (PA_INT|PA_FLAG_LONG_LONG):
			here:
				GET_VA_ARG(p,ull,unsigned long long,ppfs->arg);
				break;
			// ......
				/* PA_FLOAT */
			case PA_DOUBLE:
				goto here;
				GET_VA_ARG(p,d,double,ppfs->arg);
				break;
			// ......
		}
		++p;
	}
#endif

}

void init_FLOAT_vfprintf() {
	modify_vfprintf();
	modify_ppfs_setargs();
}
