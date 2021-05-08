#include "windows.h"
#include "compbox.h"

#define bracket "[   ]"

static Compboxretval* getmem(int size);

Compboxstruct* createcompbox(int attr, int num, char** ptr)
    {
    int index;
    Compboxstruct* p;
    p = (Compboxstruct*) malloc(sizeof(Compboxstruct));

    p->attr = attr;
    p->todisplay = ptr;
    p->no_todisplay = num;
    p->len = strlen(p->todisplay[0]);

    for(index = 1; index < p->no_todisplay; index++)
        if(p->len < strlen(p->todisplay[index]))
           p->len = strlen(p->todisplay[index]);
    return p;
    }

void addcompbox(Winstruct* thiswindow, Compboxstruct* comp,
                int left_y, int left_x)
{
store_pert_info(thiswindow, comp, (accepttype)acceptcompbox, (displaytype)displaycompbox,
                 left_y, left_x);
}

void displaycompbox(Compboxstruct* thiscbox, int left_y, int left_x)
    {
  int index;
  int len = thiscbox->len;
  for(index = 0; index < thiscbox->no_todisplay; index++)
    {
       wattrset(Present->win, thiscbox->attr);
       mvwaddstr(Present->win, left_y+index*2, left_x, 
            thiscbox->todisplay[index]);
       wattroff(Present ->win, thiscbox->attr);
       mvwaddstr(Present->win, left_y+index*2, left_x+len+1, bracket);
    } 
}

Compboxretval* acceptcompbox(Compboxstruct* thiscbox,
                                int left_y , int left_x)
    {
    int *node;
    int len = thiscbox->len;
    int index = 0, ypos = left_y;

    chtype ch = 0;
    int val ;
    char toput[2] = { ' ', 'X' };

    node = getmem(thiscbox->no_todisplay);
    for(val = 0; val < thiscbox->no_todisplay; val++)
        node[val] = 0;
    curs_set(1);   
    wmove(Present->win, left_y, left_x+len+3);

    while ((ch = input_key) != 10)
      {
      switch(ch)
	{
	case KEY_UP :
        if(index == 0) 
	    {
	    index = thiscbox->no_todisplay - 1;
            ypos = left_y + (thiscbox->no_todisplay - 1) * 2;
	    } 
        else
	   {
	   index--;
	   ypos -= 2;
	   }
           wmove(Present->win, ypos,left_x+len+3);
           break;

	case KEY_DOWN :
        if(index==thiscbox->no_todisplay-1)
	   {
	    index = 0;
	    ypos = left_y;
	   } 
        else
	   {
	   index++;
	   ypos += 2;
	   }
           wmove(Present->win, ypos,left_x+len+3);
	   break;
        
	case 32 :
          node[index] ^= 1;
          mvwaddch(Present->win, ypos, left_x + thiscbox->len + 3, 
                    toput[node[index]]);
          wmove(Present->win, ypos, left_x + thiscbox->len + 3);
	  break;
     }
 }
	  return node;
 }

Compboxretval* getmem(int size)
{
    Compboxretval* p;
    p = (Compboxretval*)malloc(size*sizeof(int)); 
    return p;
}
