#include "windows.h"
#include "textitem.h"
#include <string.h>

Textitemstruct* createtextitem( int attr, char* buffer )
    {
    Textitemstruct* p;
    p = ( Textitemstruct* ) malloc( sizeof(Textitemstruct) );

    p->attr = attr;
    p->todisplay = strdup( buffer );
    return p;
    }

void addtextitem( Winstruct* thiswindow, 
                   Textitemstruct* comp, int left_y,
		  int left_x )
    {
    store_pert_info( thiswindow, comp, (accepttype)accepttextitem, 
                     (displaytype)displaytextitem, left_y, left_x );
    }

void displaytextitem( Textitemstruct* thistitem, 
				  int left_y, int left_x )
    {
    char* ptr;
    int maxchardisp, tempchardisp, ndisp;
    char c;

    wattrset( Present->win, thistitem->attr );
    wmove( Present->win, left_y, left_x );

    ptr = thistitem->todisplay;

    tempchardisp = Present->right_x - left_x - 1;

    maxchardisp = ( Present->right_x - Present->left_x - 1 );
    ndisp = tempchardisp;

    while( ( c = *ptr++ ) )
        {	
	if( c == '\n' || ndisp == 0 )
	    {
            left_y++;
	    left_x = Present->left_x;
	    wmove( Present->win, left_y, left_x );
	    if( c == '\n' )
		continue;
	    ndisp = maxchardisp;
	    }
        waddch( Present->win, c );
	ndisp--;
       }
    wattroff( Present->win, thistitem->attr );
     }

Textitemretval* accepttextitem( Textitemstruct* thistitem,
                                  int left_y, int left_x )
    {
    wgetch( Present->win );
    return (Textitemretval*) NULL;
    }
