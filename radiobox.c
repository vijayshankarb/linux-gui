#include "windows.h"
#include "radiobox.h"
#define  BRACKET "( )" 
#define BRACKETWO "(o)"
#define BRACKETP  2

static int maxl;

Radioboxstruct* createradiobox( int attr, int num, char** ptr )
    {
    Radioboxstruct* p;
    p = (Radioboxstruct* ) malloc( sizeof(Radioboxstruct) );

    p->attr = attr;
    p->todisplay = ptr;
    p->no_todisplay = num;
    return p;
    }

void addradiobox( Winstruct* thiswindow, 
                  Radioboxstruct* comp, int left_y,
		  int left_x )
{
  store_pert_info( thiswindow, comp, (accepttype)acceptradiobox, 
                   (displaytype)displayradiobox, left_y, left_x );
}

   
void displayradiobox( Radioboxstruct* thisrbar, int left_y, int left_x )
    {
    int index, i;

    thisrbar->state.index = 0;
    thisrbar->state.position = left_y; 
    mvwaddstr( Present->win, left_y, left_x, thisrbar->todisplay[0] );

    maxl = strlen(thisrbar -> todisplay[0]); 
    for (i=1 ; i < thisrbar -> no_todisplay ; ++i)
        {   
	if(strlen(thisrbar -> todisplay[i]) > maxl )
		maxl = strlen(thisrbar -> todisplay[i]);
        }

   mvwaddstr(Present->win, left_y, left_x + maxl + BRACKETP, BRACKETWO);

  for( index = 1; index < thisrbar->no_todisplay; index++ )
     mvwaddstr( Present->win, left_y + index*2, left_x, 
     thisrbar->todisplay[index] );
  
  for( index = 1; index < thisrbar->no_todisplay; index++ )
    mvwaddstr( Present->win, left_y + index*2, left_x + maxl +BRACKETP, 
     BRACKET );
}


Radioboxretval* acceptradiobox( Radioboxstruct* thisrbar,
				int left_y , int left_x )
    {
    int index = thisrbar->state.index, ypos = thisrbar->state.position;
    int tpos, temp;
    int i; 
    Radioboxretval val ;
    chtype ch = 0;
    val = index;

    wmove( Present->win, left_y, left_x + maxl + 3);
    curs_set( 0 );


    while( ( ch = input_key) != 10 )
      {
      switch( ch )
	{
	case KEY_UP :
	temp = index;
	tpos = ypos ;
	if( index == 0 ) 
	    {
	    index = thisrbar->no_todisplay - 1;
	    ypos = left_y + ( thisrbar->no_todisplay - 1 ) * 2;
	    } 
        else
	   {
	   index--;
	   ypos -= 2;
	   }
	   val = index;
	    mvwaddstr( Present->win, tpos, left_x + maxl + BRACKETP,  
	   			 BRACKET );
	   mvwaddstr( Present->win, ypos,
	   			 left_x + maxl + BRACKETP, BRACKETWO );
	   wmove(Present->win, ypos, left_x + maxl + 3);	
           wrefresh( Present->win );		
           break;

	case KEY_DOWN :
	temp = index;
	tpos = ypos ;
	if( index == thisrbar->no_todisplay - 1 ) 
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
	     mvwaddstr( Present->win, tpos, left_x + maxl +BRACKETP, 
						BRACKET);
	    mvwaddstr( Present->win, ypos,
	   			 left_x + maxl + BRACKETP, BRACKETWO );
	    wmove( Present->win, ypos, left_x + maxl + 3 );
	    wrefresh( Present->win );	
	    break;
       }
     }
	  thisrbar->state.index = index;
	  thisrbar->state.position = ypos;

          val = val + 1;  /* update val to reflect the 0 
                            start of C array indices */ 
	  return &val;
 }
