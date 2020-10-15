#include<stdio.h>
#include"PSW.h"
#define OLD_LEFT_FLIPPER 0x80
#define OLD_RIGHT_FLIPPER 0x40
#define NEW_LEFT_FLIPPER 0x8000
#define NEW_RIGHT_FLIPPER 0x4000

/* Declarations */
void rollPSW();
void pressLeftButton();
void pressRightButton();
int leftFlipperFired();
int rightFlipperFired();

/* Obtain PSW for function */
static unsigned short *getPSW() {
	static unsigned short actualPSW;
	return &actualPSW;
}

/* Shifts PSW 8 bits */
void rollPSW() {
	unsigned short *oldPSW;
	unsigned short *psw;
	psw = getPSW();
	oldPSW = psw;
	*psw = *oldPSW >> 8;
	fprintf(stderr, "Roll PSW from 0x%X to 0x%X\n", *oldPSW, *psw);
}

void pressLeftButton() {
	unsigned short *psw = getPSW();
	*psw = *psw | NEW_LEFT_FLIPPER;
	fprintf(stderr, "Press left fires left flipper PSW = 0x%X\n", *psw);
}

void pressRightButton() {
	unsigned short *psw = getPSW();
	*psw = *psw | NEW_RIGHT_FLIPPER;
	fprintf(stderr, "Press left fires left flipper PSW = 0x%X\n", *psw);
}

int leftFlipperFired() {
	unsigned short *psw = getPSW();
	return ((*psw & NEW_LEFT_FLIPPER) && !(*psw & OLD_LEFT_FLIPPER));
}

int rightFlipperFired() {
	unsigned short *psw = getPSW();
	return ((*psw & NEW_RIGHT_FLIPPER) && !(*psw & OLD_RIGHT_FLIPPER));
}
