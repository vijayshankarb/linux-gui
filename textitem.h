#ifndef _TEXTITEM_H
#define _TEXTITEM_H 

typedef struct Textitemstruct_tag 
    {
    int attr;
    char* todisplay;
    } Textitemstruct;

typedef void  Textitemretval;

Textitemstruct* createtextitem( int attr,  char* ptr );
void addtextitem( Winstruct*, Textitemstruct*, int, int ); 
Textitemretval* accepttextitem( Textitemstruct*, int, int );
void displaytextitem( Textitemstruct*, int, int );
#endif
