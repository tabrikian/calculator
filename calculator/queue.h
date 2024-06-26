#include "stack.h"

typedef struct queue {
	node_t* head;
	node_t* last;
} queue;


queue* init_queue();

int queue_push(queue* q, token_t* item);

token_t* queue_top(queue* q);

token_t* queue_pop(queue* q);

bool queue_is_empty(queue* q);

int queue_delete(queue* q);

int print_queue(queue* q);

queue* parse_tokens(char** input);

queue* to_negative_numbers(queue* exp);
