#include <string.h>
#include <math.h>
#include "queue.h"

#define MAX_LENGTH 1000

int execute_operator(stack* s, char _operator);

int execute_function(stack* s, char* function);

int op_rate(token_t* op);

my_int* evaluate_rpn(queue* expression);

bool is_less_precedence(token_t* op1, token_t* op2);

queue* shunting_yard(queue* tokens);


int execute_operator(stack* s, char _operator) {
	my_int* num2 = delete_token(stack_pop(s));
	my_int* num1 = delete_token(stack_pop(s));


	my_int* res = NULL;
	switch (_operator) {
	case '+':
		res = int_add(num1, num2);
		break;
	case '-':
		res = int_sub(num1, num2);
		break;
	case '*':
		res = int_mul(num1, num2);
		break;
	case '/':
		res = int_div(num1, num2);
		break;
	case '^':
		res = int_pow(num1, num2);
		break;
	default:
		break;
	}
	
	delete_int(num1);
	delete_int(num2);
	stack_push(s, create_by_int(res));
	return 1;
}


int execute_function(stack* s, char* function) {
	my_int* res = NULL;
	if (strcmp(function, "MIN") == 0) {
		my_int* num1 = delete_token(stack_pop(s));
		my_int* num2 = delete_token(stack_pop(s));
		res = int_min(num1, num2);
		delete_int(num1);
		delete_int(num2);
	}
	else {
		if (strcmp(function, "MAX") == 0) {
			my_int* num1 = delete_token(stack_pop(s));
			my_int* num2 = delete_token(stack_pop(s));
			res = int_max(num1, num2);
			delete_int(num1);
			delete_int(num2);
		}
		else {
			if (strcmp(function, "ABS") == 0) {
				my_int* num = delete_token(stack_pop(s));
				res = int_abs(num);
				delete_int(num);
			}
			else {
				if (strcmp(function, "MOSHE") == 0)
					res = init_int(1337);
			}
		}
	}

	stack_push(s, create_by_int(res));
	return 1;
}


my_int* evaluate_rpn(queue* expression) {
	stack* s = init_stack();
	while (!queue_is_empty(expression)) {
		while (!queue_is_empty(expression) && queue_top(expression)->is_num) {
			stack_push(s, queue_pop(expression));
		}
		while (!queue_is_empty(expression) && !(queue_top(expression)->is_num)) {
			if (queue_top(expression)->is_char)
				execute_operator(s, queue_top(expression)->_operator);
			if (queue_top(expression)->is_function)
				execute_function(s, queue_top(expression)->function);


			free(queue_pop(expression));
		}
	}
	token_t* res = stack_pop(s);
	stack_delete(s);
	return delete_token(res);
}


int op_rate(token_t* op) {
	int rate;
	switch (op->_operator) {
	case '+':
		rate = 2;
		break;
	case '-':
		rate = 2;
		break;
	case '*':
		rate = 3;
		break;
	case '/':
		rate = 3;
		break;
	case '^':
		rate = 4;
		break;
	default: //function
		rate = 5;
		break;
	}
	return rate;
}


bool is_less_precedence(token_t* op1, token_t* op2) {
	return op_rate(op1) >= op_rate(op2);
}


queue* shunting_yard(queue* tokens) {
	queue* output = init_queue();
	stack* operators_stack = init_stack();
	while (!queue_is_empty(tokens)) {
		token_t* token = queue_pop(tokens);
		if (token->is_num)
			queue_push(output, token);
		else {
			if (token->is_function)
				stack_push(operators_stack, token);
			else {
				if (token->is_operator) {
					while (!stack_is_empty(operators_stack) &&
						!(stack_top(operators_stack)->_operator == '(') &&
						is_less_precedence(stack_top(operators_stack), token))
						queue_push(output, stack_pop(operators_stack));
					stack_push(operators_stack, token);
				}
				else {
					if (token->_operator == '(')
						stack_push(operators_stack, token);
					else {
						while (!stack_is_empty(operators_stack) &&
							!(stack_top(operators_stack)->_operator == '('))
							queue_push(output, stack_pop(operators_stack));
						delete_token(stack_pop(operators_stack));
						delete_token(token);
					}
				}
			}
		}
	}
	while (!stack_is_empty(operators_stack))
		queue_push(output, stack_pop(operators_stack));

	queue_delete(tokens);
	return output;
}


char* read_input() {
	char* inp = (char*)malloc(sizeof(char) * MAX_LENGTH);
	for (int i = 0; i < MAX_LENGTH; i++) {
		inp[i] = getchar();
		if (inp[i] == '\n' || inp[i] == 0) {
			inp[i] = 0;
			break;
		}
	}
	inp[MAX_LENGTH - 1] = 0;
	return inp;
}


int calculator() {
	char* input = read_input();	
	print_int(evaluate_rpn(shunting_yard(parse_tokens(&input))));
	printf("\n\n");
}


int main(){
	while (true){
		calculator();
	}
}
