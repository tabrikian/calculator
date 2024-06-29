#include "token.h"

typedef struct node_ {
	token_t* data;
	struct node_* next;
} node_t;

typedef struct stack_t {
	node_t* head;
} stack_t;


stack_t* init_stack_t();

int stack_t_push(stack_t* s, token_t* item);

token_t* stack_t_pop(stack_t* s);

token_t* stack_t_top(stack_t* s);

bool stack_t_is_empty(stack_t* s);

int stack_t_delete(stack_t* s);

int print_tokens(node_t* tokens);

int print_stack_t(stack_t* s);
