#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10 //Input can be changed

int count=0;

int access_value(int x, int y) {
	int **input,i;
	input=(int**)calloc(LENGTH,sizeof(int*));
	for (i=0; i<LENGTH; i++) {
		input[i]=(int*)calloc(LENGTH,sizeof(int));
	}
	
	count++;
	
	//Input can be changed
	input[0][0]= 1;
	input[0][1]= 2;
	input[0][2]= 3;
	input[0][3]= 4;
	input[0][4]= 5;
	input[0][5]= 6;
	input[0][6]= 7;
	input[0][7]= 22;
	input[0][8]= 23;
	input[0][9]= 24;
	
	input[1][0]= 2;
	input[1][1]= 3;
	input[1][2]= 4;
	input[1][3]= 5;
	input[1][4]= 6;
	input[1][5]= 7;
	input[1][6]= 8;
	input[1][7]= 22;
	input[1][8]= 23;
	input[1][9]= 24;
	
	input[2][0]= 3;
	input[2][1]= 6;
	input[2][2]= 8;
	input[2][3]= 9;
	input[2][4]= 10;
	input[2][5]= 11;
	input[2][6]= 12;
	input[2][7]= 23;
	input[2][8]= 23;
	input[2][9]= 24;
	
	input[3][0]= 4;
	input[3][1]= 6;
	input[3][2]= 9;
	input[3][3]= 9;
	input[3][4]= 10;
	input[3][5]= 12;
	input[3][6]= 23;
	input[3][7]= 24;
	input[3][8]= 24;
	input[3][9]= 25;
	
	input[4][0]= 6;
	input[4][1]= 6;
	input[4][2]= 9;
	input[4][3]= 10;
	input[4][4]= 10;
	input[4][5]= 12;
	input[4][6]= 24;
	input[4][7]= 25;
	input[4][8]= 25;
	input[4][9]= 25;
	
	input[5][0]= 9;
	input[5][1]= 9;
	input[5][2]= 10;
	input[5][3]= 10;
	input[5][4]= 12;
	input[5][5]= 12;
	input[5][6]= 24;
	input[5][7]= 32;
	input[5][8]= 32;
	input[5][9]= 38;
	
	input[6][0]= 9;
	input[6][1]= 10;
	input[6][2]= 10;
	input[6][3]= 10;
	input[6][4]= 23;
	input[6][5]= 23;
	input[6][6]= 25;
	input[6][7]= 32;
	input[6][8]= 33;
	input[6][9]= 38;
	
	input[7][0]= 12;
	input[7][1]= 12;
	input[7][2]= 12;
	input[7][3]= 23;
	input[7][4]= 24;
	input[7][5]= 24;
	input[7][6]= 25;
	input[7][7]= 33;
	input[7][8]= 38;
	input[7][9]= 39;
	
	input[8][0]= 23;
	input[8][1]= 23;
	input[8][2]= 24;
	input[8][3]= 24;
	input[8][4]= 25;
	input[8][5]= 25;
	input[8][6]= 32;
	input[8][7]= 38;
	input[8][8]= 38;
	input[8][9]= 39;
	
	input[9][0]= 24;
	input[9][1]= 24;
	input[9][2]= 24;
	input[9][3]= 24;
	input[9][4]= 32;
	input[9][5]= 32;
	input[9][6]= 32;
	input[9][7]= 39;
	input[9][8]= 41;
	input[9][9]= 43;
	
	/*
	The input array is
  1   2   3   4   5   6   7  22  23  24 
  2   3   4   5   6   7   8  22  23  24 
  3   6   8   9  10  11  12  23  23  24
  4   6   9   9  10  12  23  24  24  25
  6   6   9  10  10  12  24  25  25  25
  9   9  10  10  12  12  24  32  32  38
  9  10  10  10  23  23  25  32  33  38
 12  12  12  23  24  24  25  33  38  39
 23  23  24  24  25  25  32  38  38  39
 24  24  24  24  32  32  32  39  41  43
	*/
	
	return input[x][y];
	
}

