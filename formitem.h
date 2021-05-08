#ifndef _FORMITEM_H

#define _FORMITEM_H 

#define MAXITEMS 10

typedef struct Formitemstruct_tag 
    {
    int attr;
    char** promptstr;
    int* maxsize;
    int maxlen;
    int no_items;

    } Formitemstruct;

typedef char*  Formitemretval;


Formitemstruct* createformitem(int attr, int no_items, char** pstr, int* size );
void addformitem( Winstruct*, Formitemstruct*, int, int ); 
Formitemretval* acceptformitem( Formitemstruct*, int, int );
void displayformitem( Formitemstruct*, int, int );
#endif
