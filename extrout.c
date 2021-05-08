#include <curses.h>
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
