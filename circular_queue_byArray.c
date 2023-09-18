#include <stdio.h>
#include <stdlib.h>
//******************************************circular queue by linked list**************************
#define MAX_SIZE 100

typedef struct CircularQueue
{
	int items[MAX_SIZE];
	int front;
	int rear;
} CircularQueue;
//******************************************function declaration***********************************
CircularQueue *createCircularQueue();
int isEmpty(CircularQueue *queue);
int isFull(CircularQueue *queue);
void enqueue(CircularQueue *queue, int data);
int dequeue(CircularQueue *queue);
int peek(CircularQueue *queue);
void display(CircularQueue *queue);
//*************************************************************************************************

// Function to create an empty circular queue
CircularQueue *createCircularQueue()
{
	CircularQueue *queue = malloc(sizeof(CircularQueue));
	queue->front = -1;
	queue->rear = -1;
	return queue;
}

// Function to check if the circular queue is empty
int isEmpty(CircularQueue *queue)
{
	return (queue->front == -1);
}

// Function to check if the circular queue is full
int isFull(CircularQueue *queue)
{
	return ((queue->rear + 1) % MAX_SIZE == queue->front);
}

// Function to enqueue an element
void enqueue(CircularQueue *queue, int data)
{
	if (isFull(queue))
	{
		printf("Circular queue is full. Cannot enqueue element.\n");
		return;
	}

	if (isEmpty(queue))
	{
		queue->front = 0;
	}

	queue->rear = (queue->rear + 1) % MAX_SIZE;
	queue->items[queue->rear] = data;
}

// Function to dequeue an element
int dequeue(CircularQueue *queue)
{
	if (isEmpty(queue))
	{
		printf("Circular queue is empty. Cannot dequeue element.\n");
		return -1;
	}

	int data = queue->items[queue->front];

	if (queue->front == queue->rear)
	{
		queue->front = -1;
		queue->rear = -1;
	}
	else
		queue->front = (queue->front + 1) % MAX_SIZE;

	return data;
}

// Function to peek at the front element of the circular queue
int peek(CircularQueue *queue)
{
	if (isEmpty(queue))
	{
		printf("Circular queue is empty. No elements to peek.\n");
		return -1;
	}

	return queue->items[queue->front];
}

// Function to print the elements of the circular queue
void display(CircularQueue *queue)
{
	if (isEmpty(queue))
	{
		printf("Circular queue is empty. No elements to display.\n");
		return;
	}

	printf("Circular queue elements: ");
	int i = queue->front;
	while (i != queue->rear)
	{
		printf("%d ", queue->items[i]);
		i = (i + 1) % MAX_SIZE;
	}
	printf("%d\n", queue->items[i]); // print last item
}

int main()
{
	CircularQueue *queue = createCircularQueue();

	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);
	enqueue(queue, 40);

	display(queue); // Output: Circular queue elements: 10 20 30 40

	printf("Front element: %d\n", peek(queue)); // Output: Front element: 10

	dequeue(queue);
	dequeue(queue);

	display(queue); // Output: Circular queue elements: 30 40

	printf("Front element: %d\n", peek(queue)); // Output: Front element: 30

	return 0;
}
