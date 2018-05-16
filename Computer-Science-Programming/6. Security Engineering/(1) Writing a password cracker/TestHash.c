#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

int main() {
	FILE *fp, *fp2, *fp3, *fp4;
	uint8_t **uname, **uhash, **hashlist, **passwordlist;
	uint8_t buffer[200];
	int *match;
	int i, j, count = 0, nuser=0, nlist=0;
	time_t startTime = 0, endTime = 0;
	float gap;

	startTime = clock();
	
	uname = (uint8_t**)malloc(100000 * sizeof(uint8_t*));
	for (i = 0; i < 100000; i++)
		uname[i] = (uint8_t*)malloc(100 * sizeof(uint8_t));

	uhash = (uint8_t**)malloc(100000 * sizeof(uint8_t*));
	for (i = 0; i < 100000; i++)
		uhash[i] = (uint8_t*)malloc(50 * sizeof(uint8_t));

	hashlist = (uint8_t**)malloc(50000 * sizeof(uint8_t*));
	for (i = 0; i < 50000; i++)
		hashlist[i] = (uint8_t*)malloc(50 * sizeof(uint8_t));

	passwordlist = (uint8_t**)malloc(50000 * sizeof(uint8_t*));
	for (i = 0; i < 50000; i++)
		passwordlist[i] = (uint8_t*)malloc(10 * sizeof(uint8_t));

	match = (int*)malloc(100000 * sizeof(int));

	for (i = 0; i < 100000; i++) {
		for (j = 0; j < 100; j++)
			uname[i][j] = 0;
	}

	for (i = 0; i < 100000; i++) {
		for (j = 0; j < 50; j++)
			uhash[i][j] = 0;
	}

	for (i = 0; i < 50000; i++) {
		for (j = 0; j < 50; j++)
			hashlist[i][j] = 0;
	}

	for (i = 0; i < 50000; i++) {
		for (j = 0; j < 10; j++)
			passwordlist[i][j] = 0;
	}

	for (i = 0; i < 100000; i++)
		match[i] = 0;


	fopen_s(&fp, "hashedPasswords.txt", "r");
	fopen_s(&fp2, "hashlist.txt", "r");
	fopen_s(&fp3, "passwordlist.txt", "r");
	fopen_s(&fp4, "Passwords.txt", "w");
	

	while (fgets(buffer, 200, fp) != NULL) {

		i = 0; j = 0;
		while (buffer[i] != ':') i++;

		i++;

		while (buffer[i] != ':') {
			if (buffer[i] != ' ') {
				uname[nuser][j] = buffer[i];
				j++;
				i++;
			}
		}
		uname[nuser][j] = '\0';

		i++; j = 0;

		while (i < strlen(buffer)) {
			uhash[nuser][j] = buffer[i];
			j++;
			i++;
		}

		if (uhash[nuser][j - 1] == '\n')
			uhash[nuser][j - 1] = '\0';

		else if (feof(fp))
			uhash[nuser][j] = '\0';
		
		nuser++;
	}

	while (fgets(buffer, 50, fp2) != NULL) {
		buffer[32] = '\0';

		for (i = 0; i < 50; i++)
			hashlist[nlist][i] = buffer[i];
		
		nlist++;
	}
	

	nlist = 0;
	while (fgets(buffer, 50, fp3) != NULL) {

		for (i = 0; i < strlen(buffer); i++) {
			passwordlist[nlist][i] = buffer[i];
			if (passwordlist[nlist][i] == '\n')
				passwordlist[nlist][i] = '\0';
		}

		if (feof(fp3))
			passwordlist[nlist][i] = '\0';
		
		nlist++;
	}

	for (i = 0; i < nuser; i++) {
		count = 0;

		for (j=0; j < nlist; j++) {
			if (strcmp(hashlist[j], uhash[i]) == 0) {
				match[i] = j;
				count = 1;
			}
			if (count == 1)
				break;
		}

		if (count == 0)
			match[i] = 99999;
	}

	for (i = 0; i < nuser; i++) {
		if (match[i] == 99999)
			fprintf(fp4, "%d:%s:%s%d%c\n", i + 1, uname[i], uname[i], 1,'!');
		else
			fprintf(fp4, "%d:%s:%s\n", i + 1, uname[i], passwordlist[match[i]]);
	}

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);
	printf("파일 생성 성공. 소요시간 : %f 초\n", gap);

}