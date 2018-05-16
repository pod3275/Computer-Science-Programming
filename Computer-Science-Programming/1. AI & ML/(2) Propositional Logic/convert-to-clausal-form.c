#include <stdio.h>

void IFOF(char* str);
void Implication(char* str);
void Negation(char* str);
void AndOr(char *str);
void ClausalForm(char *str);

char* clause[100][100] = { 0 };
int form = 0;

void IFOF(char* str) {
	int i = 0, j, k, m, end, count, ecount = 0, ifofs, ifofe;
	char str2[1000];
	while (str[i] != '\0') {
		if (str[i] == '=')
			ecount++;
		i++;
	} // = 개수 저장.

	for (m = 0; m < ecount; m++) {
		end = 0;
		i = 0;
		ifofe = 0;
		ifofs = 0;
		count = 0;

		while (str[end] != '\0')
			end++;
		end--;

		while (str[i] != '\0') {
			if (str[i] == '=') {
				j = i - 1;
				while (j >= 0) {
					if (str[j] == ')')
						count--;
					else if (str[j] == '(')
						count++;
					if (count == 0) {
						ifofs = j;
						break;
					}
					j--;
				} // (A) = (B) 에서, A의 첫 부분의 위치를 ifofs에 저장.
				count = 0; j = i + 1;
				while (j <= end) {
					if (str[j] == '(')
						count++;
					else if (str[j] == ')')
						count--;
					if (count == 0) {
						ifofe = j;
						break;
					}
					j++;
				} // (A) = (B) 에서, B의 끝 부분의 위치를 ifofe에 저장.

				for (j = 0; j < ifofs; j++)
					str2[j] = str[j];

				str2[j] = '('; j++;
				for (k = 0; k < i - ifofs; k++) {
					str2[j + k] = str[ifofs + k];
				}
				j = j + k; str2[j] = '>'; j++;
				for (k = 0; k < ifofe - i; k++) {
					str2[j + k] = str[i + k + 1];
				}
				j = j + k; str2[j] = ')'; j++;

				str2[j] = '*'; j++;

				str2[j] = '('; j++;
				for (k = 0; k < ifofe - i; k++) {
					str2[j + k] = str[i + k + 1];
				}
				j = j + k; str2[j] = '>'; j++;
				for (k = 0; k < i - ifofs; k++) {
					str2[j + k] = str[ifofs + k];
				}
				j = j + k; str2[j] = ')'; j++;

				for (k = 0; k < end - ifofe; k++) {
					str2[j + k] = str[ifofe + k + 1];
				}
				str2[j + k] = '\0';

				break;
			} // A=B ==> (A>B)+(B>A) 로 변형.
			i++;
		} // 여기까지 변형.

		for (i = 0; str2[i] != '\0'; i++)
			str[i] = str2[i];
		str[i] = '\0'; // str에 변형한 것을 복사.

	} // =의 개수만큼 반복.
}

void Implication(char *str) {
	int i = 0, j, k, m, end, count, icount = 0, imps, impe;
	char str2[1000];
	while (str[i] != '\0') {
		if (str[i] == '>')
			icount++;
		i++;
	} // > 개수 저장.

	for (m = 0; m < icount; m++) {
		end = 0;
		i = 0;
		impe = 0;
		imps = 0;
		count = 0;

		while (str[end] != '\0')
			end++;
		end--;

		while (str[i] != '\0') {
			if (str[i] == '>') {
				j = i - 1;
				while (j >= 0) {
					if (str[j] == ')')
						count--;
					else if (str[j] == '(')
						count++;
					if (count == 0) {
						imps = j;
						break;
					}
					j--;
				} // (A) > (B) 에서, A의 첫 부분의 위치를 imps에 저장.
				count = 0; j = i + 1;
				while (j <= end) {
					if (str[j] == '(')
						count++;
					else if (str[j] == ')')
						count--;
					if (count == 0) {
						impe = j;
						break;
					}
					j++;
				} // (A) > (B) 에서, B의 끝 부분의 위치를 impe에 저장.

				for (j = 0; j < imps; j++)
					str2[j] = str[j];

				str2[j] = '~'; j++;
				for (k = 0; k < i - imps; k++) {
					str2[j + k] = str[imps + k];
				}
				j = j + k; str2[j] = '+'; j++;
				for (k = 0; k < impe - i; k++) {
					str2[j + k] = str[i + k + 1];
				}
				j = j + k;
				for (k = 0; k < end - impe; k++) {
					str2[j + k] = str[impe + k + 1];
				}
				str2[j + k] = '\0';

				break;
			} // A>B ==> ~A*B 로 변형.
			i++;
		} // 여기까지 변형.

		for (i = 0; str2[i] != '\0'; i++)
			str[i] = str2[i];
		str[i] = '\0'; // str에 변형한 것을 복사.

	} // >의 개수만큼 반복.
}

