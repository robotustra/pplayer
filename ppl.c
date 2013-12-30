#include <stdio.h>
#include <ctype.h>
#include <locale.h>

#define MAX_OBJ 	1024
#define MAX_BYTES	1024
#define DEBUG_LEVEL 3

/*
* Lookups input buffer and find the next name of symbol:
* There is a restriction on symbols, it could be a word, number or sign.
* words contain letters only, numbers - digits only, signs - any delimiter or bracket.
* symbol, object, dynamic object.
* if it's a symbol - just write it to the output. if it's an object - should substitute it with set of 
* objects or symbols. if it's number - just treat it as symbol.
* pattern - it's a group of objects by type. to substitute it we should have a defined pattern.
*/
int get_name(char* ibuf, int ibuf_len, int offset)
{
	char ctmp = 0;
	int idx = 0;

	if (offset > ibuf_len) return 0;

	ctmp = ibuf[ offset + idx ];
	
	setlocale(LC_ALL, "");

	if (isalpha(ctmp)) 
	{
		while(1) 
		{
			ctmp = ibuf[ offset + idx ];
			if (!isalpha(ctmp) || ( (offset+idx) == ibuf_len ) )
			{
				break; //return(offset+idx);
			}
			idx++;
			
		}
	}
	
	return (offset+idx);
	
	/*
	if (is(ctmp)) {};
	if (isNonLetter(ctmp)) {};
	if (isdigit(ctmp)) {}; 
	*/
	//isalnum, iscntrl, isdigit, ispunct, isupper, islower

}


int main (int argc, char* argv[])
{
	FILE* fdb;	// database of all objects
	FILE* input; 
	FILE* output;
	long fpos = 0;
	int c, i;
	long count = 0;
	char buffer[] = { 0x01 , 'o', 'b', 'j', 'e', 'c', 't', 's', '.', 't', 'x', 't' , 0x02 };
	long iobjb [MAX_OBJ];	// starting index of objects (offset)
	long iobje [MAX_OBJ];
    long isymb [MAX_OBJ];	// symbols
    long isyme [MAX_OBJ];
    long ipatb [MAX_OBJ];	// patterns
    long ipate [MAX_OBJ];
    int	 odx = 0; 			// object counter.
    int  sdx = 0;			// symbol counter.
    int  pdx = 0;			// pattern counter.
    char bcache [MAX_BYTES];// cache of string form file.
    char ibuf [MAX_BYTES]; 	// input buffer, only first MAX_BYTES are interpreted.
    long ibuf_len = 0;
    int  inextb = 0; 		// the index of the next symbol
    int  inexte = 0; 		// the index of the next symbol
    
    printf("pplayer \n");

	// 1) Open local database
    fdb = fopen ("objects.txt","r+b");
  	if (fdb == NULL)
  	{
    	printf ("Failed to open objects! Exiting!\n");
    	return 1;
  	}


	// 2) Load all objects
	fseek(fdb, 0, SEEK_END);
	fpos = ftell(fdb);

	if (fpos == 0)
	{
		// 2.1) Create default header for databse.
		printf("Writing default header...\n");
  		fwrite (buffer , sizeof(char), sizeof(buffer), fdb);
	}
	else
	{
		printf("The length of database is %d bytes.\n", fpos);
	}

	// 2.2 Creating index of objects.
	fseek(fdb, 0, SEEK_SET);
  	while(1)
   	{
    	c = fgetc(fdb);
    	if( feof(fdb) )
      	{
        	break ;
      	}

      	if( c == 0x01 ) // objects
      	{
      		//new object is found.
      		iobjb[odx++] = count; 

      	}

      	if( c == 0x03 ) // symbols
      	{
      		//new object is found.
      		isymb[sdx++] = count; 

      	}

      	if( c == 0x05 ) // patterns
      	{
      		//new object is found.
      		ipatb[pdx++] = count; 

      	}

      	//printf("%c", c);
      	count++;
   	}

   	printf("Objects read: %d.\n", odx);
   	printf("Symbols read: %d.\n", sdx);
   	printf("Patterns read: %d.\n", pdx);

   	if (DEBUG_LEVEL >= 3)
   	{
   		printf("Objects:");
   		for (i=0; i<odx; i++) printf("%d:", iobjb[i]);
   		printf("\n");
   		printf("Symbols:");
   		for (i=0; i<sdx; i++) printf("%d:", isymb[i]);
   		printf("\n");
   		printf("Patterns:");
   		for (i=0; i<pdx; i++) printf("%d:", ipatb[i]);
   		printf("\n");
   	}

    // 3) Split on all symbols
    // 3.0) Read input file
    input = fopen ("input.txt","r");
  	if (input == NULL)
  	{
  		// This is supposed to be normal termination
    	printf ("No input! Exiting!\n");
    	if (fdb != NULL) fclose(fdb);
    	return 0;
  	}
  	fseek(input, 0, SEEK_SET);
  	count = 0;
  	while(1)
   	{
    	c = fgetc(input);
    	if( feof(input) || (count == (MAX_BYTES - 2)) )
      	{
        	ibuf_len = count;
        	break ;
      	}
      	ibuf[count] = c;
      	count++;
   	}
   	for (i = count; i < MAX_BYTES; ++i) ibuf[i] = 0; // clean the rest of the buffer.
	
	printf("Input has %d bytes.\n", count);
	fclose(input);
   	
	// 3.0.1) Looking for symbols. There is a restriction on symbols, it could be a word, number or sign.
	// words contain letters only, numbers - digits only, signs - any delimiter or bracket.
	// symbol, object, dynamic object.
	// if it's a symbol - just write it to the output. if it's an object - should substitute it with set of 
	// objects or symbols. if it's number - just treat it as symbol.
  	// pattern - it's a group of objects by type. to substitute it we should have a defined pattern.

	inextb = get_name(ibuf, ibuf_len, 0);

	printf("The name is found at offset %d.\n", inextb);



    // 3.1) If not all objects are found - ask a description of object.
    // 3.2) Repeat until all symbols are known.
    // 4) Find gropes of symbols
	// 5) Do the sequential substitution from all objects to symbols.
	// 6) Save everything and exit.  
    	

  	if (fdb != NULL) fclose(fdb);

	return 0;

}

