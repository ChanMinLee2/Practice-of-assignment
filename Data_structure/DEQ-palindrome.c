#include <stdio.h>

typedef struct DEQ DEQ;
struct DEQ
{
    int size;
    char *array;
    int front;
    int rear; 
};

DEQ my_DEQ;

void create_DEQ( int input_size )
{
    my_DEQ.size = input_size;
    my_DEQ.array = (char)calloc( size, sizeof(char) );
    my_DEQ.front = my_DEQ.rear = -1;
}

int is_empty(DEQ my_deq)
{
    return (my_deq.front == my_deq.rear); 
}

int is_full(DEQ my_deq)
{
    return (my_deq.rear == my_deq.size - 1);
}

int palindrome( char * s )
{
    DEQ

}

int main(void)
{
    int check = 0;



}