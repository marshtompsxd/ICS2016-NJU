#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

bool find_obj_in_elf(const char* , uint32_t * );


enum {
	NOTYPE = 256,EQ,NEQ,AND,OR,NOT,DEREF,NEG,ELFOBJ

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"==", EQ},						// equal
    {"!=",NEQ},                     // not equal
    {"&&",AND},                     // and
    {"\\|\\|",OR},                  // or
    {"!",NOT},                      // not
    {"\\$[a-z]+", 'r'},             // register
	{"\\+", '+'},					// plus
    {"-", '-'},                     // minus
    {"\\*", '*'},                   // multiply
    {"/", '/'},                     // divide
    {"\\(", '('},                   // left bracket
    {"\\)", ')'},                   // right bracket
    {"0x[0-9a-f]+",'h'},            // hexadecimal number
    {"[0-9]+", 'd'},                // decimal number
    {"[_a-zA-Z0-9]+",ELFOBJ}        // object in elf
}; 

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				//Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */
                

				switch(rules[i].token_type) {
                    case '+': 
                    case '-': 
                    case '*': 
                    case '/': 
                    case EQ: 
                    case NEQ: 
                    case OR: 
                    case AND: 
                    case NOT:
                    case ELFOBJ: 
                    case '(': 
                    case ')':
                    case 'r':
                    case 'd':
                    case 'h':{
                        tokens[nr_token].type=rules[i].token_type;
                        if(substr_len>32)panic("over 32 characters");
                        strncpy(tokens[nr_token].str,substr_start,substr_len);
                        nr_token++;
                        break;
                    }
                    case NOTYPE:break;
					default: panic("please implement me");
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}


static bool check_match(int p,int q){
    int i;
    int leftNum=0;
    int rightNum=0;
    for(i=p;i<=q;i++){

        if(tokens[i].type=='(')leftNum++;
        else if(tokens[i].type==')')rightNum++;

        if(leftNum<rightNum)return false;
    }
    if(leftNum==rightNum)return true;
    else return false;
}

static bool check_parentheses(int p,int q){
    int i;
    if(tokens[p].type!='('||tokens[q].type!=')'){
        return false;
    }
    int leftNum=0;
    int rightNum=0;
    for(i=p;i<=q;i++){

        if(tokens[i].type=='(')leftNum++;
        else if(tokens[i].type==')')rightNum++;

        if(leftNum<rightNum)return false;
        else if(leftNum==rightNum&&i<q)return false;
    }
    if(leftNum==rightNum)return true;
    else return false;
}


static int find_dominant_operator(int p,int q){
    int i;
    int qend;
    int qleft,qright;
    qleft=qright=0;
    int plus_in,minus_in,mult_in,divide_in,equal_in,notequal_in,and_in,or_in,not_in,deref_in,neg_in;
    plus_in=minus_in=mult_in=divide_in=equal_in=notequal_in=and_in=or_in=not_in=deref_in=neg_in=-1;
    
    qend=q;
    do{

        for(i=qend;i>=p;i--){
            if(tokens[i].type=='(')qleft++;
            else if(tokens[i].type==')')qright++;
        
            if(qleft==qright){
                qend=(qleft==0)?i:i-1;
                break;
            }
        }


        for(i=qend;i>=p;i--){
            if(tokens[i].type=='+'&&plus_in==-1)plus_in=i;
            else if(tokens[i].type=='-'&&minus_in==-1)minus_in=i;
            else if(tokens[i].type=='*'&&mult_in==-1)mult_in=i;
            else if(tokens[i].type=='/'&&divide_in==-1)divide_in=i;
            else if(tokens[i].type==EQ&&equal_in==-1)equal_in=i;
            else if(tokens[i].type==NEQ&&notequal_in==-1)notequal_in=i;
            else if(tokens[i].type==AND&&and_in==-1)and_in=i;
            else if(tokens[i].type==OR&&or_in==-1)or_in=i;
            else if(tokens[i].type==NOT&&not_in==-1)not_in=i;
            else if(tokens[i].type==DEREF&&deref_in==-1)deref_in=i;
            else if(tokens[i].type==NEG&&neg_in==-1)neg_in=i;
            else if(tokens[i].type==')')break;
        }

        qend=i;
    }while(i>p);


    if(or_in!=-1)return or_in;
    else if(and_in!=-1)return and_in;
    else if(equal_in!=-1||notequal_in!=-1)return (equal_in>notequal_in)?equal_in:notequal_in;
    else if(plus_in!=-1||minus_in!=-1)return (plus_in>minus_in)?plus_in:minus_in;
    else if(mult_in!=-1||divide_in!=-1)return (mult_in>divide_in)?mult_in:divide_in;
    else if(not_in!=-1||deref_in!=-1||neg_in!=-1){
        if(not_in>deref_in&&not_in>neg_in)return not_in;
        else if(deref_in>not_in&&deref_in>neg_in)return deref_in;
        else return neg_in;
    }


    
    return -1;
}


