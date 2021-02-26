#include <stdio.h>
#include <stdlib.h>
#include "decrypt.h"

const int FILE_READ_BUFFER = 512;

int main() {
	FILE *input = fopen("input.gif", "rb");

	if(input == NULL) {
		printf("Input file open error\n");
		return 1;
	}

	int size = FILE_READ_BUFFER;
	char *buf = malloc(size);

	if(buf == NULL) {
		printf("Memory allocation error\n");
		return 1;
	}

	int c = 0;
	int n = 0;

	while((c = fgetc(input)) != EOF) {
		if(n >= size-1) {
			size += FILE_READ_BUFFER;
			buf = realloc(buf, size);

			if(buf == NULL) {
				printf("Memory allocation error\n");
				return 1;
			}
		}

		buf[n++] = c;
	}

	decryptImage(buf);

	FILE *output = fopen("output.gif", "wb");

	if(output == NULL) {
		printf("Output file open fail\n");
		return 1;
	}

	fwrite(buf, n, 1, output);
	fclose(output);
}
