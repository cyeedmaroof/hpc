/******************************************************************************
   Example 7    :           Omp_Recursion.c

   Objective    : Write an OpenMP program for recursive computation
                  This example demonstrates the use of
                  PARALLEL For DIRECTIVE and Critical Section  Clause

   Input        : User has to set OMP_NUM_THREADS environment variable for
                  running and the size of the array

   Output       : The Master thread prints the final elements of the array

*****************************************************************************/

#include <stdio.h>
#include <omp.h>

/* Main Program */

main()
{
	int             i, N;
	float          *array, *check;

	/* Size Of An Array */

	printf("Enter the size \n");
	scanf("%d", &N);

	if (N <= 0) {
		printf("Array Size Should Be Of Postive Sign \n");
		exit(1);
	}
	/* Dynamic Memory Allocation */

	array = (float *) malloc(sizeof(float) * N);
	check = (float *) malloc(sizeof(float) * N);

	/* Initialization Of Array Elements  */

	for (i = 0; i < N; i++) {
		array[i] = i * 1;
		check[i] = i * 1;
	}

	/* The Input Array Is */
	printf("The Input Array Is\n");

	for (i = 0; i < N; i++)
		printf("%f\t", array[i]);


	/* OpenMP Parallel For Directive And Critical Section */

#pragma omp parallel for
	for (i = 1; i < N; i++) {
#pragma omp critical
		array[i] = (array[i - 1] + array[i]) / 2;
	}

	/* Serial Calculation */

	for (i = 1; i < N; i++)
		check[i] = (check[i - 1] + check[i]) / 2;

	/* Output Checking */

	for (i = 0; i < N; i++) {
		if (check[i] == array[i])
			continue;
		else {
			printf("There is a difference in the parallel and serial calculation \n");
			exit(1);
		}
	}

	/* The Final Output */

	printf("\nThe Array Calculation Is Same Using Serial And OpenMP Directives\n");
	printf("The Output Array Is \n");
	for (i = 0; i < N; i++)
		printf("\n %f \t", array[i]);

printf("\n");
	/* Freeing The Memory */

	free(array);
	free(check);
}