static int eval(int p,int q,bool* success){
    if(!(*success)){
        return -1;
    }
    if(p>q){
        printf("tokens index error\n");
        *success=false;
        return -1;
    }
    else if(p==q){
        if(tokens[p].type=='d'){
            int val=atoi(tokens[p].str);
            //printf("val is %d\n",val);
            return val;
        }
        else if(tokens[p].type=='h'){
            char *str;
            int val=strtol(tokens[p].str,&str,16);
            //printf("val is %x(or we can say %d)",val,val);
            return val;
        }
        else if(tokens[p].type=='r'){
            int val;
            if(!strcmp("$eax",tokens[p].str))val=cpu.eax;
            else if(!strcmp("$ecx",tokens[p].str))val=cpu.ecx;
            else if(!strcmp("$edx",tokens[p].str))val=cpu.edx;
            else if(!strcmp("$ebx",tokens[p].str))val=cpu.ebx;
            else if(!strcmp("$esp",tokens[p].str))val=cpu.esp;
            else if(!strcmp("$ebp",tokens[p].str))val=cpu.ebp;
            else if(!strcmp("$esi",tokens[p].str))val=cpu.esi;
            else if(!strcmp("$edi",tokens[p].str))val=cpu.edi;
            else panic("register name error");
            //printf("val is %d\n",val);
            return val;
        }
        else if(tokens[p].type==ELFOBJ){
            uint32_t addr;
            bool findit=find_obj_in_elf(tokens[p].str,&addr);
            if(findit)
                return addr;
            else{
                printf("no such odj in elf\n");
                *success=false;
                return -1;
            }
        }
        else {
            printf("it is not a number\n");
            *success=false;
            return -1;
        }
    }
    else if(check_parentheses(p,q)==true){
        int val=eval(p+1,q-1,success);
        if(!(*success)){
            return -1;
        }

        //printf("val is %d\n",val);

        return val;
    }
    else{
        int index=find_dominant_operator(p,q);
        if(index==-1){
            printf("fail to find the dominant operator\n");
            *success=false;
            return -1;
        }
        
        int op_type=tokens[index].type;
        
        //printf("dominant op is %s\n",op);
        
        if(op_type==DEREF){
            int addr=eval(index+1,q,success);
            if(!(*success)){
                return -1;
            }
            return swaddr_read(addr,4);
        }
        else if(op_type==NEG){
            int val=-1*eval(index+1,q,success);
            if(!(*success)){
                return -1;
            }
            return val;
        }
        else if(op_type==NOT){
            int val=!eval(index+1,q,success);
            if(!(*success)){
                return -1;
            }
            return val;
        }
        else{
            int val1=eval(p,index-1,success);
            if(!(*success)){
                return -1;
            }
            int val2=eval(index+1,q,success);
            if(!(*success)){
                return -1;
            }
            switch(op_type){
                case '+':return val1+val2;
                case '-':return val1-val2;
                case '*':return val1*val2;
                case '/':{
                    if(val2)return val1/val2;
                    else{
                        printf("val2 cannot be 0\n");
                        *success=false;
                        return-1;
                    }
                }
                case EQ:return val1==val2;
                case NEQ:return val1!=val2;
                case OR:return val1||val2;
                case AND:return val1&&val2;
                default:assert(0);

            }
        }
    }
}


static bool is_operator(int index){
    int type=tokens[index].type;
    if(type=='+'||type=='-'||type=='*'||type=='/'||type==EQ||type==NEQ||type==OR||type==AND||type==NOT||type==DEREF||type==NEG){
        return true;
    }
    else return false;
}



uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}



    int i;
    for(i=0;i<nr_token;i++){
        if(tokens[i].type=='*'&&(i==0||is_operator(i-1))){
            tokens[i].type=DEREF;
        }
    }
    

    for(i=0;i<nr_token;i++){
        if(tokens[i].type=='-'&&(i==0||is_operator(i-1))){
            tokens[i].type=NEG;
        }
    }

    if(!check_match(0,nr_token-1)){
        printf("bracket match error\n");
        *success=false;
        return 0;
    }

    //printf("nr_token is %d\n",nr_token); 
    
    /*
    for(i=0;i<nr_token;i++){
        printf("tokens[%d].type==%c\n",i,tokens[i].type);
        printf("tokens[%d].str==%s\n",i,tokens[i].str);
    }
    */

	/* TODO: Insert codes to evaluate the expression. */
	//panic("please implement me");
    
    return eval(0,nr_token-1,success);
}

