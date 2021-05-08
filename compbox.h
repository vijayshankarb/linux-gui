#ifndef  _COMPBOX_H

#define   _COMPBOX_H  


typedef struct Compboxstruct_tag 
    {
    int attr;
    char** todisplay;
    int no_todisplay;
    int len;
    } Compboxstruct;

typedef int  Compboxretval;

 
 Compboxstruct* createcompbox(int attr,int num,char** ptr);
void addcompbox( Winstruct*, Compboxstruct*, int, int ); 
Compboxretval* acceptcompbox(Compboxstruct*,int,int);
void displaycompbox( Compboxstruct*, int, int );
#endif
