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
    wptr->next=head;
    head=wptr;
    wptr->expr=args;
    return wptr;
}


void free_wp(WP *wp){
    if(wp==NULL)panic("wp is NULL");
    WP* ip;
    if(head->NO==wp->NO)head=head->next;
    else{
        for(ip=head;ip->next!=NULL;ip=ip->next){
            if(ip->next->NO==wp->NO){
                ip->next=ip->next->next;
            }
        }
    }
    wp->next=free_;
    free_=wp;

}
/*
void write_wp(WP* wp,char *args){
    strcpy(wp->expr,args);
}
*/
void print_wp(){
    printf("%-20s","wpNO");
    printf("%-20s","wpEXPR");
    printf("%-20s","wpVAL");
    printf("\n");
    WP* wp;
    
    for(wp=head;wp!=NULL;wp=wp->next){
        //bool success=true;
        //int val=expr(wp->expr,&success);
        printf("%-20d",wp->NO);
        printf("%-20s",wp->expr);
        printf("%-20d",wp->originvalue);
        printf("\n");
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



bool check_wp(){
    WP* wp;
    for(wp=head;wp!=NULL;wp=wp->next){
        bool success=true;
        int val=expr(wp->expr,&success);
        if(val!=wp->originvalue)return false;
    }
    return true;
}
