#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;
    char* expr;
    int prevalue;
	/* TODO: Add more members if necessary */


} WP;


WP* new_wp();

void free_wp(WP*);

void print_wp();

WP* find_wp_byNO(int);
#endif
