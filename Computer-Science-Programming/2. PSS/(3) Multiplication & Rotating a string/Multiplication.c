#include <stdio.h>
#include <stdlib.h>

/* You can modify from here */

int cal_x(int x[], int y) {

	int n = 0;

	int fib[1000], i = 0, k = 0, min, sub = 0; 
	/* fib : �Ǻ���ġ ������ �����ϴ� 1���� �迭, i, k : count variabe, min : �Էµ� ������ �����鼭 �ִ��� ���� �����ϴ� ����.
	   sub : ������ ������ ���� �Էµ� ������ ���� �����ϴ� ����. */

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
	// �Էµ� ���� 1, 2, 3, 4�� Ư���� ��쿡 ���ؼ��� ���� ����� �Է��ϰ� �Լ��� ����. 

	fib[0] = fib[1] = 1;
	for (i = 0; i < 998; i++)
		fib[i + 2] = fib[i + 1] + fib[i];
	// 1000������ �Ǻ���ġ ������ fib�� �����Ѵ�.

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
	/* ������ ���� ū �� ���� �������ν� ���ο� ���� ����Ͽ� ������ ����, �����Ѵ�.
	   ���ο� ���� �Էµ� ������ ū ��� while���� break�Ѵ�. */

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
	/* sub�� �Էµ� ��-�������� ���� ū ���� �����Ѵ�. sub���� ���� ���� ��Ÿ�� ������ �������� ������ �˻��Ѵ�.
	   ��Ÿ�� ���, �������� ���� ū ���� �� ���� ���Ͽ� ���ο� ���� ����, �����Ѵ�. �Էµ� ���� ������ ������ �ݺ��Ѵ�. */

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
