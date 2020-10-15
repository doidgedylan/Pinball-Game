/* Author: Dylan Doidge 
Lab4*/
/* The lab simulates a game of pinball from the user's input and will display the interactions between
the walls and flippers of the game.  It will also show the positioning of the balls at relative times
with their speeds and the time each ball exits the game.
*/

#include<stdio.h>
#include<stdlib.h>
#include"ballstructs.h"
#include"constants.h"
#include"linkedlist.h"
#include"PSW.h"

/* Declarations */
void readAll(Node **p2head);
int goesInFrontOf(void *d1, void *d2);
OneBall *allocateBall();
void doThis(void *data);
void printAll(Node *p2head);
void printNodes(void *data);
int leftWall(OneBall *b);
int rightWall(OneBall *b);
int topWall(OneBall *b);
void physics(OneBall *b);
void updateOneBall(void *data);
void oneSimStep(Node **p2head);
int mustGo(void *data);
void disposal(void *data);
int leftFlipper(OneBall *b);
int rightFlipper(OneBall *b);
void interpChar(char ch);

int main(int argc, char *argv[]) {
	FILE *fp;
	int ch;
	Node *headPtr;
	float time = 0.0;
	headPtr = NULL;
	/* File open */
	fp = fopen(argv[1], "r");
	readAll(&headPtr);
	printf("Ball\t____X____\t____Y____\t____VX____\t____VY____\n");
	fprintf(stderr, "Time is %.2f seconds.\n", time);
	printAll(headPtr);
	while (headPtr != NULL) {
	    time = time + TIME_INT;
	    fprintf(stderr, "Time is %.2f seconds.\n", time);
	    rollPSW();
	    if (fp) {
	    	ch = fgetc(fp);
	        interpChar(ch);
	    }
	    /* Adjust ball data */
	    oneSimStep(&headPtr);
	}
	/* File close */
	if (fp) {
	    fclose(fp);
	    fprintf(stderr, "Closing ui file\n");
	}
	return 0;
}

/* Interpret each character of ui file */
void interpChar(char ch) {
	if (ch == 'L') {
	    pressLeftButton();
	} else if (ch == 'R') {
	    pressRightButton();
	} else if (ch == 'X') {
	    pressLeftButton();
	    pressRightButton();
	} else if (ch != EOF) {
	    fprintf(stderr, "UI is ignoring '%c'\n", ch);
	}
}

/* Read data file and populate linked list */
void readAll(Node **p2head) {
	OneBall localBall;
	OneBall *wp;
	while (scanf("%i%f%f%f%f", &(localBall.ball_name), &(localBall.x), &(localBall.y), &(localBall.vx), &(localBall.vy)) == 5) {
	    wp = allocateBall();
	    if (wp != NULL) {
	    *wp = localBall;
	    insert(p2head, wp, &goesInFrontOf);
	    } else {
		return;
	    }
	}
}

/* Allocate ball and store counter data */
OneBall *allocateBall() {
	OneBall *ball;
	static int counter = 0;
	ball = malloc(sizeof(OneBall));
	if (ball == NULL) {
	    fprintf(stderr, "Error allocating memory\n");
	} else {
	    counter = counter + 1;
	    fprintf(stderr, "%i ball(s) allocated\n", counter);
	}
	return ball;
}

/* Linked list comparison function */
int goesInFrontOf(void *data1, void *data2) {
	OneBall *ball1;
	OneBall *ball2;
	ball1 = data1;
	ball2 = data2;
	return (ball1->ball_name < ball2->ball_name);
}

/* Print data from nodes */
void printAll(Node *head) {
	traverse(head, printNodes);
	printf("\n");
}

void printNodes(void *data) {
	OneBall *ptr;
	ptr = data;
	printf("%c\t%9.4f\t%9.4f\t%9.4f\t%9.4f\n", ptr->ball_name, ptr->x, ptr->y, ptr->vx, ptr->vy);
}

/* Updates all balls in list */
void oneSimStep(Node **p2head) {	
	OneBall *ptr;
	/* Apply constraints and physics to each ball */
	traverse(*p2head, updateOneBall);
	deleteSome(p2head, &mustGo, &disposal);
	printAll(*p2head);
}

