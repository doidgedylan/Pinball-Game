#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Declarations */
static Node *allocateNode();
static void deallocateNode(Node *n);

void traverse(Node *head, ActionFunction doThis) {
	Node *traversePtr;
	traversePtr = head;
	while (traversePtr != NULL)  {
	    /* Apply action function */
	    doThis(traversePtr->data);
	    traversePtr = traversePtr->next;
	}
}

void insert(Node **p2head, void *data, ComparisonFunction goesInFrontOf) {	
	Node *newNodePtr;
	Node *traversePtr;
	Node *priorNode;
	newNodePtr = allocateNode();
	newNodePtr->data = data;
	if (newNodePtr == NULL) {
	    fprintf(stderr, "Storage not allocated");
	} else if (*p2head == NULL) {
	    /* Head node is null */
	    *p2head = newNodePtr;
	    newNodePtr->next = NULL;
	    newNodePtr->prev = NULL;
	} else {
	    /* Head node is not null */
	    traversePtr = *p2head;
	    if (goesInFrontOf(newNodePtr->data, traversePtr->data)) {
		/* New node comes before head node */
		newNodePtr->next = traversePtr;
		traversePtr->prev = newNodePtr;
		traversePtr = NULL;
		*p2head = newNodePtr;
	    }
	    while (traversePtr != NULL) {
		if (goesInFrontOf(newNodePtr->data, traversePtr->data)) {
		    /* New node comes before traverse node */
		    newNodePtr->next = traversePtr;
		    newNodePtr->prev = traversePtr->prev;
		    traversePtr->prev->next = newNodePtr;
		    traversePtr->prev = newNodePtr;
		    traversePtr = NULL;
		} else if (traversePtr->next == NULL) {
		    /* New node appends to end of list */
		    traversePtr->next = newNodePtr;
		    newNodePtr->prev = traversePtr;
		    traversePtr = NULL;
		} else {
		    /* Continue with list */
		    traversePtr->prev = traversePtr;
		    traversePtr = traversePtr->next;
		}
	    }
	}
}

/* Allocates nodes and counts allocations */
static Node *allocateNode() {
	Node *node;
	static int counter = 0;
	node = malloc(sizeof(Node));
	if (node == NULL) {
	    fprintf(stderr, "Error allocating memory\n");
	} else {
	    counter = counter + 1;
	    fprintf(stderr, "%i node(s) allocated\n", counter);
	}
	return node;
}

void deleteSome(Node **p2head, CriteriaFunction mustGo, ActionFunction disposal) {
	Node *traversePtr;
	Node *priorNode;
	traversePtr = *p2head;
	if (*p2head != NULL) {
	    /* There are nodes in the list */
	    while (traversePtr != NULL) {
		if (mustGo(traversePtr->data)) {
		    /* Node data matches criteria */
		    if (traversePtr == *p2head) {
			/* Node is the head node */
			*p2head = traversePtr->next;
			disposal(traversePtr->data);
			deallocateNode(traversePtr);
			traversePtr = *p2head;
		    } else {
			/* Node is not the head node */
		    	priorNode->next = traversePtr->next;
		    	disposal(traversePtr->data);
		    	deallocateNode(traversePtr);
		    	traversePtr = priorNode->next;
		    }
		} else {
		    /* Continue with list */
		    priorNode = traversePtr;
		    traversePtr = priorNode->next;
		}
	    }
	} else {
	    fprintf(stderr, "Error: No nodes in list\n");
	}
}

/* Deallocates memory and counts deallocations */
static void deallocateNode(Node *ptr) {
	static int counter = 0;
	free(ptr);
	counter = counter + 1;
	fprintf(stderr, "%i node(s) freed\n", counter);
}