void Negation(char *str) {
	int i = 0, j, k, ncount = 0, m, end, negs, nege, count;
	char str2[1000];
	while (str[i] != '\0') {
		if (str[i] == '(' && str[i - 1] == '~')
			ncount++;
		i++;
	} // 괄호 앞에 있는 ~의 개수 저장.

	for (m = 0; m < ncount; m++) {
		end = 0;
		i = 0;
		negs = 0;
		nege = 0;
		count = 0;

		while (str[end] != '\0')
			end++;
		end--;

		while (str[i] != '\0') {
			if (str[i] == '(' && str[i - 1] == '~') {
				count = 0; j = i;
				while (j <= end) {
					if (str[j] == '(')
						count++;
					else if (str[j] == ')')
						count--;
					if (count == 0) {
						nege = j;
						break;
					}
					j++;
				} // ~(A) 에서 A의 끝부분의 위치를 nege에 저장.
				for (j = 0; j < i - 1; j++)
					str2[j] = str[j];

				str2[j] = '('; j++; k = j + 1;
				while (k < nege) {
					if (str[k] == '*') {
						str2[j] = '+';
						k++; j++;
					}
					else if (str[k] == '+') {
						str2[j] = '*';
						k++; j++;
					}
					else if (str[k] == '(') {
						str2[j] = '~'; j++;
						for (k; str[k] != ')'; k++) {
							str2[j] = str[k];
							j++;
						}
						str2[j] = ')';
						k++; j++;
					}
					else if (str[k] == '~') {
						if (str[k + 1] == '(') {
							k = k + 1;
							for (k; str[k] != ')'; k++) {
								str2[j] = str[k];
								j++;
							}
							str2[j] = ')';
							j++; k++;
						}
						else {
							str2[j] = str[k + 1];
							j++; k += 2;
						}
					}
					else {
						str2[j] = '~'; j++;
						str2[j] = str[k]; j++; k++;
					}
				}
				str2[j] = ')'; j++;

				for (k = nege + 1; k <= end; k++) {
					str2[j] = str[k];
					j++;
				}

				str2[j] = '\0';
				break;
			} // ~(a+b) ==> ~a*~b, ~(a*b) ==> ~a+~b 로 변형.
			i++;
		}

		for (i = 0; str2[i] != '\0'; i++)
			str[i] = str2[i];
		str[i] = '\0'; // str에 변형한 것을 복사.
	}

	end = 0;
	while (str[end] != '\0')
		end++;
	end--; // 총 길이 저장.

	k = 0; i = 0;
	while (i <= end) {
		if (str[i] == '~') {
			str2[k] = str[i + 1] - 32;
			k++;
			i += 2;
		}
		else {
			str2[k] = str[i];
			k++;
			i++;
		}
	} // ~a -> A로 변환.

	str2[k] = '\0';

	for (i = 0; str2[i] != '\0'; i++)
		str[i] = str2[i];
	str[i] = '\0'; // str에 변형한 것을 복사.

}


struct ope { char type; int loc; };

