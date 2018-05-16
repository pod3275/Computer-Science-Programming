#include <stdio.h>
#include <stdlib.h>
#define SIZE 20 

int is_a_solution(char a[], int k) {
	return (k == 190);
}

void process_solution(char res_case[][], char res[][]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			res[i][j] = res_case[i][j];
	}
}


void construct_candidates(char a[], char c[], int *ncandidates) {
	c[0] = 'W';
	c[1] = 'T';
	c[2] = 'L';
	*ncandidates = 3;
}


void backtrack(char a[], int k, int w_s, int t_s, int l_s, char res[][], int d, int e, int *minmax) {
	char *c = calloc(3, sizeof(char)); 
	char res_case[SIZE][SIZE + 1];
	int score[SIZE], score_sort[SIZE], mid, max;
	int ncandidates, i, j=2, n=0, l=0, m=0;

	if (is_a_solution(a, k)) {
		/* a를 res_case에 저장하기, res_case[i][]를 정리하기 : 'X' */
		for (j = 1; j < SIZE; j++) {
			for (n = 0; j + n < SIZE; n++) {
				res_case[l][j + n] = a[m];
				if (res_case[l][j + n] = 'T')
					res_case[j + n][l] = 'T';
				else if (res_case[l][j + n] = 'W')
					res_case[j + n][l] = 'L';
				else if (res_case[l][j + n] = 'L')
					res_case[j + n][l] = 'W';
				m++;
			}
			l++;
		}
		for (j = 0; j < 20; j++) {
			res_case[j][j] = 'X';
		}

		/* res_case의 각 팀의 점수 저장하기 */
		for (j = 0; j < SIZE; j++) {
			score[j] = calculate_score(res_case[j], w_s, t_s, l_s);
		}
		
		/* e에 따라 res_case의 d번째 팀의 점수 minmax와 비교하기 */
		mid = 0;
		max = 100;

		for (j = 0; j < SIZE; j++) {
			for (l = 0; l < SIZE; l++) {
				if (mid <= score[l] && score[l] <= max) {
					mid = score[l];
				}
			}
			max = mid;
			score_sort[j] = mid;
			mid = 0;
		}

		if (e == 0) {
			if (minmax > score_sort[d - 1]) {
				minmax = score_sort[d - 1];
				process_solution(res_case, res);
			}
		}
		else if (e == 1) {
			if (minmax < score_sort[d - 1]) {
				minmax = score_sort[d - 1];
				process_solution(res_case, res);
			}
		}
	}

	else {
		k = k + 1;
		construct_candidates(a, c, &ncandidates);
		for (i = 0; i < ncandidates; i++) {
			a[k - 1] = c[i];
			backtrack(a, k, w_s, t_s, l_s, res[][], d, e, &minmax);
		}
	} 
}


int calculate_score(char wtl[], int w_s, int t_s, int l_s) {
	int score = 0, i;
	for (i = 0; i < SIZE; i++) {
		if (wtl[i] == 'W')
			score += w_s;
		else if (wtl[i] == 'T')
			score += t_s;
		else if (wtl[i] = 'L')
			score += l_s;
		else if (wtl[i] = 'X')
			score += 0;
	}
	return score;
} 

int main(void) {

	int w_s, t_s, l_s, d, e;
	char res[SIZE][SIZE+1];
	char a[190], ex[SIZE];
	int i, j;
	int minmax;

	scanf("%d %d %d %d %d", &w_s, &t_s, &l_s, &d, &e);
	for (i = 0; i < SIZE; i++)
		ex[i] = 'T';

	minmax = calculate_score(ex, w_s, t_s, l_s);
	backtrack(a, 0, w_s, t_s, l_s, res, d, e, &minmax);


	if (i>0) printf("\n");
	for (j = 0; j<num_task; j++) {
		printf("%d", order[j] + 1);
		if (j<num_task - 1) printf(" ");
	}
	printf("\n");
	free(day);
	free(fine);
	free(order);
	return 0;
}
