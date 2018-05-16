#include <stdio.h>
#include <stdlib.h>

int is_a_solution(int a[], int k, int day[], int fine[], int num_task) {
	/* You can modify from here */

	/* You can modify to here */
}

void process_solution(int a[], int day[], int fine[], int num_task, int order[], int *min) {
	/* You can modify from here */

	/* You can modify to here */
}


void construct_candidates(int a[], int k,  int day[], int fine[], int num_task, int c[], int *ncandidates) {
	/* You can modify from here */

	/* You can modify to here */
}


void backtrack(int a[], int k, int num_task, int day[], int fine[], int order[], int *min) {
	/* You can modify from here */

	/* You can modify to here */
}


int calculate_fine(int day[], int fine[], int num_task, int order[] ) {
	/* You can modify from here */

	/* You can modify to here */

}

int main(void) {
	
	int num_case;
	int num_task;
	int *day;
	int *a;
	int *fine;
	int *order;
	int i,j;
	int min;

	scanf("%d",&num_case);

	for(i=0;i<num_case;i++) {
		scanf("%d",&num_task);
		day = (int*)calloc(num_task,sizeof(int));
		fine = (int*)calloc(num_task,sizeof(int));
		order = (int*)calloc(num_task,sizeof(int));
		a = (int*)calloc(num_task,sizeof(int));
		for(j=0;j<num_task;j++) {
			scanf("%d %d",&day[j],&fine[j]);
			order[j]=j;
		}
		min=calculate_fine(day,fine,num_task,order);
		backtrack(a, 0, num_task, day, fine, order, &min);
		if (i>0) printf("\n");
		for(j=0;j<num_task;j++) {
			printf("%d",order[j]+1);
			if (j<num_task-1) printf(" ");
		}
		printf("\n");
		free(day);
		free(fine);
		free(order);
	} 
	return 0;
}
