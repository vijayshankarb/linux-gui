#include "windows.h"
#include "lightbar.h"


Lightbarstruct* createlightbar( int attr, int num, char** ptr )
    {
    Lightbarstruct* p;
    p = ( Lightbarstruct* ) malloc( sizeof(Lightbarstruct) );

    p->attr = attr;
    p->todisplay = ptr;
    p->no_todisplay = num;
    return p;
    }

void addlightbar( Winstruct* thiswindow, Lightbarstruct* comp, int left_y,
                  int left_x )
{
    store_pert_info(thiswindow, comp, (accepttype)acceptlightbar, 
                 (displaytype)displaylightbar, left_y, left_x );
}

void displaylightbar( Lightbarstruct* thislbar, int left_y, int left_x )
{
  int index;
  thislbar->state.index = 0;
  thislbar->state.position = left_y; 

  wattrset( Present->win, thislbar->attr );
  mvwaddstr( Present->win, left_y, left_x, thislbar->todisplay[0] );
  wattroff( Present ->win, thislbar->attr );

  for( index = 1; index < thislbar->no_todisplay; index++ )
     mvwaddstr( Present->win, left_y + index*2, left_x, 
     thislbar->todisplay[index] );
}

Lightbarretval* acceptlightbar( Lightbarstruct* thislbar,
				int left_y , int left_x )
    {
    int index = thislbar->state.index, ypos = thislbar->state.position;
    int tpos, temp; 
    Lightbarretval val ;
    chtype ch = 0;
    val = index;

    wmove( Present->win, left_y, left_x );
    curs_set( 0 );

    while( ( ch = input_key ) != 10 )
      {
      switch( ch )
	{
	case KEY_UP :
	temp = index;
	tpos = ypos ;
	if( index == 0 ) 
	    {
	    index = thislbar->no_todisplay - 1;
	    ypos = left_y + ( thislbar->no_todisplay - 1 ) * 2;
	    } 
        else
	   {
	   index--;
	   ypos -= 2;
	   }
	   val = index;
	   wattroff( Present->win, thislbar->attr );
	   mvwaddstr( Present->win, tpos, left_x, 
	   			 thislbar->todisplay[temp] );
	   wattrset( Present->win, thislbar->attr );
	   mvwaddstr( Present->win, ypos,
	   			 left_x, thislbar->todisplay[index] );
           wrefresh( Present->win );		
           break;

	case KEY_DOWN :
	temp = index;
	tpos = ypos ;
	if( index == thislbar->no_todisplay - 1 ) 
	    {
	    index = 0;
	    ypos = left_y;
	    } 
        else
	   {
	   index++;
	   ypos += 2;
	   }
	    val = index;
	    wattroff( Present->win, thislbar->attr );
	    mvwaddstr( Present->win, tpos, left_x, 
	   			 thislbar->todisplay[temp] );
	    wattrset( Present->win, thislbar->attr );
	    mvwaddstr( Present->win, ypos,
	   			 left_x, thislbar->todisplay[index] );
	    wrefresh( Present->win );	
	    break;
       }
     }
	  thislbar->state.index = index;
	  thislbar->state.position = ypos;

          val = val + 1;  /* update val to reflect the 0 
                            start of C array indices */ 
	  return &val;
 }
