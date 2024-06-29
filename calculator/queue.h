#include "stack.h"

typedef struct queue_t {
	node_t* head;
	node_t* last;
} queue_t;


queue_t* init_queue_t();

int queue_t_push(queue_t* q, token_t* item);

token_t* queue_t_top(queue_t* q);

token_t* queue_t_pop(queue_t* q);

bool queue_t_is_empty(queue_t* q);

int queue_t_delete(queue_t* q);

int print_queue_t(queue_t* q);

queue_t* parse_tokens(char** input); // parse a string to queue of tokens

queue_t* to_negative_numbers(queue_t* exp); // parse a queue of tokens to new queue with negative numbers
