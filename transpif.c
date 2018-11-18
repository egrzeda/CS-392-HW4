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

void printmatrix(float *matrix, int width);

float *randomatrix(int width);

void transposeblock(struct block tb, float **ogmat, float **tmat, int wofmat);

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
	int vertblocks = hofmat / wofbloc;

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
