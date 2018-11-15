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
	/* finding out where to start with the block to be transposed */
	int startpoint = (tb.width * tb.col) + (tb.width * tb.col * wofmat);
	int coltorow = tb.width * tb.col;
	int rowtocol = tb.width * tb.row;
	int elementstocopy = tb.width * tb.width;
	int c = 0;
	while(1){
		/* The following loop is the core of the transposition. Add the actual
		   transposition in now. */
		if(c % wofmat == 0){
			rowtocol++;
			coltorow = tb.width * tb.col;
			if(rowtocol == tb.width){
				break;
			}
		}
		c++;
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
