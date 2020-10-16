/* Opens file and reads it one byte at a time */
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	char ch;
	FILE *ptr;
	ptr = fopen(argv[1], "r");
	if (ptr == NULL) {
	    printf("Error opening file.\n");
	} else {
	    ch = fgetc(ptr);
	    while (ch != EOF) {
		printf("Character = %c\n", ch);
		ch = fgetc(ptr);
	    }
	}
	return 0;
}
