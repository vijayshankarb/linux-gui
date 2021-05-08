#include "windows.h"
#include "menubar.h"

Menubarstruct* createmenubar( int attr, int num, char** ptr) 
    {
    Menubarstruct* m;
    m = ( Menubarstruct* ) malloc( sizeof(Menubarstruct) );

    m->attr = attr;
    m->todisplay = ptr;
    m->no_todisplay = num;
    m->pd = (Pulldownstruct **)malloc(num * sizeof(Pulldownstruct *));	
    return m;
    }

void addmenubar( Winstruct* thiswindow, Menubarstruct* comp, int left_y,
                 int left_x )
{
  store_pert_info( thiswindow, comp, (accepttype)acceptmenubar, 
             (displaytype)displaymenubar, left_y, left_x );
  comp->state.index = 0;
  comp->state.position = left_x; 
}


Pulldownstruct *getpulldown(int attribute, char **dispstr, int num,
	int lefty, int leftx, int righty, int rightx)
{
   Pulldownstruct *pds;
   pds = (Pulldownstruct *)malloc(sizeof(Pulldownstruct));
   pds->attr = attribute;
   pds->todisplay = dispstr;
   pds->no_todisplay = num;
   pds->left_y = lefty;
   pds->left_x = leftx;
   pds->right_y = righty;
   pds->right_x = rightx;
   pds->state.index = 0;
   pds->state.position = lefty+2;

   return pds;
}

void displaymenubar( Menubarstruct* thismenubar, int left_y, 
							int left_x )
{
  int index;
  wattrset( Present->win, thismenubar->attr );
  mvwaddstr( Present->win, left_y, left_x, thismenubar->todisplay[0] );
  wattroff( Present ->win, thismenubar->attr );

  for( index = 1; index < thismenubar->no_todisplay; index++ )
     mvwaddstr( Present->win, left_y, left_x + index*9, 
     thismenubar->todisplay[index] );
  
  wrefresh(Present->win);
}



Menubarretval* acceptmenubar( Menubarstruct* thismenubar,
				int left_y , int left_x )
{
    Winstruct *tmp;
    char *tmpfile = "tmp$0"; 
    int index = thismenubar->state.index, 
				xpos = thismenubar->state.position;
    int tpos, temp, pdactive=FALSE; 
    Menubarretval *val ;
    chtype ch = 0, ret2 = (chtype)-1;

    val = (Menubarretval *)malloc(sizeof(Menubarretval));
    val->ret1 = index;

    wmove( Present->win, left_y, left_x );
    slk_init(1);	
    curs_set( 0 );

      while (TRUE)  
      {
      switch( ch )
	{
	case KEY_LEFT :
	temp = index;
        tpos = xpos ;
	if( index == 0 ) 
	    {
	    index = thismenubar->no_todisplay - 1;
	    xpos = left_x + ( thismenubar->no_todisplay - 1 ) * 9;
	    } 
        else
	   {
	   index--;
	   xpos -= 9;
	   }
	   val->ret1 = index;
	   wattroff( Present->win, thismenubar->attr );
	   mvwaddstr( Present->win, left_y, tpos, 
	   			 thismenubar->todisplay[temp] );
	   wattrset( Present->win, thismenubar->attr );
	   mvwaddstr( Present->win, left_y,
	   			 xpos, thismenubar->todisplay[index] );
           wrefresh( Present->win );		
	   if (pdactive)
		ch = ENTER;
           break;

	case KEY_RIGHT :
	temp = index;
	tpos = xpos ;
	if( index == thismenubar->no_todisplay - 1 ) 
	    {
	    index = 0;
	    xpos = left_x;
	    } 
        else
	   {
	   index++;
	   xpos += 9;
	   }
	    val->ret1 = index;
	    wattroff( Present->win, thismenubar->attr );
	    mvwaddstr( Present->win, left_y, tpos,
	   			 thismenubar->todisplay[temp] );
	    wattrset( Present->win, thismenubar->attr );
	    mvwaddstr( Present->win, left_y,
	   			 xpos, thismenubar->todisplay[index] );
	    wrefresh( Present->win );	
	    if (pdactive)
		ch = ENTER;
	    break;

	case ENTER : 
	    scr_dump(tmpfile);
	    ret2 = acceptpulldown(thismenubar->pd[index]);
	    scr_restore(tmpfile);
	    wrefresh(Present->win);
	    pdactive = FALSE;
	    break; 

	case ESC :
	    if (!pdactive)
	    {
	         val->ret1 = val->ret2 = 0;
	         return val;
	    }
	    else
		 ret2 = (chtype)-1;
	    break;

       }

       if ( ret2 >= 0 && ret2 <= 
		    ((thismenubar->pd)[index])->no_todisplay ) 
       {	
		thismenubar->state.index = index;
	  	thismenubar->state.position = xpos;
		val->ret1++;
		val->ret2 = (int)++ret2;
		return val;
       }		
       else if (( ret2 == KEY_LEFT || ret2 == KEY_RIGHT || ret2 == ESC) 								 && !pdactive )
       {
		ch = ret2;
		pdactive = TRUE;
       }		
       else if (ret2 == (chtype)-1)
       {
		ch = input_key;
		pdactive = FALSE;
       }


     }

 }




