#include <stdio.h>

/* You can modify from here */

int Foker_hands(char BN1, char BS1, char BN2, char BS2, char BN3, char BS3, char WN1, char WS1, char WN2, char WS2, char WN3, char WS3) {
	int Bvalue = 0, Wvalue = 0; //각 플레이어의 족보 점수를 저장하는 변수.
	char bnl, bnm, bns, wnl, wnm, wns; //BN1, BN2, BN3, WN1, WN2, WN3을 내림차순으로 정리하여 저장한 변수.


	//세 장의 카드의 숫자를 내림차순으로 정리하여, 새로 정의한 변수에 저장.
	if (BN1 >= BN2) {
		if (BN1 >= BN3) {
			bnl = BN1;
			if (BN3 >= BN2) {
				bnm = BN3;
				bns = BN2;
			}
			else {
				bnm = BN2;
				bns = BN3;
			}
		}
		else {
			bnl = BN3;
			bnm = BN1;
			bns = BN2;
		}
	}
	else {
		if (BN2 >= BN3) {
			bnl = BN2;
			if (BN3 >= BN1) {
				bnm = BN3;
				bns = BN1;
			}
			else {
				bnm = BN1;
				bns = BN3;
			}
		}
		else {
			bnl = BN3;
			bnm = BN2;
			bns = BN1;
		}
	}

	if (WN1 >= WN2) {
		if (WN1 >= WN3) {
			wnl = WN1;
			if (WN3 >= WN2) {
				wnm = WN3;
				wns = WN2;
			}
			else {
				wnm = WN2;
				wns = WN3;
			}
		}
		else {
			wnl = WN3;
			wnm = WN1;
			wns = WN2;
		}
	}
	else {
		if (WN2 >= WN3) {
			wnl = WN2;
			if (WN3 >= WN1) {
				wnm = WN3;
				wns = WN1;
			}
			else {
				wnm = WN1;
				wns = WN3;
			}
		}
		else {
			wnl = WN3;
			wnm = WN2;
			wns = WN1;
		}
	}


	//black 점수채점

	//Straight, Straight Flush
	if (bnl - bnm == 1 || bnl - bns == 1) {
		if (bnl == '9') {
			if (BS1 == BS2 && BS2 == BS3) {
				if (Bvalue < 59)
					Bvalue = 59;
			}
			else {
				if (Bvalue < 49)
					Bvalue = 49;
			}
		}
		else {
			if (BS1 == BS2 && BS2 == BS3) {
				if (Bvalue < 50 + bnl - 48 + 1)
					Bvalue = 50 + bnl - 48 + 1;
			}
			else {
				if (Bvalue < 40 + bnl - 48 + 1)
					Bvalue = 40 + bnl - 48 + 1;
			}
		}
	}

	if (bnm - bns == 1) {
		if (bnm == '9') {
			if (BS1 == BS2 && BS2 == BS3) {
				if (Bvalue < 59)
					Bvalue = 59;
			}
			else {
				if (Bvalue < 49)
					Bvalue = 49;
			}
		}
		else {
			if (BS1 == BS2 && BS2 == BS3) {
				if (Bvalue < 50 + bnm - 48 + 1)
					Bvalue = 50 + bnm - 48 + 1;
			}
			else {
				if (Bvalue < 40 + bnm - 48 + 1)
					Bvalue = 40 + bnm - 48 + 1;
			}
		}
	}

	if (bnl - bnm == 2 || bnl - bns == 2) {
		if (BS1 == BS2 && BS2 == BS3) {
			if (Bvalue < 50 + bnl - 48)
				Bvalue = 50 + bnl - 48;
		}
		else {
			if (Bvalue < 40 + bnl - 48)
				Bvalue = 40 + bnl - 48;
		}
	}

	if (bnm - bns == 2) {
		if (BS1 == BS2 && BS2 == BS3) {
			if (Bvalue < 50 + bnm - 48)
				Bvalue = 50 + bnm - 48;
		}
		else {
			if (Bvalue < 40 + bnm - 48)
				Bvalue = 40 + bnm - 48;
		}
	}


	//Flush
	if (BS1 == BS2 && BS2 == BS3) {
		if (Bvalue < 39)
			Bvalue = 39;
	}


	//Three of a kind
	if (bnl == bnm || bnm == bns) {
		if (Bvalue < 20 + bnm - 48)
			Bvalue = 20 + bnm - 48;
	}


	//Pair
	if (Bvalue == 0) {
		Bvalue = 10 + bnl - 48;
	}


	// white 점수 채점

	//Straight, Straight Flush
	if (wnl - wnm == 1 || wnl - wns == 1) {
		if (wnl == '9') {
			if (WS1 == WS2 && WS2 == WS3) {
				if (Wvalue < 59)
					Wvalue = 59;
			}
			else {
				if (Wvalue < 49)
					Wvalue = 49;
			}
		}
		else {
			if (WS1 == WS2 && WS2 == WS3) {
				if (Wvalue < 50 + wnl - 48 + 1)
					Wvalue = 50 + wnl - 48 + 1;
			}
			else {
				if (Wvalue < 40 + wnl - 48 + 1)
					Wvalue = 40 + wnl - 48 + 1;
			}
		}
	}

	if (wnm - wns == 1) {
		if (wnm == '9') {
			if (WS1 == WS2 && WS2 == WS3) {
				if (Wvalue < 59)
					Wvalue = 59;
			}
			else {
				if (Wvalue < 49)
					Wvalue = 49;
			}
		}
		else {
			if (WS1 == WS2 && WS2 == WS3) {
				if (Wvalue < 50 + wnm - 48 + 1)
					Wvalue = 50 + wnm - 48 + 1;
			}
			else {
				if (Wvalue < 40 + wnm - 48 + 1)
					Wvalue = 40 + wnm - 48 + 1;
			}
		}
	}

	if (wnl - wnm == 2 || wnl - wns == 2) {
		if (WS1 == WS2 && WS2 == WS3) {
			if (Wvalue < 50 + wnl - 48)
				Wvalue = 50 + wnl - 48;
		}
		else {
			if (Wvalue < 40 + wnl - 48)
				Wvalue = 40 + wnl - 48;
		}
	}

	if (wnm - wns == 2) {
		if (WS1 == WS2 && WS2 == WS3) {
			if (Wvalue < 50 + wnm - 48)
				Wvalue = 50 + wnm - 48;
		}
		else {
			if (Wvalue < 40 + wnm - 48)
				Wvalue = 40 + wnm - 48;
		}
	}


	//Flush
	if (WS1 == WS2 && WS2 == WS3) {
		if (Wvalue < 39)
			Wvalue = 39;
	}


	//Three of a kind
	if (wnl == wnm || wnm == wns) {
		if (Wvalue < 20 + wnm - 48)
			Wvalue = 20 + wnm - 48;
	}


	//Pair
	if (Wvalue == 0) {
		Wvalue = 10 + wnl - 48;
	}


	// 승부 가르기

	if (Bvalue > Wvalue)
		return -1;
	else if (Bvalue < Wvalue)
		return 1;
	else {
		if (Bvalue >= 10 && Bvalue <= 19) { // Pair로 같은 경우, pair를 이루지 않은 나머지 한 장의 숫자가 크면 승리.
			if (bnm > wnm)
				return -1;
			else if (bnm < wnm)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}

	//printf("%c%c %c%c %c%c %c%c %c%c %c%c", BN1, BS1, BN2, BS2, BN3, BS3,WN1, WS1, WN2, WS2, WN3, WS3 );

}

/* You can modify to here */

int main(void) {
	// your code goes here
	int result;
	char BN1, BS1, BN2, BS2, BN3, BS3, WN1, WS1, WN2, WS2, WN3, WS3;


	scanf("%c%c %c%c %c%c %c%c %c%c %c%c", &BN1, &BS1, &BN2, &BS2, &BN3, &BS3, &WN1, &WS1, &WN2, &WS2, &WN3, &WS3);

	result = Foker_hands(BN1, BS1, BN2, BS2, BN3, BS3, WN1, WS1, WN2, WS2, WN3, WS3);
	if (result == 1) printf("White wins.\n");
	else if (result == -1) printf("Black wins.\n");
	else printf("Tie.\n");
	return 0;
}
