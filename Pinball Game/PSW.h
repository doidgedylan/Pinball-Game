/* declarations of the public functions found in psw.c 
 * THis file is included by files that want to call into psw.c */

/* functions to tell the PSW to do things */
void rollPSW();

void pressLeftButton();
void pressRightButton();

/* functions to ask questions of the PSW */

int leftFlipperFired();
int rightFlipperFired();
