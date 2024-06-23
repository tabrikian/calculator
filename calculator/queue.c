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
