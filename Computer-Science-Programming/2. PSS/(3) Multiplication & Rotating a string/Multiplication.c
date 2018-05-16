#include <stdio.h>
#include <stdlib.h>

/* You can modify from here */

int cal_x(int x[], int y) {

	int n = 0;

	int fib[1000], i = 0, k = 0, min, sub = 0; 
	/* fib : 피보나치 수열을 저장하는 1차원 배열, i, k : count variabe, min : 입력된 수보다 작으면서 최대의 수를 저장하는 변수.
	   sub : 수열의 마지막 수와 입력된 수와의 차를 저장하는 변수. */

	if (y == 1) {
		n = 1;
		return n;
	}
	if (y == 2) {
		n = 4;
		x[n - 1] = 2;
		return n;
	}
	if (y == 3) {
		n = 3;
		return n;
	}
	if (y == 4) {
		n = 4;
		x[n - 1] = 4;
		return n;
	}
	// 입력된 수가 1, 2, 3, 4인 특이한 경우에 대해서는 직접 결과를 입력하고 함수를 종료. 

	fib[0] = fib[1] = 1;
	for (i = 0; i < 998; i++)
		fib[i + 2] = fib[i + 1] + fib[i];
	// 1000까지의 피보나치 수열을 fib에 저장한다.

	i = 0;
	n = 3;
	while (1) {
		k = 1 * fib[i] + 3 * fib[i + 1];
		if (k > y) {
			min = x[i + 2]; break;
		}
		else {
			x[n] = k;
			n++;
			if (k == y) return n;
		}
		i++;
	}
	/* 수열의 가장 큰 두 수를 더함으로써 새로운 수를 계속하여 수열에 생성, 저장한다.
	   새로운 수가 입력된 수보다 큰 경우 while문을 break한다. */

	i = n - 1;
	while (1) {
		sub = y - min;
		while (sub < x[i]) {
			i--;
		}
		x[n] = x[n - 1] + x[i];
		min = x[n];
		n++;
		if (min == y) return n;
	}
	/* sub에 입력된 수-수열에서 가장 큰 수를 저장한다. sub보다 작은 수가 나타날 때까지 역순으로 수열을 검사한다.
	   나타난 경우, 수열에서 가장 큰 수와 그 수를 더하여 새로운 수를 생성, 저장한다. 입력된 수가 생성될 때까지 반복한다. */

	return n;
}

/* You can modify to here */

int main(void) {
	int x[10000], y, n, i;

	x[0] = 1, x[1] = 1, x[2] = 3;


	printf("What is y?");
	scanf("%d", &y);


	n = cal_x(x, y);

	for (i = 0; i<n; i++) {
		printf("%d ", x[i]);
	}
	printf("\n");



	return 0;
}
