#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//******************************************Stack by linked list*********************
typedef struct Node
{
	int data;
	struct Node *next;
} Node;

typedef struct
{
	Node *top;
} Stack;
// mohamed gom3a
//******************************************function declaration*********************
void initialize(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack *stack);
void display(Stack *stack);
int isBalanced(char *expression);
int isOperator(char ch);
int isOperand(char ch);
int getPrecedence(char ch);
void infixToPostfix(char *infix, char *postfix);
void infixToPrefix(char *infix, char *prefix);
void reverseString(char *str);
//***********************************************************************************

void initialize(Stack *stack)
{
	stack->top = NULL;
}

int isEmpty(Stack *stack)
{
	return stack->top == NULL;
}
// push item in the stack
void push(Stack *stack, int data)
{
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Memory allocation failed\n");
		return;
	}

	newNode->data = data;
	newNode->next = stack->top;
	stack->top = newNode;
}
// remove item from the stack
int pop(Stack *stack)
{
	if (isEmpty(stack))
	{
		printf("Stack underflow\n");
		return -1;
	}

	Node *temp = stack->top;
	int data = temp->data;
	stack->top = stack->top->next;
	free(temp);
	return data;
}
// return top of stack
int peek(Stack *stack)
{
	if (isEmpty(stack))
	{
		printf("Stack is empty\n");
		return -1;
	}

	return stack->top->data;
}
// print item
void display(Stack *stack)
{
	if (isEmpty(stack))
	{
		printf("Stack is empty\n");
		return;
	}

	printf("Stack elements: ");
	Node *current = stack->top;
	while (current != NULL)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}
