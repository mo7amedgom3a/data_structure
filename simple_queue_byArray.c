#include <stdio.h>
#include <stdlib.h>
//******************************************simple queue by array************************
#define MAX_SIZE 100

typedef struct Queue
{
	int items[MAX_SIZE];
	int front;
	int rear;
} Queue;
// mo7amed gom3a
//*******************************************function declaration************************
Queue *createQueue();
int isEmpty(Queue *queue);
int isFull(Queue *queue);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int peek(Queue *queue);
void display(Queue *queue);
//***************************************************************************************
// Function to create an empty queue
Queue *createQueue()
{
	Queue *queue = malloc(sizeof(Queue));
	queue->front = -1;
	queue->rear = -1;
	return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue *queue)
{
	return (queue->front == -1);
}

// Function to check if the queue is full
int isFull(Queue *queue)
{
	return (queue->rear == MAX_SIZE - 1);
}

// Function to enqueue an element
void enqueue(Queue *queue, int data)
{
	if (isFull(queue))
	{
		printf("Queue is full. Cannot enqueue element.\n");
		return;
	}

	if (isEmpty(queue))
	{
		queue->front = 0;
	}

	queue->rear++;
	queue->items[queue->rear] = data;
}

// Function to dequeue an element
int dequeue(Queue *queue)
{
	if (isEmpty(queue))
	{
		printf("Queue is empty. Cannot dequeue element.\n");
		return -1;
	}

	int data = queue->items[queue->front];
	if (queue->front == queue->rear)
	{
		queue->front = -1;
		queue->rear = -1;
	}
	else
	{
		queue->front++;
	}

	return data;
}

// Function to peek at the front element of the queue
int peek(Queue *queue)
{
	if (isEmpty(queue))
	{
		printf("Queue is empty. No elements to peek.\n");
		return -1;
	}

	return queue->items[queue->front];
}

// Function to print the elements of the queue
void display(Queue *queue)
{
	if (isEmpty(queue))
	{
		printf("Queue is empty. No elements to display.\n");
		return;
	}

	printf("Queue elements: ");
	for (int i = queue->front; i <= queue->rear; i++)
	{
		printf("%d ", queue->items[i]);
	}
	printf("\n");
}

int main()
{
	Queue *queue = createQueue();

	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);
	enqueue(queue, 40);

	display(queue); // Output: Queue elements: 10 20 30 40

	printf("Front element: %d\n", peek(queue)); // Output: Front element: 10

	dequeue(queue);
	dequeue(queue);

	display(queue); // Output: Queue elements: 30 40

	printf("Front element: %d\n", peek(queue)); // Output: Front element: 30

	return 0;
}