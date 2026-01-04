//Georgios Strouggis AM5357
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

/* 
 * Retrieves and prints information for every installed NVIDIA
 * GPU device
 */
void cuinfo_print_devinfo()
{
	int num_devs, i;
	cudaGetDeviceCount(&num_devs);
	
	int driverVersion;
	int runtimeVersion; 
	
	if (num_devs == 0)
	{
		printf("No CUDA devices found.\n");
		return;
	}
	
	for (i = 0; i < num_devs; i++)
	{
		cudaDeviceProp dev_prop;
		cudaGetDeviceProperties(&dev_prop, i);
		
		printf("Device name: %s\n", dev_prop.name);
		printf("Compute Capability: %d.%d\n", dev_prop.major, dev_prop.minor);
		cudaDriverGetVersion(&driverVersion );
		cudaRuntimeGetVersion(&runtimeVersion );
		printf("Driver Version: %d.%d and Runtime Version: %d.%d\n", driverVersion /1000, (driverVersion %100) /10 , runtimeVersion / 1000, (runtimeVersion % 100) / 10);
		printf("SMs: %d\n", dev_prop.multiProcessorCount);
		printf("Global memory: %u in kilobytes\n", dev_prop.totalGlobalMem/1024);
		printf("Constant memory: %u in kilobytes\n", dev_prop.totalConstMem/1024);
		printf("Shared memory per block: %u in kilobytes\n", dev_prop.sharedMemPerBlock/1024);
	}
}

int main()
{
	cuinfo_print_devinfo();
	return 0;
}
