/******************************************************************************
   Example 3    :              Omp_MatVect_Mult.c

   Objective    : Write an OpenMP program for Matrix vector multiplication
                  This example demonstrates the use of PARALLEL Directive
                  and Shared, Private clause .It uses loop work-sharing
                  construct i.e. distribution of columns of matrix

   Input        : Size of matrix (rows and columns) and vector size

   Output       : Each thread computes the assigned row vector multiplication
                  and master prints the final output

******************************************************************************/

#include <stdio.h>
#include <omp.h>

/* Main Program */

main()
{
	int             NoofRows, NoofCols, Vectorsize, i, j;
	float         **Matrix, *Vector, *Result, *Checkoutput;

	printf("Read the matrix size noofrows and columns and vectorsize\n");
	scanf("%d%d%d", &NoofRows, &NoofCols, &Vectorsize);

	if (NoofRows <= 0 || NoofCols <= 0 || Vectorsize <= 0) {
		printf("The Matrix and Vectorsize should be of positive sign\n");
		exit(1);
	}
	/* Checking For Matrix Vector Computation Necessary Condition */

	if (NoofCols != Vectorsize) {
		printf("Matrix Vector computation cannot be possible \n");
		exit(1);
	}
	/* Dynamic Memory Allocation  And Initialization Of Matrix Elements */

	Matrix = (float **) malloc(sizeof(float) * NoofRows);
	for (i = 0; i < NoofRows; i++) {
		Matrix[i] = (float *) malloc(sizeof(float) * NoofCols);
		for (j = 0; j < NoofCols; j++)
			Matrix[i][j] = i + j;
	}

	/* Printing The Matrix */

	printf("The Matrix is \n");
	for (i = 0; i < NoofRows; i++) {
		for (j = 0; j < NoofCols; j++)
			printf("%f \t", Matrix[i][j]);
		printf("\n");
	}

	printf("\n");

	/* Dynamic Memory Allocation */

	Vector = (float *) malloc(sizeof(float) * Vectorsize);

	/* vector Initialization */

	for (i = 0; i < Vectorsize; i++)
		Vector[i] = i;

	printf("\n");

	/* Printing The Vector Elements */

	printf("The Vector is \n");
	for (i = 0; i < Vectorsize; i++)
		printf("%f \t", Vector[i]);

	/* Dynamic Memory Allocation */

	Result = (float *) malloc(sizeof(float) * NoofRows);

	Checkoutput = (float *) malloc(sizeof(float) * NoofRows);

	for (i = 0; i < NoofRows; i = i + 1)
	{
	Result[i]=0;
	Checkoutput[i]=0;
	}

	/* OpenMP Parallel Directive */

#pragma omp parallel for private(j)
	for (i = 0; i < NoofRows; i = i + 1)
		for (j = 0; j < NoofCols; j = j + 1)
			Result[i] = Result[i] + Matrix[i][j] * Vector[j];

	/* Serial Computation */

	for (i = 0; i < NoofRows; i = i + 1)
		for (j = 0; j < NoofCols; j = j + 1)
			Checkoutput[i] = Checkoutput[i] + Matrix[i][j] * Vector[j];

	for (i = 0; i < NoofRows; i = i + 1)
		if (Checkoutput[i] == Result[i])
			continue;
		else {
			printf("There is a difference from Serial and Parallel Computation \n");
			exit(1);
		}


	printf("\nThe Matrix Computation result is \n");
	for (i = 0; i < NoofRows; i++)
		printf("%f \n", Result[i]);

	/* Freeing The Memory Allocations */

	free(Vector);
	free(Result);
	free(Matrix);
	free(Checkoutput);

}
