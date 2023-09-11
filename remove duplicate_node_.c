#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node
{
        int data;
        struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;
        return newNode;
}

// Function to insert a node at the end of a linked list
void insertNode(struct Node **head, int data)
{
        struct Node *newNode = createNode(data);
        if (*head == NULL)
        {
                *head = newNode;
        }
        else
        {
                struct Node *temp = *head;
                while (temp->next != NULL)
                {
                        temp = temp->next;
                }
                temp->next = newNode;
        }
}

// Function to remove duplicate elements from an unsorted linked list
void removeDuplicates(struct Node *head)
{
        if (head == NULL || head->next == NULL)
        {
                return;
        }

        struct Node *current = head;
        struct Node *runner;

        while (current != NULL)
        {
                runner = current;
                while (runner->next != NULL)
                {
                        if (current->data == runner->next->data)
                        {
                                struct Node *duplicate = runner->next;
                                runner->next = runner->next->next; // روح علي النود إلي بعد النود إلي عاوز أحذفها
                                free(duplicate);
                        }
                        else
                        {
                                runner = runner->next;
                        }
                }
                current = current->next;
        }
}

// Function to print the linked list
void printList(struct Node *head)
{
        struct Node *temp = head;
        while (temp != NULL)
        {
                printf("%d ", temp->data);
                temp = temp->next;
        }
        printf("\n");
}

// Test the function
int main()
{
        struct Node *head = NULL;

        // Insert nodes into the linked list
        insertNode(&head, 10);
        insertNode(&head, 20);
        insertNode(&head, 20);
        insertNode(&head, 30);
        insertNode(&head, 30);
        insertNode(&head, 40);
        insertNode(&head, 50);

        printf("Original Linked List: ");
        printList(head);

        // Remove duplicates
        removeDuplicates(head);

        printf("Linked List after removing duplicates: ");
        printList(head);

        return 0;
}