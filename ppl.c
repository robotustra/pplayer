#include<stdio.h>

#define MAX_OBJ 	1024
#define MAX_BYTES	1024
#define DEBUG_LEVEL 3


int main (int argc, char* argv[])
{
	FILE* fdb;
	long fpos = 0;
	int c, i;
	long count = 0;
	char buffer[] = { 0x01 , 'o', 'b', 'j', 'e', 'c', 't', 's', '.', 't', 'x', 't' , 0x02 };
	long iobjb [MAX_OBJ];	// starting index of objects (offset)
	long iobje [MAX_OBJ];
    long isymb [MAX_OBJ];
    long isyme [MAX_OBJ];
    int	 odx = 0; 			// object counter.
    char bcache [MAX_BYTES];// cache of string form file.
    
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

      	if( c == 0x01 )
      	{
      		//new object is found.
      		iobjb[odx++] = count; 

      	}

      	//printf("%c", c);
      	count++;
   	}

   	printf("Objects read: %d.\n", odx);

   	if (DEBUG_LEVEL >= 3)
   	{
   		for (i=0; i<odx; i++) printf("%d:", iobjb[i]);
   		printf("\n");
   	}

    // 3) Split on all symbols
    // 3.0) Read input file

    // 3.1) If not all objects are found - ask a description of object.
    // 3.2) Repeat until all symbols are known.
    // 4) Find gropes of symbols
	// 5) Do the sequential substitution from all objects to symbols.
	// 6) Save everything and exit.  
    	

  	if (fdb != NULL) fclose(fdb);

	return 0;

}