void AndOr(char *str) {
	int i = 0, j = 0, m = 0, k, end = 0, numop = 0;
	char str2[1000] = { 0 }, str3[1000] = { 0 }, a, b, c;
	struct ope op[1000];

	while (str[end] != '\0')
		end++;
	end--;

	for (i = 0; i <= end; i++) {
		if (str[i] == '*') {
			op[numop].type = '*';
			op[numop].loc = i;
			numop++;
		}
		else if (str[i] == '+') {
			op[numop].type = '+';
			op[numop].loc = i;
			numop++;
		}
	} // 각 *, +의 type과 위치를 저장.

	for (i = 0; i < numop; i++) {
		if (op[i].type == '+') {
			k = op[i].loc;
			if (((str[k - 1] >= 'A' && str[k - 1] <= 'Z') ||
				(str[k - 1] >= 'a' && str[k - 1] <= 'z')) &&
				(str[k + 1] == '(') && (str[k + 3] == '*') &&
				(str[k + 5] == ')') && (k >= 1)) {

				for (m = 0; m < 1000; m++)
					str2[m] = 0;

				j = 0;
				for (m = k + 6; str[m] != '\0'; m++) {
					str2[j] = str[m];
					j++;
				}
				str2[j] = '\0';

				a = str[k - 1]; b = str[k + 2]; c = str[k + 4];
				str[k - 1] = '('; str[k] = a; str[k + 1] = '+'; str[k + 2] = b;
				str[k + 3] = ')'; str[k + 4] = '*'; str[k + 5] = '('; str[k + 6] = a;
				str[k + 7] = '+'; str[k + 8] = c; str[k + 9] = ')';

				for (m = 0; str2[m] != '\0'; m++) {
					str[k + 10 + m] = str2[m];
				}
				str[k + 10 + m] = '\0';
			} // a+(b*c) ==> (a+c)*(b+c) 로 변형.

			else if (((str[k + 1] >= 'A' && str[k + 1] <= 'Z') ||
				(str[k + 1] >= 'a' && str[k + 1] <= 'z')) &&
				(str[k - 1] == ')') && (str[k - 3] == '*') &&
				(str[k - 5] == '(') && (k > 4)) {

				for (m = 0; m < 1000; m++)
					str2[m] = 0;

				j = 0;
				for (m = k + 2; str[m] != '\0'; m++) {
					str2[j] = str[m];
					j++;
				}
				str2[j] = '\0';

				a = str[k - 4]; b = str[k - 2]; c = str[k + 1];
				str[k - 3] = '+'; str[k - 2] = c; str[k] = '*';
				str[k + 1] = '('; str[k + 2] = b; str[k + 3] = '+';
				str[k + 4] = c; str[k + 5] = ')';

				for (m = 0; str2[m] != '\0'; m++) {
					str[k + 6 + m] = str2[m];
				}
				str[k + 6 + m] = '\0';
			} // (a*b)+c ==> (a+c)*(b+c) 로 변형.
		}
	}


	for (m = 0; str[m] != '\0'; m++) {
		if (str[m] == '*') {
			for (j = 0; j < m; j++)
				str2[j] = str[j];
			str2[j] = '\0';

			for (j = m + 1; str[j] != '\0'; j++)
				str3[j - m - 1] = str[j];
			str3[j] = '\0';

			IFOF(str2);
			Implication(str2);
			Negation(str2);
			AndOr(str2);

			IFOF(str3);
			Implication(str3);
			Negation(str3);
			AndOr(str3);

			for (i = 0; i < 1000; i++) {
				str2[i] = 0;
				str3[i] = 0;
				str[i] = 0;
			}
		} // (A)*(B)에 대하여 A, B를 따로 생각하여 clausal form으로 변형.
	}

	if (str[0] != 0) {
		j = 0;
		for (i = 0; str[i] != '\0'; i++) {
			if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
				clause[form][j] = str[i];
				j++;
			}
		}
		clause[form][j] = '\0';
		form++;
	} // *가 없는 경우, a+b ==> ab로 변형하여 전역 배열 변수 clause에 저장.
}

void ClauseClean() {
	int i = 0, count = 0, count2 = 0, j, k, len, del[100] = { 0 };
	char buf[100] = { 0 };
	for (i = 0; i < form; i++) {
		count = 0; len = 0;
		for (j = 0; j < 100; j++)
			del[j] = 2;
		while (clause[i][count] != '\0') {
			for (j = 0; clause[i][j] != '\0'; j++) {
				if ((clause[i][count] - clause[i][j] == 32) || (clause[i][count] - clause[i][j] == -32)) {
					del[count] = 1;
				}
				else if ((clause[i][count] == clause[i][j]) && (del[count] != 1))
					del[count] = 0;
			} // ABaB에서 A와 a 및 B와 B의 존재를 탐색, 위치를 저장.
			count++;
		}
		for (j = 0; clause[i][j] != '\0'; j++) {
			count2 = 0;
			for (k = 0; k < 100; k++) {
				if (clause[i][j] == buf[k])
					count2 = 1;
			}
			if (del[j] == 0 && count2 == 0) {
				buf[len] = clause[i][j];
				len++;
			} // ABaB에서, 겹치는 것을 제외하고 buf에 저장.
		}
		buf[len] = '\0';
		for (j = 0; j < len; j++) {
			clause[i][j] = buf[j];
		} // clause에 buf의 내용을 복사.
		clause[i][len] = '\0';
		for (j = len + 1; clause[i][j] != '\0'; j++)
			clause[i][j] = 0;
	}
}

void ClausalForm(char *str) {
	IFOF(str); // = 을 없애는 함수.
	Implication(str); // > 을 없애는 함수.
	Negation(str); // ~ 을 없애는 함수.
	AndOr(str); // *, +을 없애는 함수.
	ClauseClean(); // and로 연결된 form에서, 같은 것을 없애거나 당연한 것을 제거하는 함수.
}

void main() {
	char str[1000];
	int i = 0, j = 0;
	printf("logic : ");
	gets_s(str, sizeof(str));

	ClausalForm(str);

	for (i = 0; i < form; i++) {
		for (j = 0; clause[i][j] != '\0'; j++) {
			printf("%c", clause[i][j]);
		}
		printf(" ");
	} // clausal form 출력.
}