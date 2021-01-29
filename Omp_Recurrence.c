/*****************************************************************************
   Example 9    :            Omp_Recurrence.c

   Objective    : Write an OpenMP program for parallelization of a loop nest
                  containing a recurrence
                  This example demonstrates the use of PARALLEL DIRECTIVE


   Input        : User has to set OMP_NUM_THREADS environment variable for
                  n number of threads and size of the Matrix

   Output       : Each thread does the row wise recurrence calculation
                  and the final Matrix is printed by the Master Thread

**********************************************************************/
#include <stdio.h>
#include <omp.h>

/* Main Program */

main()
{
	double        **InputMatrix, **CheckMatrix;
	int             j, i, N;

	printf("Enter the size of the Matrix\n");
	scanf("%d", &N);

	/* Input Checking */
	if (N <= 0) {
		printf("Array Size Should Be Of Positive Sign \n");
		exit(1);
	}
	/* Dynamic Memory Allocation */

	InputMatrix = (double **) malloc(sizeof(double) * N);
	CheckMatrix = (double **) malloc(sizeof(double) * N);

	/* Initializing The Matrix Elements */

	for (i = 0; i < N; i++) {
		InputMatrix[i] = (double *) malloc(sizeof(double) * N);
		for (j = 0; j < N; j++)
			InputMatrix[i][j] = i + j;
	}

	/* CheckMatrix Is Also Same As Input Matrix */

	for (i = 0; i < N; i++) {
		CheckMatrix[i] = (double *) malloc(sizeof(double) * N);
		for (j = 0; j < N; j++)
			CheckMatrix[i][j] = InputMatrix[i][j];
	}

	/* Printing Input Matrix */

	printf("The Input Matrix Is\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf("%lf\t", InputMatrix[i][j]);
		printf("\n");
	}

	/* OpenMP Parallel For Directive */

	for (j = 0; j < N; j++)
#pragma omp parallel for
		for (i = 0; i < N; i++)
			InputMatrix[i][j] = InputMatrix[i][j] + InputMatrix[i][j - 1];

	/* For Validity Of Output */

	/* Serial Calculation\n */

	for (j = 0; j < N; j++)
		for (i = 0; i < N; i++)
			CheckMatrix[i][j] = CheckMatrix[i][j] + CheckMatrix[i][j - 1];



	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (CheckMatrix[i][j] == InputMatrix[i][j]) {
				continue;
			} else {
				printf("Not Equal \n");
				exit(1);
			}


	printf("\n Serail And Parallel Calculation Are Same. \n");

	printf("\nThe Output Matrix After Loop Nest Containing a Recurrence \n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf("%lf\t", InputMatrix[i][j]);
		printf("\n");
	}


	printf("\n");

	/* Freeing Of Allocated Memory */

	free(InputMatrix);
	free(CheckMatrix);

}
