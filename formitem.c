#include "windows.h"
#include "formitem.h"
#define spacing 2


void drawbox( int pos_y,  int pos_x, int y_len, int x_len );
Formitemstruct* createformitem(int attr, int no_items,
								char** pstr, int* size)
{
	Formitemstruct* p;
	int count;
	p = (Formitemstruct*)malloc(sizeof(Formitemstruct));

	p->attr = attr;
	p->no_items = no_items;

	if(size == NULL)
	{
		p->maxsize = (int*)malloc(no_items*sizeof(int));
		for(count = 0; count < no_items; count++)
		p->maxsize[count] = 10;
	}
	else
		p->maxsize = size;

	p->promptstr = pstr;
	return p;
	}

void addformitem(Winstruct* thiswindow, Formitemstruct* comp, int left_y,
				 int left_x)
{
store_pert_info(thiswindow, comp, (accepttype)acceptformitem,
			(displaytype)displayformitem, left_y, left_x);
}

void displayformitem(Formitemstruct* thisfitem,
						int left_y, int left_x)
{
	int count;
	int mlen, len;
	mlen = strlen(thisfitem->promptstr[0]);
	for(count = 1; count < thisfitem->no_items; count++)
		if((len = strlen(thisfitem->promptstr[count]) > mlen))
		mlen = len;

	thisfitem->maxlen = mlen;

	wattrset(Present->win, thisfitem->attr);
	for(count = 0; count < thisfitem->no_items; count++)
		mvwaddstr(Present->win, left_y + count * 3,
			left_x + mlen - strlen(thisfitem->promptstr[count]),
						   thisfitem->promptstr[count]);

	wattroff(Present->win, thisfitem->attr);

	left_x = left_x + mlen + spacing;

	for(count = 0; count < thisfitem->no_items; count++)
		 drawbox(left_y - 1 + count*3, left_x, 1,
				  thisfitem->maxsize[count] + 1);
}

Formitemretval* acceptformitem(Formitemstruct* thisfitem,
					int left_y , int left_x)
{
	int exit = false;
	int start_x = left_x + thisfitem->maxlen + spacing + 1;
	int cur_x = start_x, cur_y = left_y;
	int offset, noffset;
	int index = 0;
	chtype ch;
	char** ptr;
	int count;

	struct {
	int n_present;
	char *wptr;
	} curstatus[MAXITEMS];

	ptr = (char**)malloc(thisfitem->no_items*sizeof(char*));
	for(count = 0; count < thisfitem->no_items; count++)
	{
	ptr[count]=(char*)malloc(thisfitem->maxsize[count]*sizeof(char));
		ptr[count][0] = '\0';
		curstatus[count].wptr = ptr[count];
		curstatus[count].n_present = 0;
	}

	wmove(Present->win, cur_y, cur_x);
	curs_set(1);
	while(!exit)
	{
		ch = input_key;
		switch(ch)
		{
		case KEY_LEFT:
		if(cur_x == start_x) break;
		curstatus[index].wptr--;
		cur_x--;
		wmove(Present->win, cur_y, cur_x);
		break;

		case KEY_RIGHT:
		if((cur_x - start_x) ==	curstatus[index].n_present)
		break;
		curstatus[index].wptr++;
		cur_x++;
		wmove(Present->win, cur_y, cur_x);
		break;

		case KEY_UP:
		if(index == 0) break;
		index--;
		offset = cur_x - start_x;
		noffset = offset <= curstatus[index].n_present ?
			offset : curstatus[index].n_present;
		cur_x = start_x + noffset;
		cur_y -= 3;
		curstatus[index].wptr = ptr[index] + noffset;
		wmove(Present->win, cur_y, cur_x);
		break;

		case 10:
		if(index == thisfitem->no_items - 1)
		{
			exit = true;
			break;
		}

		case KEY_DOWN:
		if(index == thisfitem->no_items - 1) break;
		index++;
		offset = cur_x - start_x;
		noffset = offset <= curstatus[index].n_present ?
			 offset : curstatus[index].n_present;
		cur_x = start_x + noffset;
		cur_y += 3;
		curstatus[index].wptr = ptr[index] + noffset;
		wmove(Present->win, cur_y, cur_x);
		break;

		case KEY_BACKSPACE:
		if(cur_x == start_x) break;
		wmove(Present->win, cur_y, start_x + thisfitem->maxsize[index]);
		winsch(Present->win, ' ');
		cur_x--;
		wmove(Present->win, cur_y, cur_x);
		wdelch(Present->win);
		box(Present->win, Present->Vline, Present->Hline);

		memmove(curstatus[index].wptr - 1, curstatus[index].wptr,
			ptr[index] + thisfitem->maxsize[index] - curstatus[index].wptr + 1);
		curstatus[index].wptr--;
		curstatus[index].n_present--;
		break;

		case 11:
		if(cur_x == start_x + curstatus[index].n_present) break;
		wmove(Present->win, cur_y, start_x + thisfitem->maxsize[index]);
		winsch(Present->win, ' ');

		wmove(Present->win, cur_y, cur_x);
		wdelch(Present->win);
		box(Present->win, Present->Vline, Present->Hline);
		memmove(curstatus[index].wptr ,
		curstatus[index].wptr + 1, ptr[index] +	thisfitem->maxsize[index] -
								  curstatus[index].wptr);
		curstatus[index].n_present--;
		break;

		case 27:
		exit = true;
		break;

		default:
		if(!isprint(ch) ||
			  curstatus[index].n_present == thisfitem->maxsize[index]) break;
		winsch(Present->win, ch);
		wmove(Present->win, cur_y, start_x + thisfitem->maxsize[index]);
		wdelch(Present->win);
		box(Present->win, Present->Vline, Present->Hline);
		cur_x++;
		wmove(Present->win, cur_y, cur_x);
		memmove(curstatus[index].wptr + 1, curstatus[index].wptr,
			   ptr[index] + thisfitem->maxsize[index] - curstatus[index].wptr + 1);
		*(curstatus[index].wptr) = (char)ch;
		curstatus[index].wptr++;
		curstatus[index].n_present++;
		break;
		}
	}
	return ptr;
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
