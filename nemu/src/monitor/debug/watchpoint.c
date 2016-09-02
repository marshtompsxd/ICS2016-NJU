#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
        wp_pool[i].in_use=false;
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */


WP* new_wp(char *args){
    if(free_==NULL)panic("free is NULL");
    
    WP *wptr=free_;
    free_=free_->next;
    if(head){
        wptr->next=head;
    }
    else{
        wptr->next=NULL;
    }
    head=wptr;
    strcpy(wptr->expr,args);
    bool success=true;
    int val=expr(wptr->expr,&success);
    if(!success){
        free_wp(wptr);
        return NULL;
    }
    wptr->originvalue=val;
    wptr->in_use=true;
    return wptr;
}


void free_wp(WP *wp){
    printf("free a wp\n");
    if(wp==NULL)panic("wp is NULL");
    WP* ip;
    if(head->NO==wp->NO)
    {
        head=head->next;
        printf("head change\n");
    }
    else{
        for(ip=head;ip->next!=NULL;ip=ip->next){
            printf("now ip is NO %d\n",ip->NO );
            if(ip->next->NO==wp->NO){
                ip->next=ip->next->next;
            }
        }
    }
    printf("find the wp\n");
    wp->next=free_;
    free_=wp;
    wp->in_use=false;

}



void print_wp(){
    printf("%-20s","wpNO");
    printf("%-20s","wpEXPR");
    printf("%-20s","wpVAL");
    printf("\n");
    int i;
    
    for(i=0;i<NR_WP;i++){
        if(wp_pool[i].in_use){
            printf("%-20d",wp_pool[i].NO);
            printf("%-20s",wp_pool[i].expr);
            printf("%-20d",wp_pool[i].originvalue);
            printf("\n");
            
        }
    }
}    



WP* find_wp_byNO(int NO){
    WP* wp;
    for(wp=head;wp!=NULL;wp=wp->next){
        if(wp->NO==NO){
            return wp;
        }
    }
    return NULL;
}



WP* check_wp(){
    WP* wp;
    for(wp=head;wp!=NULL;wp=wp->next){
        bool success=true;
        int val=expr(wp->expr,&success);
        if(val!=wp->originvalue)return wp;
    }
    return NULL;
}
