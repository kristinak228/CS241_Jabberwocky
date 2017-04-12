#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

void read_write( FILE*, FILE* );

int main( int argc, char * argv[] ){

	FILE *ifp, *ofp;
	clock_t begin_time, end_time;
	double time_used;

	if(argc < 3){
                fprintf(stderr, "Not enough arguments\n");
        }
        if(!(ifp = fopen(argv[1], "r"))){
                fprintf(stderr, "Cannot open file %s\n", argv[1]);
        }
        if(!(ofp = fopen(argv[2], "w"))){
                fprintf(stderr, "Cannot open file %s\n", argv[2]);
        }

        begin_time = clock();
        read_write(ifp, ofp);
        end_time = clock();
        time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
        fprintf(stderr, "Time usage = %17.13f\n", time_used);

        fclose(ifp);
        fclose(ofp);

	return 0;
}

void read_write( FILE * inputFile, FILE * outputFile ){
	
	char ch;

	while( (ch = fgetc(inputFile)) != EOF ){ 

		// put the return values into buffer of size 8 (8-bit) 
	        char buff[8];

//		for(unsigned i=0; i<8; i++)printf("%c",'0'+((ch>>i)&0x1));
		
		// strip bit by bit to get binary conversion
		if( ch & 1 ) buff[0] = 1;
		else buff[0] = 0;

		if( ch & 2 ) buff[1] = 1;
                else buff[1] = 0;
                
		if( ch & 4 ) buff[2] = 1;
                else buff[2] = 0;
                
		if( ch & 8 ) buff[3] = 1;
                else buff[3] = 0;

		if( ch & 16 ) buff[4] = 1;
                else buff[4] = 0;
                
		if( ch & 32 ) buff[5] = 1;
                else buff[5] = 0;
               
		if( ch & 64 ) buff[6] = 1;
      		else buff[6] = 0;
            
		if( ch & 128 ) buff[7] = 1;
                else buff[7] = 0;
		
		// write to output file backwards becuase that is how Tino 
		// does it :)
		for(int i = 7; i >= 0; --i){
			fputc(buff[i] + '0', outputFile);	
		}	
		
	}
	fputc('\n', outputFile);
}













