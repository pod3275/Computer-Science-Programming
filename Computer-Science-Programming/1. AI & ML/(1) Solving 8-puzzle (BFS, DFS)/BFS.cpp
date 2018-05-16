#include <iostream>
#include <queue>
using namespace std;

int VISIT = 0;
int OPEN = 0;
int LENGTH = 0;
const int GOAL = 123456780;

bool isVISITED(int temp, int *visit);
bool isGOAL(int temp, int GOAL);
void EXPAND_ADD(int temp, int leng);
void ADD_VISITED(int temp, int *visit, int size);

class NUM {
private:
	int num;
	int len;
public:
	NUM() {
		num = GOAL;
		len = 0;
	}

	NUM(int a, int b) {
		num = a;
		len = b;
	}

	int getNUM() {
		return num;
	}

	int getLEN() {
		return len;
	}
};

queue<NUM> QUEUE;

bool CREATE_BFS(int start) {
	NUM st(start, 0);
	int numt, lent, i = 0;
	int VISITED[100000];
	VISITED[0] = 0;

	QUEUE.push(st);
	OPEN++;

	while (i<100000) {
		if (QUEUE.empty())
			return false;

		while (1) {
			numt = QUEUE.front().getNUM();
			lent = QUEUE.front().getLEN();
			QUEUE.pop();
			if (isVISITED(numt, VISITED) == false)
				break;
		}

		if (isGOAL(numt, GOAL)) {
			LENGTH = lent;
			return true;
		}

		EXPAND_ADD(numt, lent);
		ADD_VISITED(numt, VISITED, VISIT);
		VISIT++;
		i++;
	}

}

bool isVISITED(int temp, int* visit) {
	for (int i = 0; i < 100000; i++) {
		if (visit[i] == temp)
			return true;
	}
	return false;
}

bool isGOAL(int temp, int GOAL) {
	if (temp == GOAL)
		return true;
	else
		return false;
}

void EXPAND_ADD(int temp, int leng) {
	int locate[9], locate2[9], locate3[9], locate4[9], casenum;
	int newtemp1 = 0, newtemp2 = 0, newtemp3 = 0, newtemp4 = 0;
	int k, t = temp, n = 0, i, j;
	for (i = 8; i >= 0; i--) {
		k = t;
		for (j = 0; j < i; j++)
			k = k / 10;
		locate[n] = k;
		n++;
		for (j = 0; j < i; j++)
			k = k * 10;
		t = t - k;
	}

	for (i = 0; i < 9; i++) {
		locate2[i] = locate[i];
		locate3[i] = locate[i];
		locate4[i] = locate[i];
	}


	for (i = 0; i < n; i++) {
		if (locate[i] == 0)
			break;
	}

	if (i == 0) {
		swap(locate[0], locate[1]);
		swap(locate2[0], locate2[3]);
		casenum = 2;
	}
	else if (i == 2) {
		swap(locate[2], locate[1]);
		swap(locate2[2], locate2[5]);
		casenum = 2;
	}
	else if (i == 6) {
		swap(locate[6], locate[3]);
		swap(locate2[6], locate2[7]);
		casenum = 2;
	}
	else if (i == 8) {
		swap(locate[8], locate[5]);
		swap(locate2[8], locate[7]);
		casenum = 2;
	}

	else if (i == 1) {
		swap(locate[1], locate[0]);
		swap(locate2[1], locate2[2]);
		swap(locate3[1], locate3[4]);
		casenum = 3;
	}
	else if (i == 3) {
		swap(locate[3], locate[0]);
		swap(locate2[3], locate2[4]);
		swap(locate3[3], locate3[6]);
		casenum = 3;
	}
	else if (i == 5) {
		swap(locate[5], locate[2]);
		swap(locate2[5], locate2[4]);
		swap(locate3[5], locate3[8]);
		casenum = 3;
	}
	else if (i == 7) {
		swap(locate[7], locate[4]);
		swap(locate2[7], locate2[6]);
		swap(locate3[7], locate3[8]);
		casenum = 3;
	}

	else {
		swap(locate[4], locate[1]);
		swap(locate2[4], locate2[3]);
		swap(locate3[4], locate3[5]);
		swap(locate4[4], locate4[7]);
		casenum = 4;
	}

	if (casenum == 2) {
		for (i = 0; i < 9; i++) {
			newtemp1 *= 10;
			newtemp2 *= 10;
			newtemp1 += locate[i];
			newtemp2 += locate2[i];
		}
		NUM new1(newtemp1, leng + 1);
		NUM new2(newtemp2, leng + 1);
		QUEUE.push(new1);
		QUEUE.push(new2);
	}
	else if (casenum == 3) {
		for (i = 0; i < 9; i++) {
			newtemp1 *= 10;
			newtemp2 *= 10;
			newtemp3 *= 10;
			newtemp1 += locate[i];
			newtemp2 += locate2[i];
			newtemp3 += locate3[i];
		}
		NUM new1(newtemp1, leng + 1);
		NUM new2(newtemp2, leng + 1);
		NUM new3(newtemp3, leng + 1);
		QUEUE.push(new1);
		QUEUE.push(new2);
		QUEUE.push(new3);
	}
	else {
		for (i = 0; i < 9; i++) {
			newtemp1 *= 10;
			newtemp2 *= 10;
			newtemp3 *= 10;
			newtemp4 *= 10;
			newtemp1 += locate[i];
			newtemp2 += locate2[i];
			newtemp3 += locate3[i];
			newtemp4 += locate4[i];
		}
		NUM new1(newtemp1, leng + 1);
		NUM new2(newtemp2, leng + 1);
		NUM new3(newtemp3, leng + 1);
		NUM new4(newtemp4, leng + 1);
		QUEUE.push(new1);
		QUEUE.push(new2);
		QUEUE.push(new3);
		QUEUE.push(new4);
	}

	if (QUEUE.size() > OPEN)
		OPEN = QUEUE.size();
}

void ADD_VISITED(int temp, int *visit, int size) {
	visit[size] = temp;
}

void swap(int * a, int * b) {
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(void) {
	int number;
	cin >> number;
	CREATE_BFS(number);
	cout << "VISIT = " << VISIT << endl;
	cout << "OPEN = " << OPEN << endl;
	cout << "LEN = " << LENGTH << endl;

	return 0;
}
