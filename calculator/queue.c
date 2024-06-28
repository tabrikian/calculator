#include "queue.h"

queue* init_queue() {
	queue* q = (queue*)malloc(sizeof(queue));
	q->head = NULL;
	q->last = NULL;
	return q;
}


int queue_push(queue* q, token_t* item) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->data = item;
	if (q->head == NULL){
		q->last = node;
		q->head = q->last;
	} else {
		q->last->next = node;
		q->last = node;
	}
	q->last->next = NULL;
	return 1;
}


token_t* queue_top(queue* q) {
	return q->head->data;
}


token_t* queue_pop(queue* q){
	token_t* item = q->head->data;
	node_t* node = q->head;
	q->head = node->next;
	if (q->head == NULL)
		q->last = NULL;
	free(node);
	return item;
}


bool queue_is_empty(queue* q) {
	return q->head == NULL;
}


int queue_delete(queue* q) {
	while (!queue_is_empty(q)) {
		queue_pop(q);
	}
	free(q);
	return 1;
}


int print_queue(queue* q) {
	return print_tokens(q->head);
}


queue* parse_tokens(char** input) {
	bool in_function = false;
	queue* tokens = init_queue();
	while (input[0][0] != 0) {
		//ignore spaces
		while (input[0][0] == ' ' || (input[0][0] == ',' && in_function)) {
			*input = *input + 1;
		}
		if (input[0][0] == 0)
			break;
		token_t* new_token = (token_t*)malloc(sizeof(token_t));
		parse_token(input, new_token);
		if (new_token->is_function && input[0][0] == '(')
			in_function = true;
		if (input[0][0] == ')')
			in_function = false;
		queue_push(tokens, new_token);
	}
	return to_negative_numbers(tokens);
}


queue* to_negative_numbers(queue* exp) {
	queue* new_exp = init_queue();
	bool may_be_negative = true;
	bool to_negative = false;

	while (!queue_is_empty(exp)) {
		token_t* token = queue_pop(exp);
		if (token->is_operator && token->_operator == '-' && may_be_negative) {
			to_negative = !to_negative;
			delete_token(token);
		}
		else {
			if (to_negative)
				int_minus_inplace(token->num);
			may_be_negative = (token->is_function || token->is_operator || (token->is_char && token->_operator == '('));
			to_negative = false;
			queue_push(new_exp, token);
		}
	}
	queue_delete(exp);
	print_queue(new_exp);
	return new_exp;
}
