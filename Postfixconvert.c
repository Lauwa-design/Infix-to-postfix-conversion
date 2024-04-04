#include <stdio.h>
#include <stdlib.h> // declares DMA function malloc
#include <string.h>
#include <ctype.h>

struct Node // using a linked list
{
    char data;
    struct Node* next;
};

struct Stack
{
    struct Node* top;
};

// initialize a new node
struct Node* new_node(char c)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node -> data = c;
    node -> next = NULL;

    return node;
}

struct Stack* create_stack()
{
    struct Stack* stack = (struct Stack*)malloc((sizeof(struct Stack)));

    stack -> top = NULL;

    return stack;
}

int isEmpty(struct Stack* stack)
{
    return stack -> top == NULL;
}

void push(struct Stack* stack, char c)
{
    struct Node* node = new_node(c);

    node -> next = stack -> top;
    stack -> top = node;
}

char pop(struct Stack* stack)
{

    if(isEmpty(stack))
    {
        printf("Stack is empty\n");

        return '\0';
    }
    char data = stack -> top -> data;
    struct Node* temp = stack -> top;

    stack -> top = stack -> top -> next;
    free(temp);

    return data;
}

char peek(struct Stack* stack)
{
    if(isEmpty(stack))
    {
        printf("Stack is empty\n");
        return '\0';

    }
    return stack -> top -> data;
}

int is_operator(char operator_)
{
    return operator_ == '+' || operator_ == '-' || operator_ == '*' || operator_ == '/' || operator_ == '%';

}

int get_precedence(char operator_)
{
    switch (operator_) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return -1; // Invalid operator
    }
}

void infix_to_postfix(char* infix, char* postfix)
{
    struct Stack* stack = create_stack();

    int i, j;

    for(i = 0, j = -1; infix[i]; ++i){
        if(isalnum(infix[i])){
            postfix[++j] = infix[i];
        }else if(infix[i] == '('){
            push(stack, infix[i]);
        }
        else if(infix[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
            {
                postfix[++j] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) == '(')
            {
                pop(stack);
            }
            else
            {
                printf("Invalid Expression\n");
                return;
            }
        }
        else if(is_operator(infix[i]))
        {
            while(!isEmpty(stack) && get_precedence(infix[i]) <= get_precedence(stack))
            {
                postfix[++j] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }
    while(!isEmpty(stack))
    {
        if(peek(stack) == '(')
        {
            printf("Invalid Expression\n");
            return;
        }
        postfix[++j] = pop(stack);
    }
    postfix[++j] = '\0';
}

int main()
{
    char infix[100];
    char postfix[100];

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0';

    infix_to_postfix(infix, postfix);
    if(strcmp(postfix, "") != 0){
        printf("Postfix expression: %s\n", postfix);
    }
    return 0;
}
