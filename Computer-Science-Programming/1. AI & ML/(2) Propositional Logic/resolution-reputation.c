#include <stdio.h>

void IFOF(char* str);
void Implication(char* str);
void Negation(char* str);
void AndOr(char *str);
void ClausalForm(char *str);
int Resolve();

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

int Resolve() {
	int i, j, k, n, l, b=0, same = 1, diff, count=0;
	char buf[100];

	while (count != 20) { // 임의로 20번의 검사를 시행한다. 20번 이상의 경우, empty clause을 찾을 수 없다고 가정.
		for (i = 0; i < form; i++) {
			for (j = i; j < form; j++) {
				k = 0;
				while (clause[i][k] != '\0') {
					n = 0;
					while (clause[j][n] != '\0') {
						if (clause[i][k] - clause[j][n] == 32 || clause[i][k] - clause[j][n] == -32) { 
							// PQ, ps에서 P와 p의 존재성을 묻는 if문.
							b = 0; same = 1; diff = 1;
							for (l = 0; l < k; l++) {
								buf[b] = clause[i][l];
								b++;
							}
							l = k + 1;
							while (clause[i][l] != '\0') {
								buf[b] = clause[i][l];
								l++; b++;
							}
							for (l = 0; l < n; l++) {
								buf[b] = clause[j][l];
								b++;
							}
							l = n + 1;
							while (clause[j][l] != '\0') {
								buf[b] = clause[j][l];
								l++; b++;
							}
							buf[b] = '\0'; // NpQ, mPs를 통해 NQms를 얻고, buf에 저장한다.

							if (buf[0] == '\0') {
								l = 0;
								while (clause[i][l] != '\0') {
									printf("%c", clause[i][l]);
									l++;
								}
								l = 0; printf(" ");
								while (clause[j][l] != '\0') {
									printf("%c", clause[j][l]);
									l++;
								}
								printf(" => ");
								printf("EMPTY\n");
								return 1;
							} // empty clause가 생성되는 경우, EMPTY이다 를 출력하고 return 1.
							
							for (l = 0; l < form; l++) {
								b = 0; same = 1;
								while (clause[l][b] != '\0') {
									if (clause[l][b] != buf[b])
										same += 1;
									b++;
								}
								if (same == 1) diff = 0;
							} // 기존 clausal form들과 buf를 비교하여, 같은 것이 있으면 추가하지 않음.

							if (diff == 1) {
								// 같은 것이 없다면, 프린트 및 clause에 저장.
								l = 0;
								while (clause[i][l] != '\0') {
									printf("%c", clause[i][l]);
									l++;
								}
								l = 0; printf(" ");
								while (clause[j][l] != '\0') {
									printf("%c", clause[j][l]);
									l++;
								}
								printf(" => ");
								l = 0;
								while (buf[l] != '\0') {
									printf("%c", buf[l]);
									l++;
								}
								printf("\n");

								l = 0;
								while (buf[l] != '\0') {
									clause[form][l] = buf[l];
									l++;
								}
								form++;
							}
						}
						n++;
					}
					k++;
				}
			}
		}
		count++;
	}
	return 0;
}


void main() {
	char goal[1000], str[100][1000], buf[1000] = { 0 };
	int i = 0, j = 0, numexp;
	printf("Input the goal:\n");
	gets_s(goal, sizeof(goal));
	
	printf("Input logic expressions:\n");
	while (1) {
		gets_s(str[i], sizeof(str[i]));
		if (str[i][0] == '.')
			break;
		i++;
	}

	numexp = i;

	for (i = 0; goal[i] != '\0'; i++) {
		buf[i] = goal[i];
	}
	goal[0] = '~'; goal[1] = '(';

	for (i = 0; buf[i] != '\0'; i++) {
		goal[i + 2] = buf[i];
	}
	goal[i + 2] = ')'; goal[i + 3] = '\0'; // goal을 부정한다.

	ClausalForm(goal); // goal의 부정을 clausal form으로 변형한 후, clause에 넣는다.

	for (i = 0; i<numexp; i++) {
		ClausalForm(str[i]);
	} // 각 logic expressions을 clausal form으로 변형한 후에 clause에 넣는다.

	printf("\nClausal forms:\n");
	for (i = 0; i < form; i++) {
		for (j = 0; clause[i][j] != '\0'; j++) {
			printf("%c", clause[i][j]);
		}
		printf(" ");
	} // clausal form 출력.

	printf("\n\nResolving:\n");
	if (Resolve() == 1) // Resolve : resolving 하는 함수.
		printf("\nThe goal is TRUE\n"); // empty clause가 나타나면 TRUE.
	else
		printf("\nUnable to prove"); // 20번의 시행 결과 나타나지 않으면 unable to prove.
}