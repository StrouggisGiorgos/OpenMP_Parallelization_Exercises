//Georgios Strouggis AM5357
#include <stdio.h>
#include <omp.h>

#define UPTO 10000000

long int count,      /* number of primes */
         lastprime;  /* the last prime found */


void serial_primes(long int n) {
	long int i, num, divisor, quotient, remainder;

	if (n < 2) return;
	count = 1;                         /* 2 is the first prime */
	lastprime = 2;

	for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
		num = 2*i + 3;

		divisor = 1;
		do 
		{
			divisor += 2;                  /* Divide by the next odd */
			quotient  = num / divisor;  
			remainder = num % divisor;  
		} while (remainder && divisor <= quotient);  /* Don't go past sqrt */
		
		if (remainder || divisor == num) /* num is prime */
		{
			count++;
			lastprime = num;
		}
	}
}


void openmp_primes(long int n) {
	long int i, num, divisor, quotient, remainder;

	if (n < 2) return;
	count = 1;                   
	lastprime = 2;
	
	 #pragma omp parallel num_threads(4) private(i, num, divisor, quotient, remainder)
    {
        long int local_count = 0;
        long int local_lastprime = 2;
        	
	 	#pragma omp for schedule(dynamic)
	 	for (i = 0; i < (n-1)/2; ++i) {   
			num = 2*i + 3;

			divisor = 1;
			do 
			{
				divisor += 2;               
				quotient  = num / divisor;  
				remainder = num % divisor;  
			} while (remainder && divisor <= quotient);  
			
			if (remainder || divisor == num) {  
                		local_count++;
                		local_lastprime = num;  
            }
		}
        #pragma omp atomic
        count += local_count;

        #pragma omp critical
         {
             if (local_lastprime > lastprime) {
                 lastprime = local_lastprime;
             }
         }
	}
}


int main()
{
	printf("Serial and parallel prime number calculations:\n\n");
	
	/* Time the following to compare performance 
	 */
	double temp1=0;
	double temp2=0;
	temp1 = omp_get_wtime();
	serial_primes(UPTO);        /* time it */
	temp2 = omp_get_wtime();
	printf("[serial] count = %ld, last = %ld (time = %.2f s)\n", count, lastprime, temp2-temp1);
	temp1 = omp_get_wtime();
	openmp_primes(UPTO);
	temp2 = omp_get_wtime();        /* time it */
	printf("[openmp] count = %ld, last = %ld (time = %.2f s)\n", count, lastprime, temp2-temp1);
	
	return 0;
}