chtype acceptpulldown(Pulldownstruct *pdm)
{
    int index = pdm->state.index, ypos; 
    int tpos, temp, xp=2, yp=2; 
    chtype ch = 0, ret1 = index;

	WINDOW *pdwin;
	ypos = index + yp;
	pdwin = newwin((pdm->right_y - pdm->left_y + 1), 
		(pdm->right_x - pdm->left_x + 1), pdm->left_y,
		pdm->left_x);

	keypad(pdwin, TRUE);
	box(pdwin, ACS_VLINE, ACS_HLINE);
	wrefresh(pdwin);
	displaypulldown(pdwin, pdm);
				
    wmove( pdwin, ypos, xp );
    slk_init(1);	
    curs_set( 0 );

      while (TRUE)  
      {
      	
      switch( (ch = wgetch(pdwin)) )
	{
	case KEY_UP :
	temp = index;
	tpos = ypos ;
	if( index == 0 ) 
	    {
	    index = pdm->no_todisplay - 1;
	    ypos = yp + pdm->no_todisplay - 1;
	    } 
        else
	   {
	   index--;
	   ypos -= 1;
	   }
	   ret1 = index;
	   wattroff( pdwin, pdm->attr );
	   mvwaddstr( pdwin, tpos, xp,
	   			 pdm->todisplay[temp] );
	   wattrset( pdwin, pdm->attr );
	   mvwaddstr( pdwin, ypos,
	   			 xp, pdm->todisplay[index] );
           wrefresh( pdwin );		
	   break;

	case KEY_DOWN :
	temp = index;
	tpos = ypos ;
	if( index == pdm->no_todisplay - 1 ) 
	    {
	    index = 0;
	    ypos = yp;
	    } 
        else
	   {
	   index++;
	   ypos += 1;
	   }
	    ret1 = index;
	    wattroff( pdwin, pdm->attr );
	    mvwaddstr( pdwin, tpos, xp,
	   			 pdm->todisplay[temp] );
	    wattrset( pdwin, pdm->attr );
	    mvwaddstr( pdwin, ypos, xp, pdm->todisplay[index] );
	    wrefresh( pdwin );	
	    break;

	case ENTER : 
 	    return ret1;
	    break;		
	
	case KEY_LEFT :
	case KEY_RIGHT :
	case ESC :
	    return ch;
	    break;
	}
    }	


}

void displaypulldown(WINDOW *pwin, Pulldownstruct *ps)
{
       
  int index;
  int xp = 2, yp = 2;
  wattrset( pwin, ps->attr );
  mvwaddstr(pwin, yp, xp, ps->todisplay[0]);
  wattroff( pwin, ps->attr );
  wrefresh(pwin);


  for( index = 1; index < ps->no_todisplay; index++ )
     mvwaddstr( pwin, yp + index, xp, 
     ps->todisplay[index] );
     wrefresh(pwin);
}
