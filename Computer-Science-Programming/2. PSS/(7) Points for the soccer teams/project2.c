#include <stdio.h>
#define SIZE 20 

void main(void) {
	int i,j;
	int valid;
	char input;
	char result[SIZE][SIZE+1];

	for (i=0; i<SIZE; i++) {
		scanf("%s",result[i]);
//		for (j=0; j<SIZE; j++) {
//			result[i][j]=getchar();		
//
//		}
//		getchar();
	}

	for (i=0; i<SIZE; i++) {
		for (j=0; j<SIZE; j++) {
			printf("%c",result[i][j]);
		}
		printf("\n");
	}
	for (i=0; i<SIZE; i++) {
		for (j=0; j<SIZE; j++) {
			if (i!=j) {
			valid=1;	
				if (result[i][j]=='W') {
					if (result[j][i]!='L') {
						valid=0;		
					}
				} else if (result[i][j]=='L') {
					if (result[j][i]!='W') {
						valid=0;		
					}
				} else if (result[i][j]=='T') {
					if (result[j][i]!='T') {
						valid=0;		
					}
				} else {
					valid=0;
				}

				if (valid==0) {
					printf("Your game results are invalid!\n");
					return;
				}
			}
		}
	}

	printf("Your game results are valid!\n");
	return;
}
