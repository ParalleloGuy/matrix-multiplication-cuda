#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFSIZE 255

void matfillrand(FILE *fp, int m, int n, int k);
void matfilluser(FILE *fp, int m, int n, int k);
void newline();


/*******************************
matfillrand - randomly fills 2 matrices
fp - pointer to output file

matrices will be  m*n  and  n*k
*******************************/

void matfillrand(FILE *fp, int m, int n, int k){
	int i, j, temp;

	fprintf(fp, "%d %d %d", m, n, k);
	fprintf(fp,"\n");

	// Fill Matrix 1
	for(i = 0;i < m; ++i){		// for filling file with random matricies
		for(j = 0;j < n; ++j){	// row
			temp = rand() % 512;
			fprintf(fp,"%6d ", temp); // puts temp in file
		}
		fprintf(fp,"\n");
	}

	fprintf(fp,"\n");

	// Fill Matrix 2
	for(i = 0;i < n; ++i){		// for filling file with random matricies
		for(j = 0;j < k; ++j){	// row
			temp = rand() % 512;// column
			fprintf(fp,"%6d ", temp); 
		}
		fprintf(fp,"\n");
	}
}


/*******************************
matfilluser - allows the user to enter inputs for the matrix

fp - pointer to output file
m  - rows
n  - columns
*******************************/

void matfilluser(FILE *fp, int m, int n, int k){ 
    int i, j, temp;

	fprintf(fp,"%d %d %d\n", m, n, k);

	printf("\n");
	printf("Matrix 1:\n");

	// fill matrix 1
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("[%d][%d]:", i, j);
            scanf("%d", &temp);
            fprintf(fp,"%6d", temp);
        }
        fprintf(fp,"\n");
    }

	fprintf(fp,"\n");

	printf("\n");
	printf("Matrix 2:\n");

	// fill matrix 2
	for(i = 0; i < n; i++){
		for(j = 0; j < k; j++){
			printf("[%d][%d]:", i, j);
			scanf("%d", &temp);
			fprintf(fp,"%6d", temp);
		}
		fprintf(fp,"\n");
	}
}
          
void newline(){
	printf("\n");
}
