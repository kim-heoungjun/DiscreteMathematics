#include <stdio.h>
#include <stdlib.h>


int main() {
	int num[81];
	int numcount = 0;
	int starnum[4];
	int starcount = 0;
	int c = 1, r = 1;
	char ch;
	FILE *fp1 = fopen("input.txt", "r");
	if (fp1 == NULL) {
		printf("File open error.\n");
		return 0;
	}
	while ((ch = fgetc(fp1)) != EOF)
	{
		if (ch >= '0' && ch <= '9') {
			if (ch != '0') {
				num[numcount++] = (ch - '0') + (r - 1) * 9 + (c - 1) * 81;
			}
			r++;
		}
		if (ch == '\n') {
			r = 1;
			c++;
		}
		if (ch == '*') {
			starnum[starcount++] = (r - 1) * 9 + (c - 1) * 81;
			r++;
		}

	}

	fclose(fp1);
	int i = 1, j = 1, n = 1;
	FILE *fp2 = fopen("formula.txt", "wt");
	if (fp2 == NULL) {
		printf("File write error.\n");
		return 0;
	}
	fprintf(fp2, "p cnf 729\n");
	for (int i = 1; i <= 9; i++) {
		for (int n = 1; n <= 9; n++) {
			for (int j = 1; j <= 9; j++) {
				int k = (j - 1) * 9 + (i - 1) * 81 + n;
				fprintf(fp2, "%d ", k);
			}
			fprintf(fp2, "0\n");
		}
	}

	for (j = 1; j <= 9; j++) {
		for (n = 1; n <= 9; n++) {
			for (i = 1; i <= 9; i++) {
				int k = (j - 1) * 9 + (i - 1) * 81 + n;
				fprintf(fp2, "%d ", k);
			}
			fprintf(fp2, "0\n");
		}
	}

	int s;
	for (r = 0; r <= 2; r++) {
		for (s = 0; s <= 2; s++) {
			for (n = 1; n <= 9; n++) {
				for (i = 1; i <= 3; i++) {
					for (j = 1; j <= 3; j++) {
						int k = ((j + (3 * s)) - 1) * 9 + (i + (3 * r) - 1) * 81 + n;
						fprintf(fp2, "%d ", k);
					}
				}
				fprintf(fp2, "0\n");
			}
		}
	}
	int m;
	for (i = 1; i <= 9; i++) {
		for (j = 1; j <= 9; j++) {
			for (n = 1; n <= 8; n++) {
				for (m = n + 1; m <= 9; m++) {
					fprintf(fp2, "-%d -%d 0\n", ((j - 1) * 9 + (i - 1) * 81 + n), ((j - 1) * 9 + (i - 1) * 81 + m));
				}
			}
		}
	}

	for (i = 0; i < numcount; i++) {
		fprintf(fp2, "%d 0\n", num[i]);
	}

	switch (starcount) {
	case 2:
		for (int n = 1; n <= 9; n++) {
			fprintf(fp2, "%d -%d 0\n", starnum[0] + n, starnum[1] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[1] + n, starnum[0] + n);
		}
		break;
	case 3:
		for (int n = 1; n <= 9; n++) {
			fprintf(fp2, "%d -%d 0\n", starnum[0] + n, starnum[1] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[0] + n, starnum[2] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[1] + n, starnum[0] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[1] + n, starnum[2] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[2] + n, starnum[0] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[2] + n, starnum[1] + n);
		}
		break;
	case 4:
		for (int n = 1; n <= 9; n++) {
			fprintf(fp2, "%d -%d 0\n", starnum[0] + n, starnum[1] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[0] + n, starnum[2] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[0] + n, starnum[3] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[1] + n, starnum[0] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[1] + n, starnum[2] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[1] + n, starnum[3] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[2] + n, starnum[0] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[2] + n, starnum[1] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[2] + n, starnum[3] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[3] + n, starnum[0] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[3] + n, starnum[1] + n);
			fprintf(fp2, "%d -%d 0\n", starnum[3] + n, starnum[2] + n);
		}
		break;
	}

	fclose(fp2);

	system("z3 -dimacs formula.txt > sat.txt");

	int su[81];
	int co = 1;
	int count = 0;
	FILE *fp3 = fopen("sat.txt", "r");
	if (fp3 == NULL) {
		printf("File3 open error.\n");
	}
	char ch2[10];
	while ((fscanf(fp3, "%s", ch2) != EOF)) {
		if (ch2[0] != 's' && ch2[0] != '-')
			su[count++] = atoi(ch2) % 9;
	}
	fclose(fp3);
	FILE *fp4 = fopen("output.txt", "w");
	for (i = 0; i < 81; i++) {
		if (su[i] == 0)
			su[i] = 9;
		if (co > 9) {
			fprintf(fp4, "\n");
			co = 1;
		}
		fprintf(fp4, "%d ", su[i]);
		co++;
	}
	fclose(fp4);
}
