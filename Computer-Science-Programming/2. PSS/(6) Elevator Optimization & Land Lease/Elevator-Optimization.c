#include <stdio.h>
#include <stdlib.h>
#define SIZE 20 
#define SIZE_K (SIZE-1)*SIZE/2

int is_a_solution(char a[], int k) {
	return (k == SIZE_K);	// �ܰ谡 SIZE_K��ŭ ������ ��츦 �Ǵ���.
}

void process_solution(char **res_case, char **res) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			res[i][j] = res_case[i][j];
	}	// main �Լ��� return �Ǵ� res��� ������ �迭�� ���ǿ� �´� ������ �迭�� ������.
}


void construct_candidates(char a[], char c[], int *ncandidates) {
	c[0] = 'W';
	c[1] = 'T';
	c[2] = 'L';
	*ncandidates = 3;	// �� �ܰ踶�� �ĺ��� 'W', 'L', 'T'�� 3���� ����.
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
	return score;	// �� ���� ��� ��� ����� ���� ���(wtl�� ����), �̿� ���� �� ���� score�� ����Ͽ� ������.
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
		/* a(������ �迭)�� res_case(������ �迭)�� ����, res_case[][]�� ��� �׸��� ����('X') */
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


		/* res_case�� �� ���� ���� ��� �� ���� */
		for (j = 0; j < SIZE; j++) {
			score[j] = calculate_score(res_case[j], w_s, t_s, l_s);
		}

		/* ������ �� ���� ����(score)�� ������������ ����(score_sort) */
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

		/* e�� ���� d��° ���� ���� ������ minmax�� ��, ���ǿ� �´� ��� ���� �� process_solution. */
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
			backtrack(a, k, w_s, t_s, l_s, res, d, e, minmax);	// �ܰ谡 ���� �������� ���� ���, backtrack�� ����Ѵ�.
		}
	}
}


int main(void) {

	int w_s, t_s, l_s, d, e;
	char **res, **res_case1, **res_case2;
	char a[SIZE_K], ex[SIZE], *rot;
	int i, j, k, l, num, count = 0, score1[SIZE], score2[SIZE], score_sort1[SIZE], score_sort2[SIZE], check1[SIZE], check2[SIZE];
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
	res = (char**)calloc(SIZE, sizeof(char*));
	for (i = 0; i < SIZE; i++) {
		res[i] = (char*)calloc(SIZE, sizeof(char));
	}

	scanf_s("%d %d %d %d %d", &w_s, &t_s, &l_s, &d, &e);

	/* Ư�� ���� 1�� ��� �̸� ���� */
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

	/* Ư�� ���� 2�� ��� �̸� ���� */
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

	/* Ư�� ���� 3�� ��� �̸� ���� */
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

		//���� ���
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


	/* Ư�� ���� 4�� ��� �̸� ���� */
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

		//���� ���
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

	/* ������ ���, backtracking ��� ��� */
	else {
		for (i = 1; i < SIZE; i++)
			ex[i] = 'T';
		ex[0] = 'X';

		minmax = calculate_score(ex, w_s, t_s, l_s);
		backtrack(a, 0, w_s, t_s, l_s, res, d, e, &minmax);
	}

	/* ��� */
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			printf("%c ", res[i][j]);
		printf("\n");
	}
	return 0;
}
