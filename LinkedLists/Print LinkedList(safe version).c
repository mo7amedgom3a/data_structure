#include <stdio.h>
#include <stdlib.h>
typedef struct listint_s
{
        int n;
        struct listint_s *next;
} listint_t;

size_t looped_listint_len(const listint_t *head);
size_t print_listint_safe(const listint_t *head);

/**
 * looped_listint_len - Counts the number of unique nodes
 *                      in a looped listint_t linked list.
 * @head: A pointer to the head of the listint_t to check.
 *
 * Return: If the list is not looped - 0.
 *         Otherwise - the number of unique nodes in the list.
 */
size_t looped_listint_len(const listint_t *head)
{
        const listint_t *tortoise, *hare;
        size_t count = 1;

        if (head == NULL || head->next == NULL)
                return (0);

        tortoise = head->next;
        hare = (head->next)->next;

        while (hare)
        {
                if (tortoise == hare)
                {
                        tortoise = head;
                        while (tortoise != hare)
                        {
                                count++;
                                tortoise = tortoise->next;
                                hare = hare->next;
                        }

                        tortoise = tortoise->next;
                        while (tortoise != hare)
                        {
                                count++;
                                tortoise = tortoise->next;
                        }

                        return (count);
                }

                tortoise = tortoise->next;
                hare = (hare->next)->next;
        }

        return (0);
}

/**
 * print_listint_safe - Prints a listint_t list safely.
 * @head: A pointer to the head of the listint_t list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_listint_safe(const listint_t *head)
{
        size_t count, index = 0;

        count = looped_listint_len(head);

        if (count == 0)
        {
                for (; head != NULL; count++)
                {
                        printf("[%p] %d\n", (void *)head, head->n);
                        head = head->next;
                }
        }

        else
        {
                for (index = 0; index < count; index++)
                {
                        printf("[%p] %d\n", (void *)head, head->n);
                        head = head->next;
                }

                printf("-> [%p] %d\n", (void *)head, head->n);
        }

        return (count);
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
        head = NULL;
        node = add_nodeint(&head, 0);
        add_nodeint(&head, 1);
        add_nodeint(&head, 2);
        add_nodeint(&head, 3);
        add_nodeint(&head, 4);
        node->next = add_nodeint(&head, 98);
        add_nodeint(&head, 402);
        add_nodeint(&head, 1024);
        print_listint_safe(head);
        return (0);
}