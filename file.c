#include "muhfile.h"

#define MAX_NAME 255


int main(){

	FILE *fp;
	char buff[BUFFSIZE];
	char buff2[BUFFSIZE];	//DEL
    int i, j;				//counters
    int m, n, k;			// matrix dimensions. n columns of A and rows of B
	int temp;				// filling the file
	srand(time(NULL));
	char filename[MAX_NAME];
	
	printf("Enter filename for output: ");
	fgets(filename, MAX_NAME, stdin);

	printf("Opening %s for writing\n", filename);
	fp = fopen(filename,"w");
	
	printf("Enter m, n, k: ");
	scanf("%d %d %d", &m, &n, &k);

	printf("Filling Matricies\n");
	matfill(fp, m, n, k);

	printf("Closing %s\n", filename);
	fclose(fp);

	printf("Opening %s for reading\n", filename);
	fp = fopen(filename,"r");


	while(fgets(buff, BUFFSIZE,fp))
	printf("%s",buff);

	printf("Closing %s\n", filename);
	fclose(fp);
}
