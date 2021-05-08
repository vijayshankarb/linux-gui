#ifndef _PASSWORD_H

#define _PASSWORD_H 

typedef struct Passwordstruct_tag 
    {

    int attr;
    char* todisplay;
    int size;

    } Passwordstruct;

typedef char  Passwordretval;


Passwordstruct* createpassword( int attr,  char* ptr ,int size );
void addpassword( Winstruct*, Passwordstruct*, int, int ); 
Passwordretval* acceptpassword( Passwordstruct*, int, int );
void displaypassword( Passwordstruct*, int, int );
#endif
