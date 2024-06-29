#include "queue.h"

queue_t* init_queue_t() {
	queue_t* q = (queue_t*)malloc(sizeof(queue_t));
	q->head = NULL;
	q->last = NULL;
	return q;
}


int queue_t_push(queue_t* q, token_t* item) {
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


token_t* queue_t_top(queue_t* q) {
	return q->head->data;
}


token_t* queue_t_pop(queue_t* q){
	token_t* item = q->head->data;
	node_t* node = q->head;
	q->head = node->next;
	if (q->head == NULL)
		q->last = NULL;
	free(node);
	token_t* item_copy = copy_token(item);
	my_int_t* num = delete_token(item);
	if (num != NULL) {
		delete_int(num);
	}
	return item_copy;
}


bool queue_t_is_empty(queue_t* q) {
	return q->head == NULL;
}


int queue_t_delete(queue_t* q) {
	while (!queue_t_is_empty(q)) {
		my_int_t* num = delete_token(queue_t_pop(q));
		if (num != NULL) {
			delete_int(num);
		}
	}
	free(q);
	return 1;
}


int print_queue_t(queue_t* q) {
	return print_tokens(q->head);
}


queue_t* parse_tokens(char** input) {
	bool in_function = false;
	queue_t* tokens = init_queue_t();
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
		queue_t_push(tokens, new_token);
	}
	return to_negative_numbers(tokens);
}


queue_t* to_negative_numbers(queue_t* exp) {
	queue_t* new_exp = init_queue_t();
	bool may_be_negative = true;
	bool to_negative = false;

	while (!queue_t_is_empty(exp)) {
		token_t* token = queue_t_pop(exp);
		if (token->is_operator && token->parenthesis_or_operator == '-' && may_be_negative) {
			to_negative = !to_negative;
			delete_token(token);
		}
		else {
			if (to_negative)
				int_minus_inplace(token->num);
			may_be_negative = (token->is_function || token->is_operator || (token->is_char && token->parenthesis_or_operator == '('));
			to_negative = false;
			queue_t_push(new_exp, token);
		}
	}
	queue_t_delete(exp);
	return new_exp;
}