// check if the Parentheses is Balanced or not
int isBalanced(char *expression)
{
	Stack stack;
	initialize(&stack);

	for (int i = 0; expression[i] != '\0'; i++)
	{
		char ch = expression[i];
		// push لو لقينا فتحة قوس هنعمل ليها
		if (ch == '(' || ch == '[' || ch == '{')
		{
			push(&stack, ch);
		}
		// topلو لقينا قفلة قوس هنبدأ بقا نقارنها مع ال
		else if (ch == ')' || ch == ']' || ch == '}')
		{
			// not Balanced أصلا فاضي فكدا هتكون stack لو ال
			if (isEmpty(&stack))
			{
				return 0;
			}
			char top = peek(&stack);
			if ((ch == ')' && top == '(') ||
			(ch == ']' && top == '[') ||
			(ch == '}' && top == '{'))
			{
				pop(&stack);
			}
			// لو فتحة القوس مش بتساوي قفلةالقوس إطلع
			else
			{
				return 0;
			}
		}
	}
	// balancedفاضي يبقا كدا stack لو ال
	return isEmpty(&stack);
}
// return true if the char is operand
int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
// return true if char is operator
int isOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
int getPrecedence(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}
// convert infix to postfix
void infixToPostfix(char *infix, char *postfix)
{
	Stack stack;
	initialize(&stack);

	int infixLength = strlen(infix);
	int postfixIndex = 0;

	for (int i = 0; i < infixLength; i++)
	{
		char ch = infix[i];

		if (isOperand(ch))
		{
			postfix[postfixIndex++] = ch;
		}
		else if (ch == '(')
		{
			push(&stack, ch);
		}
		else if (ch == ')')
		{
			// ( مش بيساوي ال top مش فضي وكمان ال stack طالما ال
			while (!isEmpty(&stack) && peek(&stack) != '(')
			{
				// postfixوضيف في pop إفضل إعمل
				postfix[postfixIndex++] = pop(&stack);
			}
			// (في حالة لو لقينا ال
			if (!isEmpty(&stack) && peek(&stack) == '(')
			{
				// stackإمسحه من ال
				pop(&stack);
			}
		}
		// +, *, /, -, ^
		else if (isOperator(ch))
		{
			// إلي انا مباصيهOperatorأقل من ال Operatorفاضي أو تجيب stack إعمل لوب لغاية ماتخلي ال
			while (!isEmpty(&stack) && getPrecedence(ch) <= getPrecedence(peek(&stack)))
			{
				postfix[postfixIndex++] = pop(&stack);
			}
			push(&stack, ch); // الجديد إلي مباصيهOperatorضيف بقا ال
		}
	}
	// طلعها stack باقيه في ال  Operatorsلو فيه
	while (!isEmpty(&stack))
	{
		postfix[postfixIndex++] = pop(&stack);
	}

	postfix[postfixIndex] = '\0';
}
// convert infix to prefix
void infixToPrefix(char *infix, char *prefix)
{
	Stack stack;
	initialize(&stack);

	int infixLength = strlen(infix);
	int prefixIndex = 0;
	// infixهنمشي بالعكس علي ال
	for (int i = infixLength - 1; i >= 0; i--)
	{
		char ch = infix[i];
		// a,b,c...
		if (isOperand(ch))
		{
			prefix[prefixIndex++] = ch;
		}
		// postfix هنبدأ نحول ل
		// والعكسclosing parenthesis هتكون opening parenthesis هنعكس الأقواس بدل ماكانت
		else if (ch == ')')
		{
			push(&stack, ch);
		}
		// opening parenthesis في حالة لو لقينا
		else if (ch == '(')
		{
			// operatorيكون فاضي وكل شوية هنضيف ال stack او ال closing parenthesis هنفضل ماشين لغاية لما نوصل ل
			while (!isEmpty(&stack) && peek(&stack) != ')')
			{
				prefix[prefixIndex++] = pop(&stack);
			}
			if (!isEmpty(&stack) && peek(&stack) == ')')
			{
				pop(&stack);
			}
		}
		else if (isOperator(ch))
		{
			// getPrecedence(ch) <= getPrecedence(peek(&stack)) الاول كانت كدا
			while (!isEmpty(&stack) && getPrecedence(ch) < getPrecedence(peek(&stack)))
			{
				// ) فوق ال operator إطلع وضيف ال closing parenthesis لو لقينا
				if (peek(&stack) == ')')
				{
					break;
				}
				prefix[prefixIndex++] = pop(&stack);
			}
			// if the stack contain + and i need to add + so the stack apper ++
			// ) وكمان لو عاوزين نضيف فوق ال
			push(&stack, ch);
		}
	}

	while (!isEmpty(&stack))
	{
		char top = pop(&stack);
		if (top != ')')
		{
			prefix[prefixIndex++] = top;
		}
	}

	prefix[prefixIndex] = '\0';
	// ده  postfix  إعكس بقا ال
	reverseString(prefix);
}
void reverseString(char *str)
{
	Stack stack;
	initialize(&stack);

	int length = strlen(str);

	// Push characters onto the stack
	for (int i = 0; i < length; i++)
	{
		push(&stack, str[i]);
	}

	// Pop characters from the stack to reverse the string
	for (int i = 0; i < length; i++)
	{
		str[i] = pop(&stack);
	}
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

	char expression1[] = "((a + b) * (c - d))";
	char expression2[] = "(a + b) * (c - d))";

	if (isBalanced(expression1))
	{
		printf("Expression 1 is balanced\n");
	}
	else
	{
		printf("Expression 1 is not balanced\n");
	}

	if (isBalanced(expression2))
	{
		printf("Expression 2 is balanced\n");
	}
	else
	{
		printf("Expression 2 is not balanced\n");
	}

	char infixExpression[] = "a + (b * c) - d";
	char postfixExpression[100];
	char prefixExpression[100];

	infixToPostfix(infixExpression, postfixExpression);
	infixToPrefix(infixExpression, prefixExpression);

	printf("Infix Expression: %s\n", infixExpression);
	printf("Postfix Expression: %s\n", postfixExpression);
	printf("Prefix Expression: %s\n", prefixExpression);

	char str[] = "Hello, World!";
	printf("Original String: %s\n", str);

	reverseString(str);
	printf("Reversed String: %s\n", str);

	return 0;
}