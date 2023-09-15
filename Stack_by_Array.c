#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
//*****************************************Stack (LIFO)*******************************
typedef struct
{
        int items[MAX_SIZE];
        int top;
} Stack;
//************************************************************************************
// mohamed gom3a
//****************************************function declariton*************************
void initialize(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack *stack);
void display(Stack *stack);
//************************************************************************************

// initialize th stack
void initialize(Stack *stack)
{
        stack->top = -1;
}
// function return true if the top equal -1 otherwise return 0
int isEmpty(Stack *stack)
{
        return stack->top == -1;
}
// function return true if the stck is full
int isFull(Stack *stack)
{
        return stack->top == MAX_SIZE - 1;
}
// insert item in the stack
void push(Stack *stack, int data)
{
        if (isFull(stack))
        {
                printf("Stack overflow\n");
                return;
        }

        stack->top++;
        stack->items[stack->top] = data;
}
// remove item from the stack
int pop(Stack *stack)
{
        if (isEmpty(stack))
        {
                printf("Stack underflow\n");
                return -1;
        }

        int data = stack->items[stack->top];
        stack->top--;
        return data;
}
// return the item at the top of stack
int peek(Stack *stack)
{
        if (isEmpty(stack))
        {
                printf("Stack is empty\n");
                return -1;
        }

        return stack->items[stack->top];
}
// print the item of stack
void display(Stack *stack)
{
        if (isEmpty(stack))
        {
                printf("Stack is empty\n");
                return;
        }

        printf("Stack elements: ");
        for (int i = stack->top; i >= 0; i--)
        {
                printf("%d ", stack->items[i]);
        }
        printf("\n");
}

int main()
{
        Stack stack;
        initialize(&stack);

        push(&stack, 10);
        push(&stack, 20);
        push(&stack, 30);

        display(&stack); // Output: Stack elements: 30 20 10

        printf("Top element: %d\n", peek(&stack)); // Output: Top element: 30

        pop(&stack);
        display(&stack); // Output: Stack elements: 20 10

        return 0;
}