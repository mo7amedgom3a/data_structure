#include <stdio.h>
#include <stdlib.h>
//******************************************Queue by linked list*************************
// Queue Node
typedef struct QueueNode
{
	int data;
	struct QueueNode *next;
} QueueNode;

// Queue
typedef struct Queue
{
	QueueNode *front;
	QueueNode *rear;
} Queue;
//******************************************function declaration*************************
Queue *createQueue();
int isEmpty(Queue *queue);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int peek(Queue *queue);
void display(Queue *queue);
//***************************************************************************************

// Function to create an empty queue
Queue *createQueue()
{
	Queue *queue = malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue *queue)
{
	return (queue->front == NULL);
}

// Function to enqueue an element
void enqueue(Queue *queue, int data)
{
	QueueNode *newNode = malloc(sizeof(QueueNode));
	newNode->data = data;
	newNode->next = NULL;

	if (isEmpty(queue))
	{
		queue->front = newNode;
		queue->rear = newNode;
	}
	else
	{
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

// Function to dequeue an element
int dequeue(Queue *queue)
{
	if (isEmpty(queue))
	{
		printf("Queue is empty. Cannot dequeue element.\n");
		return -1;
	}

	QueueNode *temp = queue->front;
	int data = temp->data;

	queue->front = queue->front->next;

	// If front becomes NULL, set rear to NULL as well
	if (queue->front == NULL)
	{
		queue->rear = NULL;
	}

	free(temp);
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

	return queue->front->data;
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
	QueueNode *current = queue->front;
	while (current != NULL)
	{
		printf("%d ", current->data);
		current = current->next;
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
