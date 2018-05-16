#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* You can modify from here */

int cal_S(int p, char s[], int swap1[], int swap2[]) {
	int n = 0, len = 0, i = 0, j = 0;
	char s_chg[1000], temp;
	/* len : 문자열의 길이, i, j : count variable
	   s_chg : swap 중간 과정을 저장하는 문자열, temp : swap 과정에 사용되는 변수. */

	while (s[len] != '\0') len++; // 문자열의 길이를 len에 저장.

	if (len < p) p %= len; // p가 len보다 크다면, p에 p%len를 저장.

	if (p%len == 0) return 0; // p가 len의 배수이거나 0이면, rotate를 할 필요가 없으므로 0을 리턴하고 함수를 종료.

	for (i = 0; i < len; i++) {
		s_chg[i] = s[i];
	} // s_chg에 s 문자열을 복사.


	// 1. 문자열의 길이의 절반보다 rotate 수가 작은 경우
	if (len / 2 > p) {
		for (i = 0; i < len - p; i++) {
			swap1[n] = i;
			swap2[n] = p + i;
			temp = s_chg[swap1[n]];
			s_chg[swap1[n]] = s_chg[swap2[n]];
			s_chg[swap2[n]] = temp;
			n++;
		} // 기준점으로부터 오른쪽에 있는 문자열을 제자리에 위치하도록 swap.
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
		} // 나머지 문자열을 제자리에 위치하도록 swap. 제자리에 있다면 swap을 하지 않음.
	}


	// 2. 문자열의 길이의 절반보다 rotate 수가 큰 경우.
	else if (len / 2 < p) {
		for (i = 0; i < p; i++) {
			swap1[n] = p - i - 1;
			swap2[n] = len - i - 1;
			temp = s_chg[swap1[n]];
			s_chg[swap1[n]] = s_chg[swap2[n]];
			s_chg[swap2[n]] = temp;
			n++;
		} // 기준점으로부터 왼쪽에 있는 문자열을 제자리에 위치하도록 swap.
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
		} // 나머지 문자열을 제자리에 위치하도록 swap. 제자리에 있다면 swap을 하지 않음.
	}


	// 3. 문자열의 길이의 절반과 rotate 수가 같은 경우.
	else {
		for (i = 0; i < p; i++) {
			swap1[n] = i;
			swap2[n] = i + p;
			n++;
		}
	} // 문자열의 길이의 절반 만큼의 swap을 진행.

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
