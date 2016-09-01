#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

enum {
	NOTYPE = 256,EQ

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
	{"\\+", '+'},					// plus
    {"-", '-'},                     // minus
    {"\\*", '*'},                   // multiply
    {"/", '/'},                     // divide
    {"\\(", '('},                   // left bracket
    {"\\)", ')'},                   // right bracket
    {"[0-9]+", 'n'}                 // number
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

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */
                

				switch(rules[i].token_type) {
                    case '+': tokens[nr_token].type='+';tokens[nr_token].str[0]='+';nr_token++;break;
                    case '-': tokens[nr_token].type='-';tokens[nr_token].str[0]='-';nr_token++;break;
                    case '*': tokens[nr_token].type='*';tokens[nr_token].str[0]='*';nr_token++;break;
                    case '/': tokens[nr_token].type='/';tokens[nr_token].str[0]='/';nr_token++;break;
                    case '(': tokens[nr_token].type='(';tokens[nr_token].str[0]='(';nr_token++;break;
                    case ')': tokens[nr_token].type=')';tokens[nr_token].str[0]=')';nr_token++;break;
                    case 'n':{
                        tokens[nr_token].type='n';
                        strncpy(tokens[nr_token].str,substr_start,substr_len);
                        nr_token++;
                        break;
                    }
                    case NOTYPE:break;
                    case EQ:break;
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


bool check_parentheses(int p,int q){
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


int find_dominant_operator(int p,int q){
    int i;
    int qend;
    int qleft,qright;
    qleft=qright=0;
    
    /*
    for(i=p;i<=q;i++)
    {
        if(tokens[i].type=='(')pleft++;
        else if(tokens[i].type==')')pright++;
        
        if(pleft==pright){
             pend=(pleft==0)?i:i+1;
        }
    }
    */
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
            if(tokens[i].type=='*'||tokens[i].type=='/')return i;
            else if(tokens[i].type==')')break;
        }

        qend=i;
    }while(i>p);
    
    qleft=qright=0;
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
            if(tokens[i].type=='+'||tokens[i].type=='-')return i;
            else if(tokens[i].type==')')break;
        }
    }while(i>p);
    
    return -1;
}


int eval(int p,int q){
    if(p>q){
        panic("tokens index error");
    }
    else if(p==q){
        if(tokens[p].type=='n'){
            int val=atoi(tokens[p].str);
            return val;
        }
        else panic("this is not a number");
    }
    else if(check_parentheses(p,q)==true){
        return eval(p+1,q-1);
    }
    else{
        int index=find_dominant_operator(p,q);
        if(index==-1)panic("fail to find the dominant operator");
        char op=tokens[index].str[0];
        int val1=eval(p,index-1);
        int val2=eval(index+1,q);
        switch(op){
            case '+':return val1+val2;
            case '-':return val1-val2;
            case '*':return val1*val2;
            case '/':return val1/val2;
            default:assert(0);
        }
    }
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
    printf("nr_token is %d\n",nr_token); 
    int i;
    for(i=0;i<nr_token;i++){
        printf("tokens[%d].type==%c\n",i,tokens[i].type);
        printf("tokens[%d].str==%s\n",i,tokens[i].str);
    }
    
	/* TODO: Insert codes to evaluate the expression. */
	//panic("please implement me");
    
    return eval(0,nr_token-1);
}

