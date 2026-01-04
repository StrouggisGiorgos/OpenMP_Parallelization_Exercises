//Georgios Strouggis AM5357
#include <omp.h>
#include <stdio.h>

long count = 10000; 

void serial_test() {
    double sum = 0.0;
    double sum2 = 0.0;
    for (int i = 0; i < count; i++) {
        sum += 1.0;
        for (int j = 0; j < count; j++) {
            sum2 += sum;
        }
    }
}

void taskloop_test() {
    double sum = 0.0;
    double sum2 = 0.0;

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            #pragma omp taskloop
            for (int i = 0; i < count; i++) {
                double local_sum = 0.0; 
                for (int j = 0; j < count; j++) {
                    local_sum += 1.0;
                }
                #pragma omp atomic
                sum2 += local_sum; 
            }
        }
    }
}


int main()
{
	
	double temp1=0;
	double temp2=0;
	temp1 = omp_get_wtime();
	serial_test();
	temp2 = omp_get_wtime();
	printf("[serial] count = %ld, (time = %.2f s)\n", count, temp2-temp1);
	temp1 = omp_get_wtime();
	taskloop_test();
	temp2 = omp_get_wtime(); 
	printf("[taskloop] count = %ld, (time = %.2f s)\n", count, temp2-temp1);
	
	return 0;
}
