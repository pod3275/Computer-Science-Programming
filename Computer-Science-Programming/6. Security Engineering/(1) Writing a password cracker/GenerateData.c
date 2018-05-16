#include "fastpbkdf2.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef void (*pbkdf2_fn)(const uint8_t *pw, size_t npw,
                          const uint8_t *salt, size_t nsalt,
                          uint32_t iterations,
                          uint8_t *out, size_t nout);

int main(void) {
	int i = 0, j, n = 0, count, csymbols;
	uint8_t **datalist;
	uint8_t buffer[200], buffer2[16];
	FILE *fp, *fp2, *fp3, *fp4;

	datalist = (uint8_t**) malloc(200000 * sizeof(uint8_t*));
	for (i = 0; i < 200000; i++)
		datalist[i] = (uint8_t*) malloc(16 * sizeof(uint8_t));


	fopen_s(&fp, "mostpasswords.txt", "r");
	fopen_s(&fp2, "passwordlist.txt", "w");


	for (i = 0; i < sizeof(buffer); i++)
		buffer[i] = 0;


	while ( fgets(buffer, 200, fp) != NULL ) {
		count = 0;
		csymbols = 0;

		for (i = 0; i < sizeof(buffer); i++) {
			if (buffer[i] == '\n') {
				buffer[i] = '\0';
			}
			if (buffer[i] >= '0' && buffer[i] <= '9')
				count++;
			if (buffer[i] == '!' || buffer[i] == '@')
				csymbols++;
		}

		if (strlen(buffer) >= 6 && strlen(buffer) <= 10) {

			if (count == 0) {
				buffer[strlen(buffer)] = '1';
				buffer[strlen(buffer)+1] = '\0';
				fprintf(fp2, "%s\n", buffer);
				n++;
			}

			else if (count != 0) {
				fprintf(fp2, "%s\n", buffer);
				n++;
			}

			if (buffer[0] >= 'a' && buffer[0] <= 'z') {
				fprintf(fp2, "%c", buffer[0] - 32);
				for (i = 1; i<strlen(buffer); i++)
					fprintf(fp2, "%c", buffer[i]);
				fprintf(fp2, "\n");

				n++;
			}

			if (csymbols == 0) {
				fprintf(fp2, "%s%c\n", buffer, '!');
				n++;
			}

			
		}

		for (i = 0; i < sizeof(buffer); i++) {
			buffer[i] = 0;
		}
	}

	printf("%d\n", n);

	fclose(fp);
	fclose(fp2);

	fopen_s(&fp3, "passwordlist.txt", "r");
	fopen_s(&fp4, "hashlist.txt", "w");

	i = 0;
	while (fgets(datalist[i], 16, fp3) != NULL) {
		for (j = 0; j < strlen(datalist[i]); j++) {
			if (datalist[i][j] == '\n') {
				datalist[i][j] = '\0';
			}
		}
		i++;
	}

	for (i = 0; i < n; i++) {
		fastpbkdf2_hmac_sha1(datalist[i], strlen(datalist[i]), "seclab", 6, 500, buffer2, 16);
		for (j = 0; j < 16; j++) {
			fprintf(fp4, "%02x", buffer2[j]);
		}
		fprintf(fp4, "\n");
	}

  return 0;
}
