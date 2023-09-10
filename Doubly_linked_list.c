#include <stdio.h>
#include <stdlib.h>
//*************************** struct Area ********************************
// Define a structure for a node in the doubly linked list
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Define a structure for the doubly linked list
typedef struct DoublyLinkedList
{
    Node *head;
    Node *tail;
    int size;
} DoublyLinkedList;
//************************************************************************
// mohamed gom3a
//*************************** function declaration ***********************
Node *createNode(int data);
DoublyLinkedList *createDoublyLinkedList();
int get_size(DoublyLinkedList *list);
int is_empty(DoublyLinkedList *list);
void insertAtBeginning(DoublyLinkedList *list, int data);
void insertAtEnd(DoublyLinkedList *list, int data);
void insertAtPosition(DoublyLinkedList *list, int data, int position);
void deleteAtBeginning(DoublyLinkedList *list);
void deleteAtEnd(DoublyLinkedList *list);
void deleteAtPosition(DoublyLinkedList *list, int position);
void printDoublyLinkedList(DoublyLinkedList *list);
void printDoublyLinkedListReverse(DoublyLinkedList *list);
Node *searchInDoublyLinkedList(DoublyLinkedList *list, int target);
void reverseDoublyLinkedList(DoublyLinkedList *list);
Node *findMiddle(DoublyLinkedList *list);
int isPalindrome(DoublyLinkedList *list);
void freeDoublyLinkedList(DoublyLinkedList *list);
//************************************************************************

// Function to create a new node
Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return (newNode);
}

// Function to create a new empty doubly linked list
DoublyLinkedList *createDoublyLinkedList()
{
    DoublyLinkedList *newList = malloc(sizeof(DoublyLinkedList));
    if (newList == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return (newList);
}
int get_size(DoublyLinkedList *list)
{
    return list->size;
}
int is_empty(DoublyLinkedList *list)
{
    return 1 ? list->size == 0 : 0;
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(DoublyLinkedList *list, int data)
{
    Node *newNode = createNode(data);
    if (is_empty(list))
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->size++;
}

// Function to insert a node at the end of the list
void insertAtEnd(DoublyLinkedList *list, int data)
{
    Node *newNode = createNode(data);
    if (is_empty(list))
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

// Function to insert a node at a given position
void insertAtPosition(DoublyLinkedList *list, int data, int position)
{
    if (position < 0 || position > list->size)
    {
        printf("Invalid position for insertion.\n");
        return;
    }

    if (position == 0)
    {
        insertAtBeginning(list, data);
    }
    else if (position == list->size)
    {
        insertAtEnd(list, data);
    }
    else
    {
        Node *newNode = createNode(data);
        Node *current = list->head;
        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        list->size++;
    }
}

// Function to delete a node at the beginning of the list
void deleteAtBeginning(DoublyLinkedList *list)
{
    if (list->head == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL)
    {
        list->head->prev = NULL;
    }
    free(temp);
    list->size--;
}

// Function to delete a node at the end of the list
void deleteAtEnd(DoublyLinkedList *list)
{
    if (list->tail == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    Node *temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL)
    {
        list->tail->next = NULL;
    }
    free(temp);
    list->size--;
}

// Function to delete a node at a given position
void deleteAtPosition(DoublyLinkedList *list, int position)
{
    if (position < 0 || position >= list->size)
    {
        printf("Invalid position for deletion.\n");
        return;
    }

    if (position == 0)
    {
        deleteAtBeginning(list);
    }
    else if (position == list->size - 1)
    {
        deleteAtEnd(list);
    }
    else
    {
        Node *current = list->head;
        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        list->size--;
    }
}

// Function to print the elements of the list
void printDoublyLinkedList(DoublyLinkedList *list)
{
    Node *current = list->head;
    printf("Doubly Linked List (Size: %d): ", list->size);
    while (current != NULL)
    {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
// Function to print the nodes of the doubly linked list in reverse order
void printDoublyLinkedListReverse(DoublyLinkedList *list)
{
    Node *current = list->tail;
    printf("Doubly Linked List in Reverse: ");
    while (current != NULL)
    {
        printf("%d <-> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

// Function to search for a value in the doubly linked list
Node *searchInDoublyLinkedList(DoublyLinkedList *list, int target)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (current->data == target)
        {
            return current; // Found the target value, return the node
        }
        current = current->next;
    }
    return NULL; // Target value not found in the list
}

// Function to reverse a doubly linked list in-place
void reverseDoublyLinkedList(DoublyLinkedList *list)
{
    Node *current = list->head;
    Node *temp = NULL;

    while (current != NULL)
    {
        // Swap next and prev pointers of the current node
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        // Move to the next node
        current = temp;
    }

    // Swap the head and tail pointers
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}
// Function to find the middle element of the doubly linked list
Node *findMiddle(DoublyLinkedList *list)
{
    Node *slow = list->head;
    Node *fast = list->head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
// Function to check if a doubly linked list is a palindrome
int isPalindrome(DoublyLinkedList *list)
{
    Node *middle = findMiddle(list);
    Node *current = middle->next;
    Node *prev = NULL;
    Node *temp;

    // Reverse the second half of the list
    while (current != NULL)
    {
        temp = current->next;
        current->next = prev;
        current->prev = temp;
        prev = current;
        current = temp;
    }

    // Compare the first and second halves for palindrome check
    Node *left = list->head;
    Node *right = prev;

    while (left != middle->next && right != NULL)
    {
        if (left->data != right->data)
        {
            return 0; // Not a palindrome
        }
        left = left->next;
        right = right->next;
    }

    return 1; // Palindrome
}

// Function to free memory occupied by the list
void freeDoublyLinkedList(DoublyLinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main()
{
    DoublyLinkedList *myList = createDoublyLinkedList();

    insertAtEnd(myList, 1);
    insertAtBeginning(myList, 2);
    insertAtEnd(myList, 3);
    insertAtBeginning(myList, 4);
    insertAtPosition(myList, 5, 2);

    printDoublyLinkedList(myList);

    deleteAtPosition(myList, 3);
    deleteAtEnd(myList);
    deleteAtBeginning(myList);

    printDoublyLinkedList(myList);

    freeDoublyLinkedList(myList);

    return 0;
}
