#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 144

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s [input file] [output file]\n", argv[0]);
		exit(1);
	}
	char *readFilename = argv[1];
	char *writeFilename = argv[2];
	FILE *wavFileRead = fopen(readFilename, "rb");
	if (wavFileRead == NULL) {
		fprintf(stderr, "Error: Could not open read file.\n");
		exit(1);
	}
	FILE *wavFileWrite = fopen(writeFilename, "wb");
	if (wavFileWrite == NULL) {
		fprintf(stderr, "Error: Could not open write file.\n");
		fclose(wavFileRead);
		exit(1);
	}
	short header[HEADER_SIZE];
	short amplitude;
	int n;
	if (n = fread(header, HEADER_SIZE, 1, wavFileRead) == 0) {
		fprintf(stderr, "Error: File too short.\n");
		fclose(wavFileWrite);
		fclose(wavFileRead);
		exit(1);
	}
	// Make the audio 7 semitones higher
	fwrite(header, HEADER_SIZE, 1, wavFileWrite);
	int cnt = 0;
	while (n = fread(&amplitude, sizeof(short), 1, wavFileRead) > 0) {
		if (cnt % 3 > 0) {
			fwrite(&amplitude, sizeof(short), 1, wavFileWrite);
		}
		cnt++;
	}
	if (n == 0 && ferror(stdin)) {
		perror("fread");
		fclose(wavFileWrite);
		fclose(wavFileRead);
		exit(1);
	}

	fclose(wavFileRead);
	if (fclose(wavFileWrite) == EOF) {
		perror("fclose");
		exit(1);
	}
}
