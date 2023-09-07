#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// ************************ struct area *************************************
// Node structure for the linked list
typedef struct Node
{
	int data;	   // Data stored in the node
	struct Node *next; // Pointer to the next node
} Node;

// Linked list structure
typedef struct LinkedList
{
	Node *head; // Pointer to the first node in the list
	int size;   // Number of nodes in the list
} LinkedList;
// **************************************************************************

//*************************function declaration******************************
void initializeLinkedList(LinkedList *list);
int isEmpty(LinkedList *list);
int getSize(LinkedList *list);
void insertAtBeginning(LinkedList *list, int data);
void insertAtEnd(LinkedList *list, int data);
void insertAtPosition(LinkedList *list, int data, int position);
bool search(LinkedList *head, int value);
void deleteFromBeginning(LinkedList *list);
void deleteFromEnd(LinkedList *list);
void deleteFromPosition(LinkedList *list, int position);
void reverseLinkedList(LinkedList *head);
void displayLinkedList(LinkedList *list);
void destroyLinkedList(LinkedList *list);
//***************************************************************************

// Function to initialize an empty linked list
void initializeLinkedList(LinkedList *list)
{
	list->head = NULL;
	list->size = 0;
}

// Function to check if the linked list is empty
int isEmpty(LinkedList *list)
{
	return list->size == 0;
}

// Function to get the size of the linked list
int getSize(LinkedList *list)
{
	return list->size;
}

// Function to insert a new node at the beginning of the linked list
void insertAtBeginning(LinkedList *list, int data)
{
	Node *newNode = malloc(sizeof(Node)); // عملت نود جديدة 
	newNode->data = data;

	newNode->next = list->head; //head خلي النود الجديدة تشاور علي ال 
	list->head = newNode; //new nodeيشاور علي ال  head خلي بقا ال 
	list->size++; // عشان زودنا نود
}

// Function to insert a new node at the end of the linked list
void insertAtEnd(LinkedList *list, int data)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL; // NULLفي كل الأحوال هتشاور علي 

	// لو مفيش نود عندي في اللينكد ليست ضيف النود في الاول 
	if (isEmpty(list))
	{
		list->head = newNode;
	}
	else
	{
		// هعمل نود امشي بيها علي اللينكد ليست لغاية ماوصل لأخر نود
		Node *current = list->head;

		// طالما مش وصلت لأخر نود في اللينكد ليست
		while (current->next != NULL)
		{
			current = current->next; // i++ زي ال 
		}

		current->next = newNode; // خلي أخر نود تشاور علي النود الجديدة 
	}

	list->size++; // زود بقا عدد النود بواحد
}

// Function to insert a new node at a specific position in the linked list
void insertAtPosition(LinkedList *list, int data, int position)
{
	if (position < 0 || position > list->size)
	{
		printf("Error: Invalid position.\n");
		return;
	}
	//  بيساوي صفر روح حط النود في بداية الليست pos لو ال 
	if (position == 0)
	{
		insertAtBeginning(list, data);
	}
	//روح حط العنصر في نهاية اللينكد ليست size لو بتساوي ال 
	else if (position == list->size)
	{
		insertAtEnd(list, data);
	}
	else
	{
		Node *newNode = malloc(sizeof(Node));
		newNode->data = data;

		Node *current = list->head; // temp node to iterator on list
		int currentPosition = 0; // pos عشان نقف عند النود إلي قبل النود إلي في ال 

		while (currentPosition < position - 1)
		{
			current = current->next;
			currentPosition++;
		}
		//  pos خلي النود الجديدة تشاور علي النود إلي في ال
		newNode->next = current->next;
		//تشاور علي النود الجديدة pos خلي النود إلي قبل النود إلي في ال 
		current->next = newNode;
		list->size++;
	}
	
}
// A function that searches for a node
bool search(LinkedList *head, int value)
{
	 Node *current = head->head;
	while (current != NULL)
	{
		if (current->data == value)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

// Function to delete the first node from the linked list
void deleteFromBeginning(LinkedList *list)
{
	if (isEmpty(list))
	{
		printf("Error: Linked list is empty.\n");
		return;
	}

	Node *temp = list->head; // هحفظ النود في متغير عشان أقدر أحذفها 
	list->head = list->head->next; //تشاور علي تاني نود head خلي ال 
	free(temp);
	list->size--; // عشان حذفنا نود
}

// Function to delete the last node from the linked list
void deleteFromEnd(LinkedList *list)
{
	if (isEmpty(list))
		return;
	// لو مفيش غير نود واحدة بس إمسحها
	if (list->head->next == NULL)
	{
		free(list->head);
		list->head = NULL;
	}
	else
	{
		Node *current = list->head; // هيقف عند أخر نود
		Node *prev = NULL; // هيقف علي النود إلي قبل الأخيرة

		while (current->next != NULL)
		{
			prev = current;
			current = current->next;
		}
		free(current);
		prev->next = NULL;
	}
	list->size--;
}

// Function to delete a node from a specific position in the linked list
void deleteFromPosition(LinkedList *list, int position)
{
	if (isEmpty(list) || position < 0 || position >= list->size)
		return;

	if (position == 0) // لو عاوز يحذف أول نود
	{
		deleteFromBeginning(list);
	}
	else if (position == list->size - 1) // لو عاوز يحذف أخر نود 
	{
		deleteFromEnd(list);
	}
	else
	{
		Node *current = list->head;
		int i = 0;

		while (i < position - 1) // أقف عند النود إلي قبل النود إلي عاوز أحذفها
		{
			current = current->next;
			i++;
		}

		Node *temp = current->next; // هات النود إلي عاوز أحذفها 
		current->next = temp->next;
		free(temp);

		list->size--;
	}
}
// Function to display the linked list
void displayLinkedList(LinkedList *list)
{
	if (isEmpty(list))
	{
		printf("Linked list is empty.\n");
		return;
	}

	Node *current = list->head;

	while (current != NULL)
	{
		printf("%d ", current->data);
		current = current->next;
	}

	printf("\n");
}

// Function to free the memory allocated for the linked list
void destroyLinkedList(LinkedList *list)
{
	Node *current = list->head;
	Node *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	list->head = NULL;
	list->size = 0;
}
// reverse the linked list
void reverseLinkedList(LinkedList *head)
{
	struct Node *prev = NULL;
	struct Node *current = head->head;
	struct Node *next = NULL;

	while (current != NULL)
	{
		// Store the next node
		next = current->next;

		// Change next of current node
		current->next = prev;

		// Move pointers one position ahead
		prev = current;
		current = next;
	}
	head->head = prev;
}


int main()
{
	LinkedList *list;
	initializeLinkedList(list);

	insertAtBeginning(list, 10);
	insertAtEnd(list, 20);
	insertAtPosition(list, 30, 1);
	displayLinkedList(list); // Output: 10 30 20
	printf("%d\n",search(list,52));
	reverseLinkedList(list);
	displayLinkedList(list);

	deleteFromBeginning(list);
	deleteFromEnd(list);
	deleteFromPosition(list, 0);
	displayLinkedList(list); // Output: Linked list is empty.

	destroyLinkedList(list);

	return 0;
}