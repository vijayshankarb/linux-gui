#include "windows.h"
#include "button.h"
#define SPACING 12


static void drawbox( int pos_y,  int pos_x, int y_len, int x_len );
Buttonstruct* createbutton(int attr, int num, char** ptr)
    {
    Buttonstruct* p;
    p = (Buttonstruct*) malloc(sizeof(Buttonstruct));

    p->attr = attr;
    p->todisplay = ptr;
    p->no_todisplay = num;
    return p;
    }

void addbutton(Winstruct* thiswindow, Buttonstruct* comp, int left_y, int left_x)
    {
    store_pert_info(thiswindow, comp, (accepttype)acceptbutton, 
         (displaytype)displaybutton, left_y, left_x);
    }

void displaybutton(Buttonstruct* thislbar, int left_y, int left_x)
    {
  int index;
 
 /* find  the  maximum   string       length     */
  thislbar->state.index = 0;
  thislbar->state.position = left_x; 

  thislbar->maxl = strlen(thislbar->todisplay[0]);
  for(index = 1; index < thislbar->no_todisplay; index++)
    if (strlen(thislbar->todisplay[index]) > thislbar->maxl)
	thislbar->maxl = strlen(thislbar->todisplay[index]);

  drawbox(left_y - 1, left_x - 1, 1, thislbar->maxl); 
  wattrset(Present->win, thislbar->attr);
  mvwaddstr(Present->win, left_y, left_x, thislbar->todisplay[0]);
  wattroff(Present ->win, thislbar->attr);

  for(index = 1; index < thislbar->no_todisplay; index++)
      { drawbox(left_y - 1, left_x + index * SPACING -1, 1, 
                                        thislbar->maxl);
        mvwaddstr(Present -> win, left_y, left_x + index*SPACING,
               thislbar->todisplay[index]);
      }
    }

Buttonretval* acceptbutton(Buttonstruct* thislbar,
                                int left_y , int left_x)
{
    int index = thislbar->state.index, xpos = thislbar->state.position;
    int tpos, temp; 
    Buttonretval val ;
    chtype ch = 0;
    val = index;

    wmove(Present->win, left_y, left_x);
    curs_set(0);

    while((ch = input_key) != 10)
      {
      switch(ch)
	{
	case KEY_LEFT :
	temp = index;
	tpos = xpos ;
        if(index == 0) 
	    {
	    index = thislbar->no_todisplay - 1;
            xpos = left_x + (thislbar->no_todisplay - 1) * SPACING;
	    } 
        else
	   {
	   index--;
           xpos -= SPACING ;
	   }
	   val = index;
           wattroff(Present->win, thislbar->attr);
           mvwaddstr(Present->win, left_y, tpos, 
                                 thislbar->todisplay[temp]);
           wattrset(Present->win, thislbar->attr);
           mvwaddstr(Present->win, left_y,xpos,
                                 thislbar->todisplay[index]);
           wrefresh(Present->win);     
           break;

	case KEY_RIGHT:
	temp = index;
	tpos = xpos ;
        if(index == thislbar->no_todisplay - 1) 
	    {
	    index = 0;
	    xpos = left_x;
	    } 
        else
	   {
	   index++;
	   xpos += SPACING;
	   }
	    val = index;
            wattroff(Present->win, thislbar->attr);
            mvwaddstr(Present->win, left_y, tpos, 
                                 thislbar->todisplay[temp]);
            wattrset(Present->win, thislbar->attr);
            mvwaddstr(Present->win, left_y,
                                 xpos, thislbar->todisplay[index]);
            wrefresh(Present->win); 
	    break;
       }
     }
	  thislbar->state.index = index;
	  thislbar->state.position = xpos;

          val = val + 1;  /* update val to reflect the 0 
                            start of C array indices */ 
	  return &val;
}


void drawbox( int pos_y,  int pos_x, int y_len, int x_len )
    {
     WINDOW* win = Present->win;
     wmove(win, pos_y, pos_x);
     waddch(win, ACS_ULCORNER);

     whline(win, ACS_HLINE, x_len);

     wmove(win, pos_y, pos_x + x_len + 1);
     waddch(win, ACS_URCORNER);

     wmove(win, pos_y + 1, pos_x);
     wvline(win, ACS_VLINE, y_len);

     wmove(win, pos_y + 1, pos_x + x_len + 1);
     wvline(win, ACS_VLINE, y_len);

     wmove(win, pos_y + y_len + 1, pos_x);
     waddch(win, ACS_LLCORNER);

     whline(win, ACS_HLINE, x_len);

     wmove(win, pos_y + y_len + 1, pos_x + x_len + 1);
     waddch(win, ACS_LRCORNER);
    }
