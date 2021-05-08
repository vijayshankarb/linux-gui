#ifndef _WINDOWS_H
#define _WINDOWS_H

#include <curses.h>


#define true 1
#define false 0
#define MAXOBJECTS 10
#define MAXWINDOWS 10
#define input_key wgetch(Present->win)

typedef void* (*accepttype)(void*, int, int);
typedef void  (*displaytype)(void*, int, int);

typedef struct Winstruct
{

    WINDOW* win; /* the curses window */
    int Vline; /* vertical line used to create the border */
    int Hline;  /* horizontal line used to create the border */
    int no_objects;  /* no of objects in the window at any point of time */
    int active; /* indicates whether the window is active or not */
    int left_y, left_x, right_y, right_x; /* window's coordintates */

    /* object holder */
    struct 
    {
    int left_y;
    int left_x;
    void* object;
    accepttype accept;
    displaytype display;
    } holder[MAXOBJECTS];

} Winstruct;

/* declare globally accessable window*/

#if !defined( WINDOWS )
extern Winstruct* Present;
#endif

/* function prototypes */

void initialise(void);
void activate(Winstruct*);
void closeall(void);
Winstruct* getnewwindow(int, int, int, int, int, int);
void* acceptobject(void*);
void store_pert_info(Winstruct*, void*, accepttype p, displaytype q, int, int)
;

#endif
