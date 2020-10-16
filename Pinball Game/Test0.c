/* Tests number of command line arguments */
#include<stdio.h>

int main(int argc, char *argv[]) {
	int i;
	if (argc == 2) {
	    printf("There are %i command line arguments\n", argc);
	    for (i = 0; i < argc; i++) {
		printf("argv[%i] = %s\n", i, argv[i]);
	    }
	} else {
	    fprintf(stderr, "There are %i command line arguments\n", argc);
	    for (i = 0; i < argc; i++) {
		fprintf(stderr, "argv[%i] = %s\n", i, argv[i]);
	    }
	}
	return 0;
}
