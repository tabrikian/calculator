#include "token.h"

typedef struct node_ {
	token_t* data;
	struct node_* next;
} node_t;

typedef struct stack {
	node_t* head;
} stack;


stack* init_stack();

int stack_push(stack* s, token_t* item);

token_t* stack_pop(stack* s);

token_t* stack_top(stack* s);

bool stack_is_empty(stack* s);

int stack_delete(stack* s);

int print_tokens(node_t* tokens);

int print_stack(stack* s);
