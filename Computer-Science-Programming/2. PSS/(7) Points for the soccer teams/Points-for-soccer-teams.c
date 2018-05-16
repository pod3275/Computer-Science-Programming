#include <stdio.h>
#include <stdlib.h>
#define SIZE 20 
#define SIZE_K (SIZE-1)*SIZE/2

int is_a_solution(char a[], int k) {
	return (k == SIZE_K);	// 단계가 SIZE_K만큼 도달한 경우를 판단함.
}

void process_solution(char **res_case, char **res) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			res[i][j] = res_case[i][j];
	}	// main 함수에 return 되는 res라는 이차원 배열에 조건에 맞는 이차원 배열을 복사함.
}


void construct_candidates(char a[], char c[], int *ncandidates) {
	c[0] = 'W';
	c[1] = 'T';
	c[2] = 'L';
	*ncandidates = 3;	// 각 단계마다 후보는 'W', 'L', 'T'로 3개가 있음.
}

int calculate_score(char wtl[], int w_s, int t_s, int l_s) {
	int score = 0, i;
	for (i = 0; i < SIZE; i++) {
		if (wtl[i] == 'W')
			score += w_s;
		else if (wtl[i] == 'T')
			score += t_s;
		else if (wtl[i] == 'L')
			score += l_s;
	}
	return score;	// 한 팀의 모든 경기 결과가 나온 경우(wtl에 저장), 이에 따라 그 팀의 score를 계산하여 리턴함.
}

void backtrack(char a[], int k, int w_s, int t_s, int l_s, char **res, int d, int e, int *minmax) {
	char *c = calloc(3, sizeof(char));
	char **res_case;
	int score[SIZE], score_sort[SIZE], mid, max, check[SIZE];
	int ncandidates, i, j, n, l = 0, m = 0, num;
	for (i = 0; i < SIZE; i++) check[i] = 0;


	if (is_a_solution(a, k)) {
		res_case = (char**)calloc(SIZE, sizeof(char*));
		for (i = 0; i < SIZE; i++) {
			res_case[i] = (char*)calloc(SIZE, sizeof(char));
		}
		/* a(일차원 배열)를 res_case(이차원 배열)에 저장, res_case[][]의 모든 항목을 설정('X') */
		for (j = 1; j < SIZE; j++) {
			for (n = 0; j + n < SIZE; n++) {
				res_case[l][j + n] = a[m];
				if (res_case[l][j + n] == 'T')
					res_case[j + n][l] = 'T';
				else if (res_case[l][j + n] == 'W')
					res_case[j + n][l] = 'L';
				else if (res_case[l][j + n] == 'L')
					res_case[j + n][l] = 'W';
				m++;
			}
			l++;
		}
		for (j = 0; j < SIZE; j++) {
			res_case[j][j] = 'X';
		}


		/* res_case의 각 팀의 점수 계산 및 저장 */
		for (j = 0; j < SIZE; j++) {
			score[j] = calculate_score(res_case[j], w_s, t_s, l_s);
		}

		/* 저장한 각 팀의 점수(score)를 오름차순으로 저장(score_sort) */
		mid = 0;
		max = 100;

		for (j = 0; j < SIZE; j++) {
			for (l = 0; l < SIZE; l++) {
				if (mid <= score[l] && check[l] == 0) {
					mid = score[l];
					num = l;
				}
			}
			check[num] = 1;
			score_sort[j] = mid;
			mid = 0;
		}

		/* e에 따라 d번째 높은 팀의 점수와 minmax를 비교, 조건에 맞는 경우 저장 및 process_solution. */
		if (e == 0) {
			if (*minmax >= score_sort[d - 1]) {
				*minmax = score_sort[d - 1];
				process_solution(res_case, res);
			}
		}

		else if (e == 1) {
			if (*minmax <= score_sort[d - 1]) {
				*minmax = score_sort[d - 1];
				process_solution(res_case, res);
			}
		}
	}

	else {
		k = k + 1;
		construct_candidates(a, c, &ncandidates);
		for (i = 0; i < ncandidates; i++) {
			a[k - 1] = c[i];
			backtrack(a, k, w_s, t_s, l_s, res, d, e, minmax);	// 단계가 아직 도달하지 않은 경우, backtrack을 계속한다.
		}
	}
}


