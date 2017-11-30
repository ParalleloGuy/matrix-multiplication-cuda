#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define BLOCK_SIZE	16
#define BUFFSIZE	255

__global__ void gpu_matrix_mult(int *a, int *b, int *c, int m, int n, int k);

void matfill(int *host_arr, int m, int n);
void matprint(int *host_arr, int m, int n);
void matfilefill(FILE *ofp, int *host_arr_a, int *host_arr_b, int m, int n, int k);
void matfilefillfunc(FILE *ofp, int *host_arr, int m, int n);


/*********************************
gpu_matrix_mult - Dot product of two matrix

&a GPU points to matrix m*n, &b GPU points to matrix n*k
&c GPU points to matrix m*k

dim3 dimGrid((k + BLOCK_SIZE - 1) / BLOCK_SIZE, (m + BLOCK_SIZE - 1) / BLOCK_SIZE);
dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);

*********************************/

__global__ void gpu_matrix_mult(int *a, int *b, int *c, int m, int n, int k){

//	printf("funcp\n");
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int sum = 0;
	int i = 0;

	if(col < k && row < m){
		for(i = 0; i < n; i++){
			sum += a[row * n + i] * b[i * k + col];
//			printf("derp ");
//			printf("sum = %d\n", sum);
		}
		c[row* k + col] = sum;
//		printf("sum = %d\n");
	}
}




// Random matfill
void matfill(int *host_arr, int m, int n){
	int i, j;
		for(i = 0;i < m; ++i){
			for(j = 0;j < n; ++j){
				host_arr[i * n + j] = rand() % 512;
//                printf("%d\n",host_arr[i * n + j]);
			}
		}	
}

void matprint(int *host_arr, int m, int n){
	int i, j;

	for(i = 0;i < m; ++i){
		for(j = 0;j < n; ++j){
		//	host_arr[i * n + j] = rand() % 1024;
               printf("%8d ",host_arr[i * n + j]);
		}
		printf("\n");
	}	
}

void fillmatfromfile(FILE * fp, int *host_arr, int m, int n){
	int i, j;
	int temp;
	//char buff[BUFFSIZE];
		for(i = 0;i < m; ++i){
			for(j = 0;j < n; ++j){
				fscanf(fp, "%d", &temp);
				host_arr[i * n + j] = temp;
			}
//		printf("\n");
		}	
}


void matfilefill(FILE *ofp, int *host_arr_a, int *host_arr_b, int m, int n, int k){
	//int i, j, temp;

	fprintf(ofp, "%d %d %d\n\n", m, n, k);

	matfilefillfunc(ofp, host_arr_a, m, n);
	matfilefillfunc(ofp, host_arr_b, n, k);
}


void matfilefillfunc(FILE *ofp, int *host_arr, int m, int n){
	int i, j, temp;
	for(i = 0;i < m; ++i){
		for(j = 0;j < n; ++j){
//			printf("innerloop start yea k thanks bye\n");
			temp = rand() % 512;
			host_arr[i * n + j] = temp;
			fprintf(ofp, "%8d ", temp);
//			printf("%d\n", host_arr[i * n + j]);
		}
		fprintf(ofp, "\n");
	}	
		fprintf(ofp, "\n");
}


