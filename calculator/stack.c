#include "stack.h"

int print_tokens(node_t* tokens) {
	while (tokens != NULL) {
		print_token(tokens->data);
		tokens = tokens->next;
	}
	printf("\n");
	return 1;
}


stack_t* init_stack_t() {
	stack_t* s = (stack_t*)malloc(sizeof(stack_t));
	s->head = NULL;
	return s;
}


int stack_t_push(stack_t* s, token_t* item) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->data = item;
	node->next = s->head;
	s->head = node;
	return 1;
}


token_t* stack_t_top(stack_t* s) {
	token_t* item = s->head->data;
	return item;
}


token_t* stack_t_pop(stack_t* s) {
	token_t* item = s->head->data;
	node_t* node = s->head;
	s->head = node->next;
	free(node);
	token_t* item_copy = copy_token(item);
	my_int_t* num = delete_token(item);
	if (num != NULL) {
		delete_int(num);
	}
	return item_copy;
}


bool stack_t_is_empty(stack_t* s) {
	return s->head == NULL;
}


int stack_t_delete(stack_t* s) {
	while (!stack_t_is_empty(s)){
		my_int_t* num = delete_token(stack_t_pop(s));
		if (num != NULL) {
			delete_int(num);
		}
	}
	free(s);
	return 1;
}


int print_stack_t(stack_t* s) {
	return print_tokens(s->head);
}
