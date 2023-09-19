#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
//******************************************double ended queue (Deque)*****************************
// Structure to represent the deque
typedef struct {
	int arr[MAX_SIZE];
	int front;
	int rear;
	int size;
} Deque;
//******************************************function declaration***********************************
Deque *createDeque();
int isEmpty(Deque *deque);
int isFull(Deque *deque);
void insertFront(Deque *deque, int data);
void insertRear(Deque *deque, int data);
void deleteFront(Deque *deque);
void deleteRear(Deque *deque);
int getFront(Deque *deque);
int getRear(Deque *deque);
int getSize(Deque *deque);
void displayDeque(Deque *deque);
int contains(Deque *deque, int data);
void clearDeque(Deque *deque);
void destroyDeque(Deque *deque);
//*************************************************************************************************

// Function to create an empty deque
Deque *createDeque()
{
	Deque* deque = malloc(sizeof(Deque));
	deque->front = -1;
	deque->rear = -1;
	deque->size = 0;
	return deque;
}

// Function to check if the deque is empty
int isEmpty(Deque* deque) {
	return deque->size == 0;
}

// Function to check if the deque is full
int isFull(Deque* deque) {
	return deque->size == MAX_SIZE;
}

// Function to insert an element at the front of the deque
void insertFront(Deque* deque, int data) {
	if (isFull(deque)) {
		printf("Deque is full.\n");
		return;
	}
	if (isEmpty(deque)) {
		deque->front = 0;
		deque->rear = 0;
	}
	else
	{
		deque->front = (deque->front - 1 + MAX_SIZE) % MAX_SIZE;
	}
	deque->arr[deque->front] = data;
	deque->size++;
}

// Function to insert an element at the rear of the deque
void insertRear(Deque* deque, int data) {
	if (isFull(deque))
	{
		printf("Deque is full.\n");
		return;
	}
	if (isEmpty(deque))
	{
		deque->front = 0;
		deque->rear = 0;
	}
	else
	{
		deque->rear = (deque->rear + 1) % MAX_SIZE;
	}
	deque->arr[deque->rear] = data;
	deque->size++;
}

// Function to delete an element from the front of the deque
void deleteFront(Deque* deque) {
	if (isEmpty(deque))
	{
		printf("Deque is empty.\n");
		return;
	}
	if (deque->front == deque->rear)
	{
		deque->front = -1;
		deque->rear = -1;
	} 
	else
	{
		deque->front = (deque->front + 1) % MAX_SIZE;
	}
	deque->size--;
}

// Function to delete an element from the rear of the deque
void deleteRear(Deque* deque) {
	if (isEmpty(deque))
	{
		printf("Deque is empty.\n");
		return;
	}
	if (deque->front == deque->rear)
	{
		deque->front = -1;
		deque->rear = -1;
	}
	else
	{
		deque->rear = (deque->rear - 1 + MAX_SIZE) % MAX_SIZE;
	}
	deque->size--;
}

// Function to get the front element of the deque
int getFront(Deque* deque) {
	if (isEmpty(deque))
	{
		printf("Deque is empty.\n");
		return -1;
	}
	return (deque->arr[deque->front]);
}

// Function to get the rear element of the deque
int getRear(Deque* deque) {
	if (isEmpty(deque))
	{
		printf("Deque is empty.\n");
		return -1;
	}
	return (deque->arr[deque->rear]);
}
// Function to get the current size of the deque
int getSize(Deque *deque)
{
	return deque->size;
}

// Function to display the elements of the deque
void displayDeque(Deque *deque)
{
	if (isEmpty(deque))
	{
		printf("Deque is empty.\n");
		return;
	}

	printf("Deque elements: ");
	int i = deque->front;

	while (i != deque->rear)
	{
		printf("%d ", deque->arr[i]);
		i = (i + 1) % MAX_SIZE;
	}
	printf("%d\n", deque->arr[deque->rear]);
}
// Function to check if an element exists in the deque
int contains(Deque *deque, int data)
{
	if (isEmpty(deque))
	{
		return 0;
	}

	int i = deque->front;
	while (i != deque->rear)
	{
		if (deque->arr[i] == data)
		{
			return 1;
		}
		i = (i + 1) % MAX_SIZE;
	}

	if (deque->arr[deque->rear] == data)
	{
		return 1;
	}

	return 0;
}

// Function to clear the deque, removing all elements
void clearDeque(Deque *deque)
{
	deque->front = -1;
	deque->rear = -1;
	deque->size = 0;
}

// Function to destroy the deque, freeing the memory
void destroyDeque(Deque *deque)
{
	clearDeque(deque);
	free(deque);
}
int main()
{
	Deque *deque = createDeque();

	insertFront(deque, 10);
	insertFront(deque, 20);
	insertRear(deque, 30);
	insertRear(deque, 40);

	printf("Front element: %d\n", getFront(deque)); // Output: Front element: 20
	printf("Rear element: %d\n", getRear(deque));   // Output: Rear element: 40

	deleteFront(deque);
	deleteRear(deque);

	printf("Size of deque: %d\n", getSize(deque)); // Output: Size of deque: 2

	printf("Is deque empty? %s\n", isEmpty(deque) ? "Yes" : "No"); // Output: Is deque empty? No

	displayDeque(deque); // Output: Deque elements: 10 30

	int searchData = 10;
	printf("Does deque contain %d? %s\n", searchData, contains(deque, searchData) ? "Yes" : "No"); // Output: Does deque contain 10? Yes

	clearDeque(deque);

	printf("Is deque empty? %s\n", isEmpty(deque) ? "Yes" : "No"); // Output: Is deque empty? Yes

	destroyDeque(deque);

	return 0;
}