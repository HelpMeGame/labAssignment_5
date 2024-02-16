#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int count = 0;
	node* nextNode = head;
	while (nextNode != NULL)
	{
		count++;
		nextNode = nextNode->next;
	}

	return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	// get size of linkedList
	int count = length(head);

	char* finalString;

	// malloc final string
	finalString = (char*)calloc(sizeof(char)*(count + 1), count + 1);
	if (finalString == NULL)
	{
		exit(1);
	}

	// loop through nodes
	node* nextNode = head;
	for (int i = 0; i < count; i++)
	{
		finalString[i] = nextNode->letter;
		nextNode = nextNode->next;
	}

	// add string terminator
	finalString[count + 1] = "\0";

	return finalString;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{

	// malloc new node
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL)
	{
		exit(1);
	}

	newNode->letter = c;
	newNode->next = NULL;

	
	node* tempOld = *pHead;

	if (tempOld == NULL)
	{
		*pHead = newNode;
	}
	else
	{
		while (tempOld->next != NULL)
		{
			tempOld = tempOld->next;
		}
		tempOld->next = newNode;
	}


}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	// create vals
	node* next = *pHead;
	node* prev = NULL;

	// return if next is null
	if (next == NULL)
		return;

	// loop through nodes, freeing prev
	while (next->next != NULL)
	{
		prev = next;
		next = next->next;
		free(prev);
	}

	// free remaining node
	if (next != NULL)
		free(next);	

	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}