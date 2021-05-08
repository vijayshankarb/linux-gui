#define WINDOWS

#include "windows.h"
#include <setjmp.h>
#include <assert.h>

/* the present window declared as global for the entire program */

Winstruct* Present;

/* declarations required for storing the 
            active window info onto the stack */

static char* flname[] = { 
			"temp$$1", "temp$$2", "temp$$3", "temp$$4"
			"temp$$5", "temp$$6", "temp$$7", "temp$$8"
			"temp$$9", "temp$$10" };

struct stack_tag { 
Winstruct* store;
int fileindex;
} *Winstack ;

static int stackindex = 0;

/* end of stack declarations */
 
jmp_buf error_buf;  /*  exception handler  */

void initialise( void )
    {
    static int INIT = false;
    int error, index;

    if( !INIT )
	{
	INIT = true;
	initscr( );
        cbreak( );
	noecho( );
       
	Present = NULL;
	Winstack = ( struct stack_tag* )
             	      malloc( MAXWINDOWS * sizeof( struct stack_tag ) );

        for( index = 0; index < MAXWINDOWS; index++ )
             Winstack[index].fileindex = index;

	if( ( error = setjmp( error_buf ) ) )
	    {
	    endwin( );
	    printf(" exception encountered %d", error );
	    exit( error );
	    }
	}
    }

void closeall( void )
    {
    /* actually unstack all the windows and  clear them */

    wclear( Present->win );
    wrefresh( Present->win );
    endwin( );
    }

void activate( Winstruct* p )
    {
    int index;
    /* push the present window onto the stack */
    if( p->active ) longjmp( error_buf, 4 );


    if( Present != NULL )
	{
	if( stackindex < MAXWINDOWS )
	    {
	    Winstack[stackindex].store = Present;
	    scr_dump( flname[Winstack[stackindex].fileindex] );
	    stackindex++;
	    }
	else
	   longjmp( error_buf, 1 );
	}

    Present = p;
    Present->active = true;

    box( Present->win, Present->Vline, Present->Hline );

    for( index = 0; index < Present->no_objects; index++ )
          Present->holder[index].display( Present->holder[index].object, 
	   Present->holder[index].left_y, 
	          Present->holder[index].left_x );

    wrefresh( Present->win );
    }

void deactivate( void )
    {
    if( stackindex == 0 )
	longjmp( error_buf, 2 );
    --stackindex;
    Present->active = false;
    wclear( Present->win );
    wrefresh( Present->win );
    Present = Winstack[stackindex].store;

    scr_restore( flname[Winstack[stackindex].fileindex] );
    }
	
Winstruct* getnewwindow(int left_y, int left_x, 
                        int right_y, int right_x,
			int Vl, int Hl )
    {
    Winstruct* p;
    p = ( Winstruct* )malloc( sizeof( Winstruct ) );
    p->no_objects = 0;
    p->win = newwin( right_y - left_y + 1, right_x - left_x + 1, 
                     left_y, left_x );
                    
    p->Vline = Vl;
    p->Hline = Hl;
    p->left_y = left_y;
    p->left_x = left_x;
    p->right_y = right_y;
    p->right_x = right_x;
    keypad( p->win, true );
    return p;
    }

void* acceptobject( void* thisobject )
    {
    int index;
    void* retval;

    for( index = 0; index < Present->no_objects; index++ )
	if( thisobject == ( Present->holder[index] ).object )
	    break;

    if( index != Present->no_objects )
         retval = ( void* )Present->holder[index].accept(
          thisobject, 
	   Present->holder[index].left_y, 
	          Present->holder[index].left_x );
    else
	longjmp( error_buf, 3 );
    return retval;
    }

void pause( void )
    {
    wgetch( Present->win );
    }

void store_pert_info( Winstruct* thiswindow, void* comp, void* (*accept)		( void*, int, int), void (*display)(void*, int, int), 
			 int left_y, int left_x )
  {
  ( thiswindow->holder[thiswindow->no_objects] ).left_y = left_y; 
  ( thiswindow->holder[thiswindow->no_objects] ).left_x = left_x; 
  ( thiswindow->holder[thiswindow->no_objects] ).object = comp;
  ( thiswindow->holder[thiswindow->no_objects] ).accept = accept;
  ( thiswindow->holder[thiswindow->no_objects] ).display = display;

  thiswindow->no_objects++;
  }
