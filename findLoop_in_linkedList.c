#include <stdlib.h>
#include <stdio.h>

typedef struct listint_s
{
        int n;
        struct listint_s *next;
} listint_t;

listint_t *find_listint_loop(listint_t *head)
{
        listint_t *slow = head, *fast = head;

        // Traverse the linked list and detect if there is a loop
        while (slow != NULL && fast != NULL && fast->next != NULL)
        {
                slow = slow->next;       // Move slow pointer one step
                fast = fast->next->next; // Move fast pointer two steps

                // If slow and fast pointers meet then there is a loop
                if (slow == fast)
                {
                        // Start from the head of linked list and move slow pointer one by one
                        slow = head;

                        // Look for the node where the loop starts
                        while (slow != fast)
                        {
                                slow = slow->next;
                                fast = fast->next;
                        }
                        return slow; // Return the address of the node where the loop starts
                }
        }
        return NULL; // Return NULL if there is no loop
}
int main(void)
{
    listint_t *head;
    listint_t *head2;
    listint_t *node;

    head2 = NULL;
    add_nodeint(&head2, 0);
    add_nodeint(&head2, 1);
    add_nodeint(&head2, 2);
    add_nodeint(&head2, 3);
    add_nodeint(&head2, 4);
    add_nodeint(&head2, 98);
    add_nodeint(&head2, 402);
    add_nodeint(&head2, 1024);
    print_listint_safe(head2);
    node = find_listint_loop(head2);
    if (node != NULL)
    {
        printf("Loop starts at [%p] %d\n", (void *)node, node->n);
    }
    free_listint_safe(&head2);
    head = NULL;
    node = add_nodeint(&head, 0);
    add_nodeint(&head, 1);
    add_nodeint(&head, 2);
    add_nodeint(&head, 3);
    add_nodeint(&head, 4);
    add_nodeint(&head, 5);
    add_nodeint(&head, 6);
    node->next = add_nodeint(&head, 7);
    add_nodeint(&head, 98);
    add_nodeint(&head, 402);
    add_nodeint(&head, 1024);
    print_listint_safe(head);
    node = find_listint_loop(head);
    if (node != NULL)
    {
        printf("Loop starts at [%p] %d\n", (void *)node, node->n);
    }
    free_listint_safe(&head);
    return (0);
}