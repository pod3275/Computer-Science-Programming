#include <stdio.h>
#include <stdlib.h>

/* You can modify from here */

int test_cases(int X, int Y, int n, int *D, int **matrix) {
	int *num_count, num, min, max, inf = 0, i, j = 0, k; 
	/* num_const : ������ �ߺ��� ���� ����, num : �ʱ�ȭ(�� ������ �밢�� ���� matrix�� �Է�)�ϴ� �������� ���̴� ����
	min, max : �밢�� ������ �� �߿� ���̴� ����, inf : matrix ������ infeasible�� ��츦 �Ǵ��ϴ� ����, i, j, k : count vairable*/

	num_count = (int*)calloc(Y - X + 1, sizeof(int));


	//num_count�� matrix �ʱ�ȭ(matrix���� �� �� ���� �밢�� �� �Է�)
	for (i = 0; i < Y - X + 1; i++) {
		num_count[i] = 0;
	}

	for (i = 0; i < n; i++) {
		matrix[n - j - 1][j] = D[i];
		j++;
	}

	for (i = 0; i <= n - 1; i++) {
		num = matrix[n - i - 1][i];
		num_count[num - X] = 1;
	}

	num_count[0] = 1;
	num_count[Y - X] = 1;

	matrix[0][0] = X;
	matrix[n - 1][n - 1] = Y;


	//ũ�� Ȥ�� �Է� ������ infeasible�� ���, 0�� �����ϰ� �Լ��� ����.
	if (n*n > Y - X + 1)
		return 0;
	for (i = 0; i < n; i++) {
		if (D[i] <= X || D[i] >= Y)
			return 0;
	}


	//�밢�� ���� ���� ���� ������ ���� ������ ���� ���� �Է�.
	for (k = 0; k < n - 2; k++) {
		for (i = 0; i <= n - k - 2; i++) {
			if (matrix[n - i - k - 1][i] < matrix[n - i - k - 2][i + 1])
				min = matrix[n - i - k - 1][i];
			else
				min = matrix[n - i - k - 2][i + 1];
			while (1) {
				if (min == X) {
					inf = 1;
					break;
				}
				min--;
				if (num_count[min - X] == 0) {
					matrix[n - i - k - 2][i] = min;
					num_count[min - X] = 1;
					break;
				}
			}
		}
	}
	if (inf == 1) return 0; //��� ������ �Է��� ������ ���, 0�� ����.


	//�밢�� ���� ������ �Ʒ��� ������ ���� ������ ���� ���� �Է�.
	for (k = 0; k < n - 2; k++) {
		for (i = 0; i <= n - k - 2; i++) {
			if (matrix[n - i - 1][i + k] < matrix[n - i - 2][i + k + 1])
				max = matrix[n - i - 2][i + k + 1];
			else
				max = matrix[n - i - 1][i + k];
			while (1) {
				if (max == Y) {
					inf = 1;
					break;
				}
				max++;
				if (num_count[max - X] == 0) {
					matrix[n - i - 1][i + k + 1] = max;
					num_count[max - X] = 1;
					break;
				}
			}
		}
	}
	if (inf == 1) return 0; //��� ������ �Է��� ������ ���, 0�� ����.

	return 1; //��� ������ �Է¿� ������ ���, 1�� ����.
}

/* You can modify to here */

int main(void) {
	// your code goes here
	int X, Y, n;
	int *D, **matrix, i, j;


	printf("What is X and Y?");
	scanf("%d %d", &X, &Y);
	printf("What is n?");
	scanf("%d", &n);
	D = (int*)calloc(n, sizeof(int));
	printf("What are Ds?");
	for (i = 0; i<n; i++) {
		scanf("%d", &D[i]);
	}



	matrix = (int**)calloc(n, sizeof(int*));
	for (i = 0; i<n; i++) {
		matrix[i] = (int*)calloc(n, sizeof(int));
	}

	printf("\n");
	if (test_cases(X, Y, n, D, matrix) == 0) {
		printf("Infeasible!\n");
	}
	else {
		for (i = 0; i<n; i++) {
			for (j = 0; j<n; j++) {
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
	}




	for (i = 0; i<n; i++) {
		free(matrix[i]);
	}
	free(matrix);
	free(D);


	return 0;
}
