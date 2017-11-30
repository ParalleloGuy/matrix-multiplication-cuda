#include "muhfile.h"

#define MAX_NAME 255
/*
void usermat(FILE *fp, int m, int n);
*/

int main(){

	FILE *fp;
	char buff[BUFFSIZE];
	char buff2[BUFFSIZE];	//DEL
    int i, j;				//counters
    int m, n, k;			// matrix dimensions. n columns of A and rows of B
	int temp;				// filling the file
	srand(time(NULL));
	char filename[MAX_NAME];
	char *p;				// for removing \n from filename after input
	char dec;
	char dump;
	
	// user input 	
	printf("Would you like to have your matricies generated randomly(1) or");
	printf(" enter them manually(0)? ");
	dec = getchar() - '0';

while((dump = getchar()) != '\n' && dec != EOF){} // for clearing inbuff


	printf("Enter filename for output: ");
	fgets(filename, MAX_NAME, stdin);

	if((p = strchr(filename, '\n')) != NULL){
		*p = '\0'; //remove newline
	}

	printf("Opening %s for writing\n", filename);
	fp = fopen(filename,"w");

	printf("Enter m, n, k: ");
	scanf("%d %d %d", &m, &n, &k);

	if(dec){	
	
// fill matrices
		printf("Filling Matricies\n");
		matfillrand(fp, m, n, k);
// file stuff
// PRINT FILE
		}else{
			matfilluser(fp, m, n, k);
		}

		printf("Closing %s\n", filename);
		fclose(fp);

		printf("Opening %s for reading\n", filename);
		fp = fopen(filename,"r");
	




		while(fgets(buff, BUFFSIZE,fp))
			printf("%s",buff);

		printf("Closing %s\n", filename);
		fclose(fp);
}

/*

void matfilluser(FILE *fp, int m, int n){
	int i, j, temp;

	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			printf("[%d][%d]:", i, j);
			scanf("%d", &temp);
			fprintf(fp,"%6d", temp);
		}
		fprintf(fp,"\n");
	}
}
*/
