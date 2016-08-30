/*************************************************************************
	> File Name: reg.h
	> Author: 
	> Mail: 
	> Created Time: Tue Aug 30 14:37:57 2016
 ************************************************************************/

#ifndef _REG_H
#define _REG_H

struct CPU_stat
{
    union
    {
        int eax;
        short ax;
        struct
        {
            char al;
            char ah;
        }
    }  
    
    union
    {
        int edx;
        short dx;
        struct
        {
            char dl;
            char dh;
        }
    }

    union
    {
        int ecx;
        short cx;
        struct
        {
            char cl;
            char ch;
        }
    }

    union
    {
        int ebx;
        short bx;
        struct
        {
            char bl;
            char bh;
        }
    }

    union
    {
        int ebp;
        short bp;
    }

    union
    {
        int esi;
        short si;
    }

    union
    {
        int edi;
        short si;
    }

    union
    {
        int esp;
        short sp;
    }
}


#endif
