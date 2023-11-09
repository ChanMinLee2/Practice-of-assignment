
#include <stdio.h>

typedef struct stack stack;
struct stack{
    stack* top;
};

typedef struct node node;
struct node{
    int value;
    node* next;
};

void push_stack(int x, stack* stack)
{
    node* newnode = (node*)malloc(node);
    newnode->value = x;
    newnode->next = stack->top;
    stack->top = newnode;
}

int pop_stack(stack* stack)
{
    if(stack->top == NULL)
    {
        return -1;
    }
    else
    {
        stack* temp = stack->top;
        free(stack->top);
        stack->top = temp->next;
    
        return temp->value;
    }
    
}

int stack_empty_check(stack* stack);

int stack_top_extract(stack* stack);

int stack_traversal(stack* stack);

int main()
{
    stack* mystack = (stack*)malloc(stack);
    stack->top = NULL;
    int command_count = 0;
    int command = 0;
    int push_num = 0;
    scanf("%d", &command_count);
    
    for (int i = 0; i < command_count; i++) {
        scanf("%d", &command);
        if(command == 1)
        {
            scanf("%d", &push_num);
            push_stack(push_num, mystack);
        }
        else
        {
            if(command == 2)
            {
                printf("%d", pop_stack(mystack));
            }
            
            else if(command == 3)
            {
                printf("%d", stack_traversal(mystack));
            }
            
            else if(command == 4)
            {
                printf("%d", stack_empty_check(mystack));
            }
            
            else if( command == 5)
            {
                printf("%d", stack_top_extract(mystack));
            }
        }
    }
    
    node* newnode = (node*)malloc(node);
    
}