int main(void) {

	int w_s, t_s, l_s, d, e;
	char **res, **res_case1, **res_case2;
	char a[SIZE_K], ex[SIZE], *rot;
	int i, j, k,l,  num, count=0, score1[SIZE], score2[SIZE], score_sort1[SIZE], score_sort2[SIZE], check1[SIZE], check2[SIZE];
	int minmax, mid, max;

	for (i = 0; i < SIZE; i++) {
		check1[i] = 0; check2[i] = 0;
	}

	res_case1 = (char**)calloc(SIZE, sizeof(char*));
	for (i = 0; i < SIZE; i++) {
		res_case1[i] = (char*)calloc(SIZE, sizeof(char));
	}
	res_case2 = (char**)calloc(SIZE, sizeof(char*));
	for (i = 0; i < SIZE; i++) {
		res_case2[i] = (char*)calloc(SIZE, sizeof(char));
	}
	res = (char**)calloc(SIZE,sizeof(char*));
	for (i = 0; i < SIZE; i++) {
		res[i] = (char*)calloc(SIZE,sizeof(char));
	}

	scanf_s("%d %d %d %d %d", &w_s, &t_s, &l_s, &d, &e);

	/* 특이 조건 1의 경우 미리 설정 */
	if ((t_s >= w_s && t_s >= l_s && e == 1) || (t_s <= w_s && t_s <= l_s && e == 0)) {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (i == j)
					res[i][j] = 'X';
				else
					res[i][j] = 'T';
			}
		}
	}

	/* 특이 조건 2의 경우 미리 설정 */
	else if ((t_s >= w_s && t_s >= l_s && e == 0) || (t_s <= w_s && t_s <= l_s && e == 1)) {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (i == j)
					res[i][j] = 'X';
				else if (i < j)
					res[i][j] = 'W';
				else
					res[i][j] = 'L';
			}
		}
	}

	/* 특이 조건 3의 경우 미리 설정 */
	else if ((t_s < w_s && t_s > l_s && e == 1) || (t_s > w_s && t_s < l_s && e == 0)) {
		rot = (char*)calloc(d - 1, sizeof(char));
		if ((d - 1) % 2 == 0) {
			for (i = 0; i < (d - 1) / 2; i++) rot[i] = 'L';
			for (i = (d - 1) / 2; i < d - 1; i++) rot[i] = 'W';
		}
		if ((d - 1) % 2 == 1) {
			for (i = 0; i < (d - 2) / 2; i++) rot[i] = 'L';
			rot[(d - 2) / 2] = 'T';
			for (i = (d - 2) / 2 + 1; i < d - 1; i++) rot[i] = 'W';
		}

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (i > j) res_case1[i][j] = 'L';
				else if (i < j) res_case1[i][j] = 'W';
				else res_case1[i][j] = 'X';
			}
		}

		for (i = 0; i < d; i++) {
			for (j = 1; j < d; j++) {
				res_case1[i][(i + j) % d] = rot[count];
				count++;
			}
			count = 0;
		}

		for (i = 0; i < d - 1; i++) rot[i] = 'T';
		
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (i > j) res_case2[i][j] = 'L';
				else if (i < j) res_case2[i][j] = 'W';
				else res_case2[i][j] = 'X';
			}
		}

		for (i = 0; i < d; i++) {
			for (j = 1; j < d; j++) {
				res_case2[i][(i + j) % d] = rot[count];
				count++;
			}
			count = 0;
		}

		//점수 계산
		for (j = 0; j < SIZE; j++) {
			score1[j] = calculate_score(res_case1[j], w_s, t_s, l_s);
		}

		mid = 0; max = 10;

		for (j = 0; j < SIZE; j++) {
			for (l = 0; l < SIZE; l++) {
				if (mid <= score1[l] && check1[l] == 0) {
					mid = score1[l];
					num = l;
				}
			}
			check1[num] = 1;
			score_sort1[j] = mid;
			mid = 0;
		}


		for (j = 0; j < SIZE; j++) {
			score2[j] = calculate_score(res_case1[j], w_s, t_s, l_s);
		}

		mid = 0;
		max = 100;

		for (j = 0; j < SIZE; j++) {
			for (l = 0; l < SIZE; l++) {
				if (mid <= score2[l] && check2[l] == 0) {
					mid = score2[l];
					num = l;
				}
			}
			check2[num] = 1;
			score_sort2[j] = mid;
			mid = 0;
		}


		if (e == 0) {
			if (score_sort2[d - 1] >= score_sort1[d - 1]) {
				process_solution(res_case1, res);
			}
			else process_solution(res_case2, res);
		}

		else if (e == 1) {
			if (score_sort2[d - 1] >= score_sort1[d - 1]) {
				process_solution(res_case2, res);
			}
			else process_solution(res_case1, res);
		}
	}


	/* 특이 조건 4의 경우 미리 설정 */
	else if (t_s < w_s && t_s > l_s && e == 0 || (t_s > w_s && t_s < l_s && e == 1)) {
		rot = (char*)calloc(d - 1, sizeof(char));
		if ((d - 1) % 2 == 0) {
			for (i = 0; i < (d - 1) / 2; i++) rot[i] = 'W';
			for (i = (d - 1) / 2; i < d - 1; i++) rot[i] = 'L';
		}
		if ((d - 1) % 2 == 1) {
			for (i = 0; i < (d - 2) / 2; i++) rot[i] = 'W';
			rot[(d - 2) / 2] = 'T';
			for (i = (d - 2) / 2 + 1; i < d - 1; i++) rot[i] = 'L';
		}

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (i > j) res_case1[i][j] = 'W';
				else if (i < j) res_case1[i][j] = 'L';
				else res_case1[i][j] = 'X';
			}
		}

		for (i = 0; i < d; i++) {
			for (j = 1; j < d; j++) {
				res_case1[i][(i + j) % d] = rot[count];
				count++;
			}
			count = 0;
		}

		for (i = 0; i < d - 1; i++) rot[i] = 'T';

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (i > j) res_case2[i][j] = 'W';
				else if (i < j) res_case2[i][j] = 'L';
				else res_case2[i][j] = 'X';
			}
		}

		for (i = 0; i < d; i++) {
			for (j = 1; j < d; j++) {
				res_case2[i][(i + j) % d] = rot[count];
				count++;
			}
			count = 0;
		}

		//점수 계산
		for (j = 0; j < SIZE; j++) {
			score1[j] = calculate_score(res_case1[j], w_s, t_s, l_s);
		}

		mid = 0;
		max = 100;

		for (j = 0; j < SIZE; j++) {
			for (l = 0; l < SIZE; l++) {
				if (mid <= score1[l] && check1[l] == 0) {
					mid = score1[l];
					num = l;
				}
			}
			check1[num] = 1;
			score_sort1[j] = mid;
			mid = 0;
		}


		for (j = 0; j < SIZE; j++) {
			score2[j] = calculate_score(res_case1[j], w_s, t_s, l_s);
		}

		mid = 0;
		max = 100;

		for (j = 0; j < SIZE; j++) {
			for (l = 0; l < SIZE; l++) {
				if (mid <= score2[l] && check2[l] == 0) {
					mid = score2[l];
					num = l;
				}
			}
			check2[num] = 1;
			score_sort2[j] = mid;
			mid = 0;
		}


		if (e == 0) {
			if (score_sort2[d - 1] >= score_sort1[d - 1]) {
				process_solution(res_case1, res);
			}
			else process_solution(res_case2, res);
		}

		else if (e == 1) {
			if (score_sort2[d - 1] >= score_sort1[d - 1]) {
				process_solution(res_case2, res);
			}
			else process_solution(res_case1, res);
		}
	}

	/* 나머지 경우, backtracking 기법 사용 */
	else {
		for (i = 1; i < SIZE; i++)
			ex[i] = 'T';
		ex[0] = 'X';

		minmax = calculate_score(ex, w_s, t_s, l_s);
		backtrack(a, 0, w_s, t_s, l_s, res, d, e, &minmax);
	}

	/* 출력 */
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			printf("%c ", res[i][j]);
		printf("\n");
	}
	return 0;
}
