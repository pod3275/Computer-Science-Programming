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
	} // = ���� ����.

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
				} // (A) = (B) ����, A�� ù �κ��� ��ġ�� ifofs�� ����.
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
				} // (A) = (B) ����, B�� �� �κ��� ��ġ�� ifofe�� ����.

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
			} // A=B ==> (A>B)+(B>A) �� ����.
			i++;
		} // ������� ����.

		for (i = 0; str2[i] != '\0'; i++)
			str[i] = str2[i];
		str[i] = '\0'; // str�� ������ ���� ����.

	} // =�� ������ŭ �ݺ�.
}

void Implication(char *str) {
	int i = 0, j, k, m, end, count, icount = 0, imps, impe;
	char str2[1000];
	while (str[i] != '\0') {
		if (str[i] == '>')
			icount++;
		i++;
	} // > ���� ����.

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
				} // (A) > (B) ����, A�� ù �κ��� ��ġ�� imps�� ����.
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
				} // (A) > (B) ����, B�� �� �κ��� ��ġ�� impe�� ����.

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
			} // A>B ==> ~A*B �� ����.
			i++;
		} // ������� ����.

		for (i = 0; str2[i] != '\0'; i++)
			str[i] = str2[i];
		str[i] = '\0'; // str�� ������ ���� ����.

	} // >�� ������ŭ �ݺ�.
}

void Negation(char *str) {
	int i = 0, j, k, ncount = 0, m, end, negs, nege, count;
	char str2[1000];
	while (str[i] != '\0') {
		if (str[i] == '(' && str[i - 1] == '~')
			ncount++;
		i++;
	} // ��ȣ �տ� �ִ� ~�� ���� ����.

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
				} // ~(A) ���� A�� ���κ��� ��ġ�� nege�� ����.
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
			} // ~(a+b) ==> ~a*~b, ~(a*b) ==> ~a+~b �� ����.
			i++;
		}

		for (i = 0; str2[i] != '\0'; i++)
			str[i] = str2[i];
		str[i] = '\0'; // str�� ������ ���� ����.
	}

	end = 0;
	while (str[end] != '\0')
		end++;
	end--; // �� ���� ����.

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
	} // ~a -> A�� ��ȯ.

	str2[k] = '\0';

	for (i = 0; str2[i] != '\0'; i++)
		str[i] = str2[i];
	str[i] = '\0'; // str�� ������ ���� ����.

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
	} // �� *, +�� type�� ��ġ�� ����.

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
			} // a+(b*c) ==> (a+c)*(b+c) �� ����.

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
			} // (a*b)+c ==> (a+c)*(b+c) �� ����.
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
		} // (A)*(B)�� ���Ͽ� A, B�� ���� �����Ͽ� clausal form���� ����.
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
	} // *�� ���� ���, a+b ==> ab�� �����Ͽ� ���� �迭 ���� clause�� ����.
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
			} // ABaB���� A�� a �� B�� B�� ���縦 Ž��, ��ġ�� ����.
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
			} // ABaB����, ��ġ�� ���� �����ϰ� buf�� ����.
		}
		buf[len] = '\0';
		for (j = 0; j < len; j++) {
			clause[i][j] = buf[j];
		} // clause�� buf�� ������ ����.
		clause[i][len] = '\0';
		for (j = len + 1; clause[i][j] != '\0'; j++)
			clause[i][j] = 0;
	}
}

void ClausalForm(char *str) {
	IFOF(str); // = �� ���ִ� �Լ�.
	Implication(str); // > �� ���ִ� �Լ�.
	Negation(str); // ~ �� ���ִ� �Լ�.
	AndOr(str); // *, +�� ���ִ� �Լ�.
	ClauseClean(); // and�� ����� form����, ���� ���� ���ְų� �翬�� ���� �����ϴ� �Լ�.
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
	} // clausal form ���.
}