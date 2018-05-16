#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* You can modify from here */

int cal_S(int p, char s[], int swap1[], int swap2[]) {
	int n = 0, len = 0, i = 0, j = 0;
	char s_chg[1000], temp;
	/* len : ���ڿ��� ����, i, j : count variable
	   s_chg : swap �߰� ������ �����ϴ� ���ڿ�, temp : swap ������ ���Ǵ� ����. */

	while (s[len] != '\0') len++; // ���ڿ��� ���̸� len�� ����.

	if (len < p) p %= len; // p�� len���� ũ�ٸ�, p�� p%len�� ����.

	if (p%len == 0) return 0; // p�� len�� ����̰ų� 0�̸�, rotate�� �� �ʿ䰡 �����Ƿ� 0�� �����ϰ� �Լ��� ����.

	for (i = 0; i < len; i++) {
		s_chg[i] = s[i];
	} // s_chg�� s ���ڿ��� ����.


	// 1. ���ڿ��� ������ ���ݺ��� rotate ���� ���� ���
	if (len / 2 > p) {
		for (i = 0; i < len - p; i++) {
			swap1[n] = i;
			swap2[n] = p + i;
			temp = s_chg[swap1[n]];
			s_chg[swap1[n]] = s_chg[swap2[n]];
			s_chg[swap2[n]] = temp;
			n++;
		} // ���������κ��� �����ʿ� �ִ� ���ڿ��� ���ڸ��� ��ġ�ϵ��� swap.
		for (i = 0; i < p - 1; i++) {
			j = 0;
			while (1) {
				if (s[i] == s_chg[len - p + i + j])
					break;
				j++;
			}
			if (j != 0) {
				swap1[n] = len - p + i;
				swap2[n] = len - p + i + j;
				temp = s_chg[swap1[n]];
				s_chg[swap1[n]] = s_chg[swap2[n]];
				s_chg[swap2[n]] = temp;
				n++;
			}
		} // ������ ���ڿ��� ���ڸ��� ��ġ�ϵ��� swap. ���ڸ��� �ִٸ� swap�� ���� ����.
	}


	// 2. ���ڿ��� ������ ���ݺ��� rotate ���� ū ���.
	else if (len / 2 < p) {
		for (i = 0; i < p; i++) {
			swap1[n] = p - i - 1;
			swap2[n] = len - i - 1;
			temp = s_chg[swap1[n]];
			s_chg[swap1[n]] = s_chg[swap2[n]];
			s_chg[swap2[n]] = temp;
			n++;
		} // ���������κ��� ���ʿ� �ִ� ���ڿ��� ���ڸ��� ��ġ�ϵ��� swap.
		for (i = 0; i < len - p - 1; i++) {
			j = 0;
			while (1) {
				if (s[p + i] == s_chg[i + j])
					break;
				j++;
			}
			if (j != 0) {
				swap1[n] = i;
				swap2[n] = i + j;
				temp = s_chg[swap1[n]];
				s_chg[swap1[n]] = s_chg[swap2[n]];
				s_chg[swap2[n]] = temp;
				n++;
			}
		} // ������ ���ڿ��� ���ڸ��� ��ġ�ϵ��� swap. ���ڸ��� �ִٸ� swap�� ���� ����.
	}


	// 3. ���ڿ��� ������ ���ݰ� rotate ���� ���� ���.
	else {
		for (i = 0; i < p; i++) {
			swap1[n] = i;
			swap2[n] = i + p;
			n++;
		}
	} // ���ڿ��� ������ ���� ��ŭ�� swap�� ����.

	return n;
}

/* You can modify to here */

int main(void) {
	char s[1000], temp;
	int swap1[10000], swap2[10000], p, y, n, i, j;

	printf("What is p?");
	scanf("%d", &p);
	printf("What is String?");
	scanf("%s", s);



	n = cal_S(p, s, swap1, swap2);
	for (i = 0; i<n; i++) {
		printf("SWAP %d and %d\n", swap1[i], swap2[i]);
		temp = s[swap1[i]];
		s[swap1[i]] = s[swap2[i]];
		s[swap2[i]] = temp;
		printf("Current String: %s\n", s);
	}
	printf("n=%d\n", n);
	return 0;
}
