#include "stack.h"

int print_tokens(node_t* tokens) {
	while (tokens != NULL) {
		print_token(tokens->data);
		tokens = tokens->next;
	}
	printf("\n");
	return 1;
}

stack* init_stack() {
	stack* s = (stack*)malloc(sizeof(stack));
	s->head = NULL;
	return s;
}
int stack_push(stack* s, token_t* item) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->data = item;
	node->next = s->head;
	s->head = node;
	return 1;
}
token_t* stack_top(stack* s) {
	token_t* item = s->head->data;
	return item;
}
token_t* stack_pop(stack* s) {
	token_t* item = s->head->data;
	node_t* node = s->head;
	s->head = node->next;
	free(node);
	return item;
}
bool stack_is_empty(stack* s) {
	return s->head == NULL;
}
int stack_delete(stack* s) {
	while (!stack_is_empty(s)){
		stack_pop(s);
	}
	free(s);
	return 1;
}
int print_stack(stack* s) {
	return print_tokens(s->head);
}