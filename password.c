#include "windows.h"
#include "password.h"

static  Passwordretval* getmem(int size);

Passwordstruct* createpassword( int attr, char* ptr, int size )
    {
    Passwordstruct* p;
    p = ( Passwordstruct* ) malloc( sizeof(Passwordstruct) );

    p->attr = attr;
    p->todisplay = ptr;
    p->size = size;
    return p;
    }

void addpassword( Winstruct* thiswindow, 
                   Passwordstruct* comp, int left_y,
		  int left_x )
    {
  store_pert_info( thiswindow, comp, (accepttype)acceptpassword, 
                   (displaytype)displaypassword, left_y, left_x );
}

void displaypassword( Passwordstruct* thispword, int left_y, int left_x )
    {
     int len = strlen( thispword->todisplay );
     
     wattrset( Present->win, thispword->attr );
     mvwaddstr( Present->win, left_y, left_x, thispword->todisplay );
     wattroff( Present->win, thispword->attr ); 

	drawbox( left_y - 1, left_x + len + 2, 1, thispword->size + 2 );
    }

Passwordretval* acceptpassword( Passwordstruct* thispword,
				int left_y , int left_x )
    {
    int index = 0;
    char *node;
    chtype ch = 0;
    int len = strlen( thispword->todisplay );

    curs_set( 1 );
    wmove( Present->win, left_y , left_x + len + 4 );
    node = getmem( thispword->size );

    while( (ch = input_key) != 10)
	   {
	   if( index == thispword->size )
	  {
	  while(( ch != 10 ) && ( ch != 8 ))
		ch = input_key;
	  }
	  if(ch == 10)
	   break;
	   switch( ch )
	    {
	 case KEY_BACKSPACE:
	 if( index > 0 )
	 index--;
	 wmove( Present->win, left_y, left_x + len + 4 +index );
	 waddch( Present->win, ' ' );
	 wmove( Present->win, left_y, left_x + len + 4 +index );
	 node[index] = '\0';
	 break;

	 default:
	 if( isprint(ch) )
	  {
	  node[index++] = ch;
	  waddch( Present->win,  '*' );
		 }
	    }
	  }
    node[index] = '\0';
    return node;
    }

Passwordretval* getmem(int size)
{
Passwordretval* p;
p = ( Passwordretval* ) malloc ( size*sizeof(char));
return p;
}