/* Applies constraints to one ball */
void updateOneBall(void *data) {
	OneBall *ball;
	int i;
	int (*fp_walls[5])(OneBall*) = {leftWall, rightWall, topWall, leftFlipper, rightFlipper};
	ball = data;
	physics(ball);
	/* Apply all three wall constraints */
	for (i = 0; i < 5; i++) {
	    if (fp_walls[i](ball)) {
		i =- 1;
	    }
	}
}

int leftWall(OneBall *ball) {
	int result = 0;
	if (ball->x < 0) {
	    fprintf(stderr, "Ball %c hits left wall at pos (%.2f, %.2f) vel (%.2f, %.2f)\n", ball->ball_name, ball->x, 
		ball->y, ball->vx, ball->vy);
	    ball->x = -(ball->x);
	    ball->vx = -(ball->vx);
	    result = 1;
	}
	return result;
}

int rightWall(OneBall *ball) {
	int result = 0;
	if (ball->x > X_WIDTH) {
	    fprintf(stderr, "Ball %c hits right wall at pos (%.2f, %.2f) vel (%.2f, %.2f)\n", ball->ball_name, ball->x, ball->y, 			ball->vx, ball->vy);
	    ball->x = X_WIDTH - ((ball->x) - X_WIDTH);
	    ball->vx = -(ball->vx);
	    result = 1;
	}
	return result;
}

int topWall(OneBall *ball) {
	int result = 0;
	if (ball->y > Y_DEPTH) {
	    fprintf(stderr, "Ball %c hits top wall at pos (%.2f, %.2f) vel (%.2f, %.2f)\n", ball->ball_name, 
		ball->x, ball->y, ball->vx, ball->vy);
	    ball->y = Y_DEPTH - ((ball->y) - Y_DEPTH);
	    ball->vy = -(ball->vy);
	    result = 1;
	}
	return result;
}

/* Adjusts data based on if flipper fires */
int leftFlipper(OneBall *ball) {
	int result = 0;
	if ((ball->y < 0) && (ball->x <= 10) && (ball->x >=5) && (ball->vy > -950) && (leftFlipperFired())) {
	    fprintf(stderr, "Left flipper hits ball at pos (%.2f, %.2f) vel (%.2f, %.2f)\n", 
		ball->x, ball->y, ball->vx, ball->vy);
	    if (ball->vx < 0) {
		ball->vx = -(ball->vx);
	    }
	    ball->y = -(ball->y);
	    ball->vy = -(ball->vy);
	    result = 1;
	}
	return result;
}

/* Adjusts data based on if flipper fires */
int rightFlipper(OneBall *ball) {
	int result = 0;
	if ((ball->y < 0) && (ball->x <= 17) && (ball->x >=12) && (ball->vy > -950) && (rightFlipperFired())) {
	    fprintf(stderr, "Right flipper hits ball at pos (%.2f, %.2f) vel (%.2f, %.2f)\n", 
		ball->x, ball->y, ball->vx, ball->vy);
	    if (ball->vx > 0) {
		ball->vx = -(ball->vx);
	    }
	    ball->y = -(ball->y);
	    ball->vy = -(ball->vy);
	    result = 1;
	}
	return result;
}

void physics(OneBall *ball) {
	ball->x = ball->x + (ball->vx * TIME_INT);
	ball->y = ball->y + (ball->vy * TIME_INT);
	ball->vy = ball->vy + (Y_ACCEL * TIME_INT);
}

/* Specifies criteria for ball freeing */
int mustGo(void *data) {
	OneBall *ball;
	ball = data;
	return (ball->y < 0);
}

/* Frees ball and counts number of frees */
void disposal(void *data) {
	OneBall *ball;
	static int counter = 0;
	ball = data;
	fprintf(stderr, "Ball %c leaves the table pos(%.2f, %.2f)\n", ball->ball_name, ball->x, ball->y);
	free(ball);
	counter = counter + 1;
	fprintf(stderr, "%i ball(s) freed\n", counter);
}



