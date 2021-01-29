/**********************************************************************
  Example 5    :           Omp_PI_Calculation.c

  Objective    : Write an OpenMP program to compute the value of pi
                 function by numerical integration of a function
                 f(x) = 4/(1+x*x ) between the limits 0 and 1
                 This example demonstrates the use of PARALLEL FOR
                 DIRECTIVE with usage of Private , Shared clause and
                 Critical Section

  Input        : User has to set OMP_NUM_THREADS environment variable for
                 n number of threads and has to specify the number of intervals

  Output       : Each thread calculates the partial sum and then the master
                 thread prints the final PI value


**********************************************************************/

#include<stdio.h>
#include<omp.h>

#define PI 3.1415926538837211

/* Main Program */

main()
{
	int             Noofintervals, i;
	float           sum, x, totalsum, h, partialsum, sumthread;

	printf("Enter number of intervals\n");
	scanf("%d", &Noofintervals);

	if (Noofintervals <= 0) {
		printf("Number of intervals should be positive integer\n");
		exit(1);
	}
	sum = 0.0;
	h = 1.0 / Noofintervals;

	/*
	 * OpenMP Parallel Directive With Private Shared Clauses And Critical
	 * Section
	 */

#pragma omp parallel for private(x) shared(sumthread)
	for (i = 1; i < Noofintervals + 1; i = i + 1) {
		x = h * (i - 0.5);

		/* OPENMP Critical Section Directive */

#pragma omp critical
		sumthread = sumthread + 4.0 / (1 + x * x);
	}
	partialsum = sumthread * h;

	/* OpenMP Critical Section Directive */

#pragma omp critical
	sum = sum + partialsum;

	printf("The value of PI is \t%f  \nerror is \t%1.16f\n", sum, fabs(sum - PI));
}
