/* header file for singly linked list */

typedef struct Node{
	struct Node *next, *prev;
	void *data;
	}Node;

typedef void (* ActionFunction)( void *data);
typedef int (* ComparisonFunction)(void *data1, void *data2);
typedef int (* CriteriaFunction)(void *data);

/* signatures that the list code provides to the outside world */
void insert(Node **p2head, void *data, ComparisonFunction goesInFrontOf);
void deleteSome(Node **p2head, CriteriaFunction mustGo, 
		ActionFunction disposal);
void traverse(Node *head, ActionFunction doThis);


