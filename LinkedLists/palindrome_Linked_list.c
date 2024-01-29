
#include <stdio.h>
#include <stdlib.h>
/**
 * struct listint_s - singly linked list
 * @n: integer
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for project
 */
typedef struct listint_s
{
        int n;
        struct listint_s *next;
} listint_t;
size_t print_listint(const listint_t *h)
{
        const listint_t *current;
        unsigned int n; /* number of nodes */

        current = h;
        n = 0;
        while (current != NULL)
        {
                printf("%i\n", current->n);
                current = current->next;
                n++;
        }

        return (n);
}

/**
 * add_nodeint_end - adds a new node at the end of a listint_t list
 * @head: pointer to pointer of first node of listint_t list
 * @n: integer to be included in new node
 * Return: address of the new element or NULL if it fails
 */
listint_t *add_nodeint_end(listint_t **head, const int n)
{
        listint_t *new;
        listint_t *current;

        current = *head;

        new = malloc(sizeof(listint_t));
        if (new == NULL)
                return (NULL);

        new->n = n;
        new->next = NULL;

        if (*head == NULL)
                *head = new;
        else
        {
                while (current->next != NULL)
                        current = current->next;
                current->next = new;
        }

        return (new);
}

/**
 * free_listint - frees a listint_t list
 * @head: pointer to list to be freed
 * Return: void
 */
void free_listint(listint_t *head)
{
        listint_t *current;

        while (head != NULL)
        {
                current = head;
                head = head->next;
                free(current);
        }
}
/**
 * reverseList - reverse the linked list
 * @head: head of the list
 * Return: reverse the second half of the linked list.
 */

listint_t *reverseList(listint_t *head)
{
        listint_t *prev = NULL;
        listint_t *current = head;
        listint_t *next;

        while (current != NULL)
        {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
        }

        return (prev);
}

/**
 * is_palindrome - check is a linked list is palindrome
 * @head: head of the list
 * Return: 0 if not 1 if it is
 */

int is_palindrome(listint_t **head)
{
        if (*head == NULL || (*head)->next == NULL)
        {
                return (1);
        }

        listint_t *slow = *head;
        listint_t *fast = *head;

        while (fast->next != NULL && fast->next->next != NULL)
        {
                slow = slow->next;
                fast = fast->next->next;
        }

        listint_t *secondHalf = reverseList(slow->next);
        listint_t *firstHalf = *head;

        while (secondHalf != NULL)
        {
                if (firstHalf->n != secondHalf->n)
                {
                        return (0);
                }
                firstHalf = firstHalf->next;
                secondHalf = secondHalf->next;
        }

        return (1);
}
/**
 * main - check the code for
 *
 * Return: Always 0.
 */
int main(void)
{
        listint_t *head;

        head = NULL;
        add_nodeint_end(&head, 1);
        add_nodeint_end(&head, 17);
        add_nodeint_end(&head, 972);
        add_nodeint_end(&head, 50);
        add_nodeint_end(&head, 98);
        add_nodeint_end(&head, 98);
        add_nodeint_end(&head, 50);
        add_nodeint_end(&head, 972);
        add_nodeint_end(&head, 17);
        add_nodeint_end(&head, 1);
        print_listint(head);

        if (is_palindrome(&head) == 1)
                printf("Linked list is a palindrome\n");
        else
                printf("Linked list is not a palindrome\n");

        free_listint(head);

        return (0);
}