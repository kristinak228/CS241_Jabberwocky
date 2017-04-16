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
	
	char bit;

	while( (bit = (int)fgetc(inputFile)) != EOF ){ 


		if(bit != '\n'){
			//I will set the individual bits in this character to equal the first 8 bits I read.
			unsigned char character = bit-'0' << 7 |
						 (int)fgetc(inputFile)-'0' << 6 |
						 (int)fgetc(inputFile)-'0' << 5 |
						 (int)fgetc(inputFile)-'0' << 4 |
						 (int)fgetc(inputFile)-'0' << 3 |
						 (int)fgetc(inputFile)-'0' << 2 |
						 (int)fgetc(inputFile)-'0' << 1 |
						 (int)fgetc(inputFile)-'0';
		
			
			fputc(character, outputFile);	
		}
	}
//	fputc('\n', outputFile);
}













