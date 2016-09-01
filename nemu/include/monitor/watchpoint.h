#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
    char* expr;
    int originvalue;
	struct watchpoint *next;
	/* TODO: Add more members if necessary */


} WP;


WP* new_wp(char*);

void free_wp(WP*);

void print_wp();

WP* find_wp_byNO(int);

bool check_wp();

void write_wp(WP*,char*);

#endif
