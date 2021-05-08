#ifndef _BUTTON_H

#define _BUTTON_H


typedef struct buttonstruct_tag 
    {
    int attr;
    char** todisplay;
    int no_todisplay;
    int maxl;
    struct
    {
    int index;
    int position;
    } state;

    } Buttonstruct;

typedef int  Buttonretval;


Buttonstruct* createbutton( int attr, int num, char** ptr );
void addbutton( Winstruct*, Buttonstruct*, int, int ); 
Buttonretval* acceptbutton( Buttonstruct*, int, int );
void displaybutton( Buttonstruct*, int, int );
#endif
