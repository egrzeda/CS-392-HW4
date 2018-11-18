/*
* transpif.c
*
* I pledge my honor that I have abided by the Stevens Honor System.
* Ethan Grzeda
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*
* This is the structure for the outlines of the block to be transposed
*/
struct block{
	int row;
	int col;
	int width;
};

void printmatrix(float *matrix, int height, int width);

float *randomatrix(int height, int width);

void transposeblock(struct block tb, float **ogmat, float **tmat, int hofmat, int wofmat);

/*
* int main
*
* This function does what transp.c does, but with any matrix dimensions and block dimensions.
*/
int main(int argc, char **argv){

	/* setting up some variables; this is copied from transp.c for the most part */
	const char *hm = argv[1];
	const char *wm = argv[2];
	const char *wb = argv[3];
	int hofmat = atoi(hm);
	int wofmat = atoi(wm);
	int wofbloc = atoi(wb);
	float *ogmat = randomatrix(hofmat, wofmat);
	float *tmat = malloc(sizeof(float) * hofmat * wofmat);//transposed matrix

	/*FOR TESTING*/
	printmatrix(ogmat, hofmat, wofmat);
	printmatrix(tmat, wofmat, hofmat);
	printf("\n\n");
	fflush(stdout);

	struct block tb;
	tb.width = wofbloc;
	tb.row = 0;
	tb.col = 0;

	float **om = &ogmat;
	float **tm = &tmat;

	/* Getting the numbers of blocks per row and column */
	int horiblocks = wofmat / wofbloc;
	if(wofmat % wofbloc != 0){
		horiblocks++;
	}
	int vertblocks = hofmat / wofbloc;
	if(hofmat % wofbloc != 0){
		vertblocks++;
	}

	for(int f = 0; f < vertblocks; f++){
		tb.row = f;
		for(int g = 0; g < horiblocks; g++){
			tb.col = g;
			transposeblock(tb, om, tm, hofmat, wofmat);
		}
	}

	/*FOR TESTING*/
	printf("\n\n");
	printmatrix(ogmat, hofmat, wofmat);
	printmatrix(tmat, hofmat, wofmat);

	free(ogmat);
	free(tmat);

	return 0;
}

/*
* void transposeblock
*
* transposes the elements of one block from the original matrix into the new matrix
*
* Note: throughout this whole function, the height and width of the matrix are used in reverse
* for the transposed matrix since the dimensions are going to be different if it's not square.
*/
void transposeblock(struct block tb, float **ogmat, float **tmat, int hofmat, int wofmat){

	/* I think this following section should be the same for this as in transp.c */
	int wofbloc = tb.width;
	int startctr = wofbloc * tb.col;
	int startrtc = wofbloc * tb.row;
	int coltorow;
	int rowtocol;

	/* besides the boundary check, I think this should be the same as in transp.c */
	for(int d = 0; d < wofbloc; d++){
		for(int e = 0; e < wofbloc; e++){
			/* INSERT BOUNDARY CHECK IN HERE; PROBABLY IN AN IF STATEMENT */
			coltorow = startctr + d;
			rowtocol = startrtc + e;
			int tmposition = coltorow * wofmat + rowtocol;
			int omposition = rowtocol * wofmat + coltorow;
			*(*tmat + tmposition) = *(*ogmat + omposition);
		}
	}
}

/*
* void printmatrix
*
* This function is only to be used for testing purposes in order to view a matrix in the works. It
* does not assume that the matrix is square in this instance, unlike the one in transp.c.
*
*/
void printmatrix(float *matrix, int height, int width){
	printf("The height is %i\n", height);
	printf("The width is %i\n", width);
	for(int b = 0; b < height * width; b++){
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
* length being the product of the height and width inputted. These floats are between -100 and
* 100, by the way
*
*/
float *randomatrix(int height, int width){
	float *randoms = malloc(sizeof(float) * height * width);
	for(int a = 0; a < height * width; a++){
		randoms[a] = (float)((float)rand() / RAND_MAX * 200-100);
	}
	return randoms;
}
