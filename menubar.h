#include <curses.h>

#ifndef _MENUBAR_H
#define _MENUBAR_H 

#define ENTER 10
#define ESC 27

struct Pulldown_tag;
typedef struct Pulldown_tag Pulldownstruct;

typedef struct Menubarstruct_tag 
    {
    int attr;
    char** todisplay;
    int no_todisplay;
    Pulldownstruct **pd; 	
    struct
    {
    int index;
    int position;
    } state;

    } Menubarstruct;


struct Pulldown_tag
    {
	int attr;
	char **todisplay;
	int no_todisplay; 
        int left_y;
	int left_x;
	int right_y;
	int right_x;
	struct
	{
	     int index;
	     int position;
	} state;
    };		

typedef struct
    {
	int ret1;
	int ret2;
    }Menubarretval;

Menubarstruct* createmenubar( int attr, int num, char** ptr);
void addmenubar( Winstruct*, Menubarstruct*, int, int ); 
Pulldownstruct *getpulldown(int attribute, char **dispstr, int num,
	int lefty, int leftx, int righty, int rightx);
Menubarretval* acceptmenubar( Menubarstruct*, int, int );
void displaymenubar( Menubarstruct*, int, int );

chtype acceptpulldown(Pulldownstruct *pd);
void displaypulldown(WINDOW *pwin, Pulldownstruct *ps);

#endif
