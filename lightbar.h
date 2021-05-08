#ifndef _LIGHTBAR_H

#define _LIGHTBAR_H 

typedef struct Lightbarstruct_tag 
    {
    int attr;
    char** todisplay;
    int no_todisplay;
    struct
    {
    int index;
    int position;
    } state;

    } Lightbarstruct;

typedef int  Lightbarretval;


Lightbarstruct* createlightbar( int attr, int num, char** ptr );
void addlightbar( Winstruct*, Lightbarstruct*, int, int ); 
Lightbarretval* acceptlightbar( Lightbarstruct*, int, int );
void displaylightbar( Lightbarstruct*, int, int );
#endif
