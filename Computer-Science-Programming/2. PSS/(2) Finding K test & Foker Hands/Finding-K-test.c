#include <stdio.h>
#include <stdlib.h>

/* You can modify from here */

int test_cases(int X, int Y, int n, int *D, int **matrix) {
	int *num_count, num, min, max, inf = 0, i, j = 0, k; 
	/* num_const : 숫자의 중복을 막는 변수, num : 초기화(양 끝값과 대각선 값을 matrix에 입력)하는 과정에서 쓰이는 변수
	min, max : 대각선 원소의 비교 중에 쓰이는 변수, inf : matrix 생성이 infeasible한 경우를 판단하는 변수, i, j, k : count vairable*/

	num_count = (int*)calloc(Y - X + 1, sizeof(int));


	//num_count와 matrix 초기화(matrix내에 양 끝 값과 대각선 값 입력)
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


	//크기 혹은 입력 오류로 infeasible한 경우, 0을 리턴하고 함수를 종료.
	if (n*n > Y - X + 1)
		return 0;
	for (i = 0; i < n; i++) {
		if (D[i] <= X || D[i] >= Y)
			return 0;
	}


	//대각선 기준 왼쪽 위의 영역에 대해 적절한 원소 값을 입력.
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
	if (inf == 1) return 0; //모든 원소의 입력을 실패한 경우, 0을 리턴.


	//대각선 기준 오른쪽 아래의 영역에 대해 적절한 원소 값을 입력.
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
	if (inf == 1) return 0; //모든 원소의 입력을 실패한 경우, 0을 리턴.

	return 1; //모든 원소의 입력에 성공한 경우, 1을 리턴.
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
