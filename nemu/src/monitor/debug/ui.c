#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

/* We use the `readline' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_si(char *args){
    int stepNum;
    if(args==NULL)
    {
        stepNum=1;
    }
    else
    {
        stepNum=atoi(args);
        if(stepNum)
        {
            int i;
            for(i=0;i<stepNum;i++)
            {
                cpu_exec(1);
            }
        }
    }
    return 0;
}

static int cmd_info(char *args){
    if(!strcmp(args,"r"))
    {
        printf("%-20s","registername");
        printf("%-20s","registercontent");
        printf("\n");
        printf("%-20s","eax");
        printf("%-20x",cpu.eax);
        printf("\n");
        printf("%-20s","ecx");
        printf("%-20x",cpu.ecx);
        printf("\n");
        printf("%-20s","edx");
        printf("%-20x",cpu.edx);
        printf("\n");
        printf("%-20s","ebx");
        printf("%-20x",cpu.ebx);
        printf("\n");
        printf("%-20s","esp");
        printf("%-20x",cpu.esp);
        printf("\n");
        printf("%-20s","ebp");
        printf("%-20x",cpu.ebp);
        printf("\n");
        printf("%-20s","esi");
        printf("%-20x",cpu.esi);
        printf("\n");
        printf("%-20s","edi");
        printf("%-20x",cpu.edi);
        printf("\n");

        
        
    }
    else if(!strcmp(args,"w")){
        
        print_wp();
        
    }

    return 0;
}


static int cmd_p(char *args){
    bool success=true;
    int result=expr(args,&success);
    if(success){
        printf("The result is %d\n",result);
    }
    else{
        printf("fail to evaluate expression\n");
    }
    return 0;
}


static int cmd_x(char *args){
    
    char *cnum=strtok(args," ");
    char *caddr=strtok(NULL," ");
    
    
    int num=atoi(cnum);
    bool success=true;
    int addr=expr(caddr,&success);
    if(!success){
        printf("fail to evaluate expression\n");
    }
    else{
        int i;
        printf("%-20s","memoryaddress");
        printf("%-20s","memorycontent");
        printf("\n");
        for(i=0;i<num;i++){
            uint32_t content=swaddr_read(addr,4);
            printf("%-20x",addr);
            printf("%-20x\n",content);
            addr+=4;
        }
    }
    return 0;
    
}

static int cmd_w(char *args){
    WP* wp=new_wp(args);
    if(wp==NULL){
        panic("fail to set watchpoint\n");
    }
    printf("watchpointNO is %d\n",wp->NO);
    printf("watchpointEXPR is %s\n",wp->expr);
    printf("watchpointVAL is %d\n",wp->originvalue);
    return 0;
}

static int cmd_d(char *args){
    int NO;
    if(!strcmp("0",args)){
        NO=0;
    }
    else{
        NO=atoi(args);
        if(NO==0){
            printf("args error");
            return 0;
        }
    }
    WP *wp=find_wp_byNO(NO);
    if(wp==NULL){
        printf("no such NO\n");
        return 0;
    }
    else{
        free_wp(wp);
        printf("delete watchpoint %d\n",NO);
        return 0;
    }

    
}

static int cmd_help(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
    { "si","After N steps the programe will suspend",cmd_si },
    { "info","Print the statue of programme",cmd_info },
    { "p","Calculate a expression",cmd_p },
    { "x","Scanf the memory",cmd_x },
    { "w","Set a watchpoint",cmd_w },
    { "d","Delete a watchpoint",cmd_d },
	{ "q", "Exit NEMU", cmd_q },

	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
    char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
