#include <curses.h>
#include "windows.h"
#include "formitem.h"
#include "textitem.h"
#include "button.h"
#include "compbox.h"
#include "radiobox.h"
#include "password.h"
#include "lightbar.h"

struct list_tag{
char word[20];
Winstruct* p;
struct list_tag* next;
} *head, *sptr;

void main( void )
    {
    Formitemstruct* fb[10];
    Textitemstruct* tb[10];
    Radioboxstruct* rb[10];
    Compboxstruct*  cb[10];
    Buttonstruct*   bb[10];
    Passwordstruct* pb[10];
    Lightbarstruct* lb[10];
    Winstruct *f1, *f2, *f3, *f4, *f5, *demo;
    int output, type, count;
    char **ptr;
    char **loc1;
    char **not1;
    char **str1;
    int attr_type, mode;
int windex = 0, findex = 0, tindex = 0, rindex = 0,
    cindex = 0, bindex = 0, pindex = 0, lindex = 0;
char *f[]= { "demo", "create", "activate", "quit" };  
char *obj[] = { "create formitem", "create textitem", "create radiobox",
"create compbox", "create button",  "create password", "create lightbar"              };
    char *estr[] = { "employee name", "employee age", "employee sex" };
    char *onc[] = { "OK", "NEXT", "CANCEL" }; 

    char *ewnp[] = { "enter window name" };
    int ewns[1] = { 15 };
    int nots[1] = { 1 };
    char *pro[] = { "prompt1", "prompt2", "prompt3", "prompt4", "prompt5" };

    char *sattr[] = { "BOLD", "REVERSE", "NORMAL" };		    
    char *locs[] = { "Y-COORDINATES", "X-COORDINATES" };
    char *not[] = { "ENTER NUM OF ITEMS" };
    char *strs[] = { "enter the prompt", "enter size" };
    int strn[] = { 20, 2 };
    int demosize[] = { 15, 2, 1 };
    Lightbarstruct *first, *second;
    Formitemstruct *fs, *ewn, *loc, *prompts, *fnot, *str;
    Radioboxstruct *attr;
    Buttonstruct *bs;
    int loc_size[] = { 2, 2 };
    initialise();
    head = sptr = NULL;

    f1 = getnewwindow( 1, 1, 20, 75, ACS_VLINE, ACS_HLINE );
    first = createlightbar( A_REVERSE, 4, f );
    addlightbar( f1, first, 7, 20 );

    demo = getnewwindow( 1, 1, 20, 75, ACS_VLINE, ACS_HLINE );
    fs = createformitem( A_BOLD, 3, estr, demosize ); 
    bs = createbutton( A_REVERSE, 3, onc );
    addformitem( demo, fs, 5, 10 );
    addbutton( demo, bs, 15, 10 );
    
    f2 = getnewwindow( 1, 1,20, 75, ACS_VLINE, ACS_HLINE );
    second = createlightbar( A_REVERSE, 7, obj );
    addlightbar( f2, second, 5, 20 );

    f3 = getnewwindow( 1, 1, 20, 75, ACS_VLINE, ACS_HLINE );
    ewn = createformitem( A_BOLD, 1, ewnp, ewns );
    addformitem( f3, ewn, 10, 10 );
   
    f4 = getnewwindow( 1, 1, 20, 75, ACS_VLINE, ACS_HLINE );
    loc = createformitem( A_BOLD, 2, locs, loc_size );
    fnot = createformitem( A_BOLD, 1, not, nots );
    attr = createradiobox( A_BOLD, 3, sattr ); 
    prompts = createformitem( A_BOLD, 5, pro, NULL );

    addformitem( f4, loc, 3, 10 );
    addformitem( f4, fnot, 2, 40 );
    addradiobox( f4, attr, 9, 10 );
    addformitem( f4, prompts, 5, 40 );

    f5 = getnewwindow( 1, 1, 20, 75, ACS_VLINE, ACS_HLINE );
    str = createformitem( A_BOLD, 2, strs, strn );

    addformitem( f5, str, 9, 30 );
    addformitem( f5, loc, 3, 10 );
    addradiobox( f5, attr, 9, 10 );


    activate( f1 );
    while( ( output = *(Lightbarretval*)acceptobject( first ) ) != 4 )
           {
	   switch( output )
	        {
		case 1:
		activate( demo );
		ptr = acceptobject( fs );
		acceptobject( bs );
		deactivate( );
                break;

		case 2:
                activate( f3 );
                ptr = acceptobject( ewn );
                deactivate( );
                for( sptr = head; sptr; sptr=sptr->next ) 
                  if( strcmp( sptr->word, ptr[0] ) == 0 ) 
                      break;
                if( sptr == NULL )
                {
                sptr = (struct list_tag*)malloc( sizeof( struct list_tag ));
                sptr->next = head;
		strcpy( sptr->word, ptr[0] );
		head = sptr;
		  sptr->p = getnewwindow( 1, 1, 20, 75, ACS_VLINE, ACS_HLINE );
                } 

		activate( f2 );
		type = *(Lightbarretval*)acceptobject( second );
		switch( type )
		    {
		    case 1:
                    activate( f4 );
                    loc1 = acceptobject( loc );
                    not1 = acceptobject( fnot );
                    attr_type = *(Radioboxretval*)acceptobject( attr );
                    ptr = acceptobject( prompts );
                    switch( attr_type )
                          {
                          case 1:
			  mode = A_BOLD;
			  break;
			  case 2:
			  mode = A_REVERSE;
			  break;
			  case 3:
			  mode = A_NORMAL;
			  break;
			  }
                    fb[findex] = createformitem( mode, atoi( not1[0] ),
                                                 ptr, NULL );
                    addformitem( sptr->p, fb[findex], atoi( loc1[0] ),
                                 atoi( loc1[1] ) );
                    findex++;  
                    /* formitem */
                    break;
                    case 2:
                    activate( f5 );
                    loc1 = acceptobject( loc );
		    str1 = acceptobject( str );
                    attr_type = *(Radioboxretval*)acceptobject( attr );
                    switch( attr_type )
                          {
                          case 1:
			  mode = A_BOLD;
			  break;
			  case 2:
			  mode = A_REVERSE;
			  break;
			  case 3:
			  mode = A_NORMAL;
			  break;
			  }
                    tb[tindex] = createtextitem( mode, str1[0] );
                    addtextitem( sptr->p, tb[tindex], atoi( loc1[0] ),
                                 atoi( loc1[1] ) );
                    tindex++;  
		    /* textitem */
		    break;
		    case 3:
                    activate( f4 );
                    loc1 = acceptobject( loc );
                    not1 = acceptobject( fnot );
                    attr_type = *(Radioboxretval*)acceptobject( attr );
                    ptr = acceptobject( prompts );
                    switch( attr_type )
                          {
                          case 1:
			  mode = A_BOLD;
			  break;
			  case 2:
			  mode = A_REVERSE;
			  break;
			  case 3:
			  mode = A_NORMAL;
			  break;
			  }
                    rb[rindex] = createradiobox( mode, atoi( not1[0] ),
                                                 ptr );
                    addradiobox( sptr->p, rb[rindex], atoi( loc1[0] ),
                                 atoi( loc1[1] ) );
                    rindex++;  
		    /* radiobox */
		    break;
		    case 4:   
                    activate( f4 );
                    loc1 = acceptobject( loc );
                    not1 = acceptobject( fnot );
                    attr_type = *(Radioboxretval*)acceptobject( attr );
                    ptr = acceptobject( prompts );
                    switch( attr_type )
                          {
                          case 1:
			  mode = A_BOLD;
			  break;
			  case 2:
			  mode = A_REVERSE;
			  break;
			  case 3:
			  mode = A_NORMAL;
			  break;
			  }
                    cb[cindex] = createcompbox( mode, atoi( not1[0] ),
                                                 ptr );
                    addcompbox( sptr->p, cb[cindex], atoi( loc1[0] ),
                                 atoi( loc1[1] ) );
                    cindex++;  
		    /* compbox */
		    case 5:
                    activate( f4 );
                    loc1 = acceptobject( loc );
                    not1 = acceptobject( fnot );
                    attr_type = *(Radioboxretval*)acceptobject( attr );
                    ptr = acceptobject( prompts );
                    switch( attr_type )
                          {
                          case 1:
			  mode = A_BOLD;
			  break;
			  case 2:
			  mode = A_REVERSE;
			  break;
			  case 3:
			  mode = A_NORMAL;
			  break;
			  }
                    bb[bindex] = createbutton( mode, atoi( not1[0] ),
                                                  ptr );
                    addbutton( sptr->p, bb[bindex], atoi( loc1[0] ),
                                 atoi( loc1[1] ) );
                    bindex++;  
		    /* button */
		    break;
		    case 6:
                    activate( f5 );
                    loc1 = acceptobject( loc );
		    str1 = acceptobject( str );
                    attr_type = *(Radioboxretval*)acceptobject( attr );
                    switch( attr_type )
                          {
                          case 1:
			  mode = A_BOLD;
			  break;
			  case 2:
			  mode = A_REVERSE;
			  break;
			  case 3:
			  mode = A_NORMAL;
			  break;
			  }
                  pb[pindex] = createpassword( mode, str1[0], atoi( str1[1] ) );
                  addpassword( sptr->p, pb[pindex], atoi( loc1[0] ),
                                 atoi( loc1[1] ) );
                    pindex++;  
		    /* password */
		    break;
		    case 7:
                    activate( f4 );
                    loc1 = acceptobject( loc );
                    not1 = acceptobject( fnot );
                    attr_type = *(Radioboxretval*)acceptobject( attr );
                    ptr = acceptobject( prompts );
                    switch( attr_type )
                          {
                          case 1:
			  mode = A_BOLD;
			  break;
			  case 2:
			  mode = A_REVERSE;
			  break;
			  case 3:
			  mode = A_NORMAL;
			  break;
			  }
                    lb[lindex] = createlightbar( mode, atoi( not1[0] ),
                                                 ptr );
                    addlightbar( sptr->p, lb[lindex], atoi( loc1[0] ),
                                 atoi( loc1[1] ) );
                    lindex++;  
		    /* lightbar */
                    break;
		    }
		    deactivate();
                    deactivate();
		break;

		case 3:
                activate( f3 );
                ptr = acceptobject( ewn );
                deactivate( );
                for( sptr = head; sptr; sptr=sptr->next ) 
                  if( strcmp( sptr->word, ptr[0] ) == 0 ) 
                     {
		     activate( sptr->p );
                     break;
                     }
                  for( count = 0; count < sptr->p->no_objects; count++ )
                       sptr->p->holder[count].accept(
                             sptr->p->holder[count].object,
                                sptr->p->holder[count].left_y,  
                                sptr->p->holder[count].left_x );  
                  deactivate();
	break;
		}
	   }
closeall();
     }  