void cal_single(int k) {
	int Kx, Ky, numconst, mid = LENGTH, i=0, j=0, c1=0; // Kx, Ky : k값 원소의 좌표 저장, numconst : 중복 참조를 막기 위한 상수 변수, mid : 기준점의 x, y 좌표, i, j, c1 : while, for문 상수 변수

	while(c1<LENGTH){
		numconst = access_value(c1,c1);
		if (k <= numconst){
			mid = c1;
			break;
		}
		c1++;
	} //기준점 설정
	
	if(mid == LENGTH){
		return;
	} //기준점이 없으면 함수 return
	
	if(k == numconst){
		Kx = c1;
		Ky = c1;
		printf("(%d,%d)\n",Kx,Ky);
		return;
	}
	
	i=0; j=1;
	while( mid-j >= 0){
		if(access_value(mid-j,mid) <= k){
			i=0;
			while( mid+i < LENGTH){
				numconst = access_value(mid-j,mid+i);
				if(k == numconst){
					Kx = mid-j;
					Ky = mid+i;
					printf("(%d,%d)\n",Kx,Ky);
					return;
				}
				else if(k < numconst){
					break;
				}
			i++;
			}
		}
		j++;
	} // 기준점을 기준으로 오른쪽 위 영역의 원소들 조사
	
	i=1; j=0;
	while( mid - i >= 0){
		if(access_value(mid,mid-i) <= k){
			j=0;
			while( mid +j < LENGTH){
				numconst = access_value(mid+j,mid-i);
				if(k == numconst){
					Kx = mid+j;
					Ky = mid-i;
					printf("(%d,%d)\n",Kx,Ky);
					return;
				}
				else if(k<numconst){
					break;
				}
			j++;
			}
		}
		i++;
	} // 기준점을 기준으로 왼쪽 아래 영역의 원소들 조사
	
}

void cal_all(int k) {
	int *Kx, *Ky, Knum=0, numconst, mid = LENGTH, i=0, j=0, c1=0; // Kx, Ky : k값 원소들의 x, y좌표를 저장하는 1차원 배열, Knum : k값 원소의 개수. 나머지는 동일
	
	Kx=(int*)calloc(LENGTH*LENGTH,sizeof(int));
	Ky=(int*)calloc(LENGTH*LENGTH,sizeof(int));
	for(i=0;i<LENGTH*LENGTH;i++){
		Kx[i] = 0;
		Ky[i] = 0;
	} // Kx, Ky를 크기 LENGTH*LENGTH만큼 동적 할당하여 1차원 배열 생성.

	while(c1<LENGTH){
		numconst = access_value(c1,c1);
		if (k <= numconst){
			mid = c1;
			break;
		}
		c1++;
	} // 기준점의 좌표 저장.
	
	if(mid == LENGTH){
		return;
	}
	
	i = 1; j = 0;
	
	if(k == numconst){
		Kx[0] = c1;
		Ky[0] = c1;
		Knum++;
		while( mid+i < LENGTH){
			numconst = access_value(mid+j,mid+i);
			if(k == numconst){
				Kx[Knum] = mid+j;
				Ky[Knum] = mid+i;
				Knum++;
			}
			else if(k < numconst){
				break;
			}
			i++;
		}
		j++;
		while(mid+j <LENGTH){
			if(access_value(mid+j,mid) > k)
				break;
			i=0;
			while( mid+i < LENGTH){
				numconst = access_value(mid+j,mid+i);
				if(k == numconst){
					Kx[Knum] = mid+j;
					Ky[Knum] = mid+i;
					Knum++;
				}
				else if(k < numconst){
					break;
				}
				i++;
			}
			j++;
		}
	} // 기준점 = k값인 경우, 오른쪽 아래의 원소들 조사
	
	i=0; j=1;
	while( mid-j >= 0){
		if(access_value(mid-j,mid) <= k){
			i=0;
			while( mid+i < LENGTH){
				numconst = access_value(mid-j,mid+i);
				if(k == numconst){
					Kx[Knum] = mid-j;
					Ky[Knum] = mid+i;
					Knum++;
				}
				else if(k < numconst){
					break;
				}
			i++;
			}
		}
		j++;
	} // 기준점을 기준으로 오른쪽 위 영역의 원소들 조사
	
	i=1; j=0;
	while( mid - i >= 0){
		if(access_value(mid,mid-i) <= k){
			j=0;
			while( mid +j < LENGTH){
				numconst = access_value(mid+j,mid-i);
				if(k == numconst){
					Kx[Knum] = mid+j;
					Ky[Knum] = mid-i;
					Knum++;
				}
				else if(k<numconst){
					break;
				}
			j++;
			}
		}
		i++;
	} // 기준점을 기준으로 왼쪽 아래 영역의 원소들 조사
	
	if(Knum == 0)
		return; // k값 원소가 없는 경우 함수 return
	
	for(i=0;i<Knum-1;i++)
		printf("(%d,%d), ",Kx[i],Ky[i]);
	printf("(%d,%d)",Kx[Knum-1],Ky[Knum-1]); // k값 원소들의 좌표를 출력
	
	return;
}


int main(void) {
	int i,j,k;

	k=24;
	printf("k is %d.\n",k);

	count=0;
	printf("\nFinding any single k\n");
	cal_single(k);
	printf("\nCount=%d\n",count);

	count=0;
	printf("\nFinding all k\n");
	cal_all(k);
	printf("\nCount=%d\n",count);

}
