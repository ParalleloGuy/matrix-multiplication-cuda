#include "matlib.h"
#include "file/muhfile.h"


int main(int argc, char const *argv[]){

	// dimensions for matrices. m*n . n*k
	int m, n, k;
	srand(time(NULL));
	int dec = 0;
	float elapsed_time;
	FILE *fp;// file pointer, used for both in and out since they dont overlap
	char filename[BUFFSIZE];// storing filename
	char *p; // removing trailing \n in filename input
	char *fileerror;

	
	int *host_a, *host_b, *host_c;	//  host array pointers
	int *dev_a, *dev_b, *dev_c;		//	device array pointers

	printf("Would you like to load your arrays from a file(1) or have them");
	printf(" generated(0)? ");
	dec = getchar() - '0';
	printf("dec = %d", dec);

	printf("\n");

	if(dec){
		while((dec = getchar()) != '\n' && dec != EOF){} // for clearing inbuff
		//char buff[BUFFSIZE];	// for reading in lines to be parsed

		printf("Enter filename for input: ");
		fgets(filename, BUFFSIZE ,stdin);				// read in filename
		//FILENAME FIXER
        if((p = strchr(filename, '\n')) != NULL){		// fix filename
			printf("in the filenam fixer\n");
            *p = '\0';								
        }

		printf("Opening %s for reading\n", filename);	//open filename
		fp = fopen(filename,"r"); 

//;asdilf;lasdfk;sdfjlak;sdfjlalk;asdfjasdfkl;jasdfkl;j





		printf("before the while\n");

		//GET MATRICES DIMENSIONS
	    fscanf(fp, "%d %d %d", &m, &n, &k);
		newline();


//CONSOLIDATE THESE MALLOCS TO BEFORE THE IF ELSE IF POSSIBLE
		cudaMallocHost((void **) &host_a, sizeof(int) * m * n); // first array
		cudaMallocHost((void **) &host_b, sizeof(int) * n * k); // first array

		fillmatfromfile(fp, host_a, m, n);
		fillmatfromfile(fp, host_b, n, k);
		
		printf("CLOsinG TiME\n");
		fclose(fp);


/* 
THIS IS THE PARTS YOURE WORKING ON
read in the matrices and store them in the arrays
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
*/

	}else{

//	    printf("Would you you like to save the randomly generated matrices");
//	    printf(" to a file?\n");
//		fgets(filename, BUFFSIZE ,stdin);

/*
	1. store randomly generated matricies in a file
	2. 
	3. add control structure
*/
		// *** can you clean up the flow? this is in both if and else. 

	    printf("please type in array dimensions m, n, and k: ");
	    scanf("%d %d %d", &m, &n, &k);

// YOU NEED TO  MOVE THIS TOBEFORE THE IF ELSE STATEMENT!!! THIS IS NOT CLEAN!!

		cudaMallocHost((void **) &host_a, sizeof(int) * m * n); // first array
		cudaMallocHost((void **) &host_b, sizeof(int) * n * k); // second array
		cudaMallocHost((void **) &host_c, sizeof(int) * m * k); // product

// CHANGE VARIABLe; Clean this up
		while((dec = getchar()) != '\n' && dec != EOF){} // for clearing inbuff
	
		// FILL MATRICES AND FILE

			printf("Enter filename for saving: ");
			fileerror = fgets(filename, BUFFSIZE ,stdin);
			if(fileerror == NULL){
				printf("fileerror = NULL; YHOU FUHAILED!\n");
			}
			//FILENAME FIXER
			if((p = strchr(filename, '\n')) != NULL){ //remove newline
				printf("in the filenam fixer\n");
				*p = '\0';								
			}

			printf("Opening %s for writing\n", filename);
			fp = fopen(filename,"w");
			printf("Opened %s for writing\n", filename);
		
	// FILLs Matrices and stores them in a file
			matfilefill(fp, host_a, host_b, m, n, k);
			printf("Matrices filled and output to file %s\n", filename);
			fclose(fp);


		// PRINT
		matprint(host_a, m, n);
		printf("\n");
		matprint(host_b, n, k);
		printf("\n");
/*
		if(matprint(host_a, m, n)){
			printf("Matrix A filled\n");
		}else{
			printf("DANGER DANGER!!!! NO MATRIX IN THE FLUX RAY!!\n");
		}

		if(matprint(host_b, n, k)){
			printf("Matrix B filled\n");
		
		}else{
			printf("DANGER DANGER!!!! NO MATRIX IN THE QUANTUM CARBURETOR!!\n");
		}
*/
	}

printf("OOT OF THE IF?ELSE\n");

	//SEG FAULT!! YOU NEED TO GO BACK TO THE : BLURG



	// for measuring time	
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// start timer
	cudaEventRecord(start, 0);
	
	
	// Allocate space for arrays on DEVICE
	cudaMalloc((void **) &dev_a, sizeof(int) * m * n); // first array
	cudaMalloc((void **) &dev_b, sizeof(int) * n * k); // second array
	cudaMalloc((void **) &dev_c, sizeof(int) * m * k); // product of arrays

	// Copy matricies from HOST to DEVICE
	cudaMemcpy(dev_a, host_a, sizeof(int) * m * n, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, host_b, sizeof(int) * n * k, cudaMemcpyHostToDevice);

	// Preparind dimGrid and dimBlock for use in gpu_matrix_mult function
	unsigned int grid_rows = (m + BLOCK_SIZE - 1) / BLOCK_SIZE; 
	unsigned int grid_cols = (k + BLOCK_SIZE - 1) / BLOCK_SIZE; 
	dim3 dimGrid(grid_cols, grid_rows);
	dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);

	// launch that fam
	gpu_matrix_mult<<<dimGrid, dimBlock>>>(dev_a, dev_b, dev_c, m, n, k);

	// transfer results to host
	cudaMemcpy(host_c, dev_c, sizeof(int) * m * k, cudaMemcpyDeviceToHost);

	// end timer
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsed_time, start, stop);
	
//	printf("Matricies multiplied: %d * %d . %d * %d\n", m, n, ,n, k);
//	printf("abbagamba\n");

	printf("World Domination Computation Completed Professor\n");
	matprint(host_c, m, k);
	printf("Time elapsed: %f\n", elapsed_time);

	// Free the mmeory so it isnt banished into eternity
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
	printf("cudaFreed\n");
	cudaFreeHost(host_a);
	printf("cudaFreedHost\n");
	cudaFreeHost(host_b);
	cudaFreeHost(host_c);

	printf("Program OVER!\n");
}
