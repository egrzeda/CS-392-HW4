/*
* transp.c
*
* I pledge my honor that I have abided by the Stevens Honor System.
* Ethan Grzeda
*/

/*
* NOTES for this project
*
* - This code will be the basis of problem 2 (transpif.c)
* - Use locality principles in inner loops
* - change return type when possible or when you know what the return type should be
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


/*
* This is the structure for the outlines of the block to be transposed
*/
struct block{
	int col;
	int row;
	int width;
};

void printmatrix(float *matrix, int width);

float *randomatrix(int width);

void transposeblock(struct block tb, float **ogmat, float **tmat, int wofmat);


/*
* int main
*
* This function will create a matrix of randomly generated floats, then transpose it
*/
int main(int argc, char **argv){

	const char *wm = argv[1];
	const char *wb = argv[2];
	int wofmat = atoi(wm);
	int wofbloc =  atoi(wb);
	float *ogmat = randomatrix(wofmat);
	float *tmat = malloc(sizeof(float) * wofmat * wofmat);

	/*FOR TESTING*/
	printmatrix(ogmat, wofmat);
	printmatrix(tmat, wofmat);//I guess this one doesn't really matter, does it?
	printf("\n\n");
	fflush(stdout);

	struct block tb;
	tb.width = wofbloc;
	tb.row = 0;
	tb.col = 0;

	float **om = &ogmat;
	float **tm = &tmat;

	int blocksperrow = wofmat / wofbloc;

	for(int f = 0; f < blocksperrow; f++){
		tb.row = f;
		for(int g = 0; g < blocksperrow; g++){
			tb.col = g;
			transposeblock(tb, om, tm, wofmat);
		}
	}

	transposeblock(tb, om, tm, wofmat);

	/*FOR TESTING*/
	printf("\n\n");
	printmatrix(ogmat, wofmat);
	printmatrix(tmat, wofmat);

	free(ogmat);
	free(tmat);

	return 0;
}

/*
* void transposeblock
*
* transposes the elements of one block from the original matrix into the new matrix
*
*/
void transposeblock(struct block tb, float **ogmat, float **tmat, int wofmat){

	int wofbloc = tb.width;
	int startctr = wofbloc * tb.col;
	int startrtc = wofbloc * tb.row;
	int coltorow;
	int rowtocol;

	*(*tmat+10) = *(*ogmat+10);//THIS LINE SEG FAULTS FOR SOME REASON


	for(int d = 0; d < wofbloc; d++){
		for(int e = 0; e < wofbloc; e++){
			coltorow = startctr + d;
			rowtocol = startrtc + e;
			int tmposition = coltorow*wofmat+rowtocol;
			int omposition = rowtocol*wofmat+coltorow;
			*(*tmat + tmposition) = *(*ogmat+omposition);
		}
	}
}

/*
* void printmatrix
*
* This function is only to be used for testing purposes in order to view a matrix in the works. It
* also assumes that the matrix is square, hence only having one width parameter
*
* - change parameters
*/
void printmatrix(float *matrix, int width){
	printf("The width is %i\n", width);
	for(int b = 0; b < width * width; b++){
		if(b % width == 0 && b != 0){
			printf("\n");
		}
		printf("%f ", matrix[b]);
	}
	printf("\n");
	fflush(stdout);
}

/*
* float *randomatrix
*
* returns a randomly created matrix of floats in the form of a 1-dimensional array with the
* length being the square of the width inputted. These floats are between 0 and 100, by the way
*
* - make sure to create another input for this for the problem 2 version
* - are there any limits as to what floats can be created here, or is it just completely random?
*/
float *randomatrix(int width){
	float *randoms = malloc(sizeof(float) * width * width);
	for(int a = 0; a < width * width; a++){
		randoms[a] = (float)((float)rand() / RAND_MAX * 200 - 100);
	}
	return randoms;
}
