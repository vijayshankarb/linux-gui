#ifndef _RADIOBOX_H

#define _RADIOBOX_H 


typedef struct Radioboxstruct_tag 
    {
    int attr;
    char** todisplay;
    int no_todisplay;
    struct
    {
    int index;
    int position;
    } state;

    } Radioboxstruct;

typedef int  Radioboxretval;


Radioboxstruct* createradiobox( int attr, int num, char** ptr );
void addradiobox( Winstruct*, Radioboxstruct*, int, int ); 
Radioboxretval* acceptradiobox(Radioboxstruct*, int, int );
void displayradiobox(Radioboxstruct*, int, int );
#endif
