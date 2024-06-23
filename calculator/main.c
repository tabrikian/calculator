#include <stdio.h>
#include <string.h>
#include <math.h>
#include "queue.h"

#define MAX_LENGTH 100

bool set_token_as_char(char** input, token_t* token);
bool set_token_as_function(char** input, token_t* token);
bool set_token_as_number(char** input, token_t* token);
bool parse_token(char** input, token_t* token);
queue* to_negative_numbers(queue* exp);
queue* parse_tokens(char** input);
int execute_operator(stack* s, char _operator);
int execute_function(stack* s, char* function);
int evaluate_rpn(queue* expression);
int print_token(token_t* token);
int print_tokens(node_t* tokens);
int print_stack(stack* s);
queue* shunting_yard(queue* tokens);

bool set_token_as_char(char** input, token_t* token) {
	token->is_char = true;
	token->is_num = false;
	token->is_function = false;
	token->_operator = *input[0];
	token->is_operator = (token->_operator != '(' && token->_operator != ')');
	*input = *input+1;
	return true;
}

bool set_token_as_function(char** input, token_t* token) {
	token->is_function = true;
	token->is_num = false;
	token->is_char = false;
	token->is_operator = false;

	int index = 0;
	while ((input[0][index] >= 'A' && input[0][index] <= 'Z') || input[0][index] == '_') {
		index++;
	}
	token->function = (char*) malloc(sizeof(char) * (index+1));
	(token->function)[index] = 0;
	for (int i = 0; i < index; i++) {
		(token->function)[i] = *(*input + i);
	}
	*input = *input + index;
	return true;
}

bool set_token_as_number(char** input, token_t* token) {
	token->is_num = true;
	token->is_function = false;
	token->is_char = false;
	token->is_operator = false;

	bool is_negative = false;
	if (!(input[0][0] >= '0' && input[0][0] <= '9')) {
		is_negative = true;
		*input = *input + 1;
	}
	token->num = 0;
	while (input[0][0] >= '0' && input[0][0] <= '9') {
		token->num *= 10;
		token->num += input[0][0]-'0';
		*input = *input + 1;
	}
	if (is_negative) {
		token->num = -token->num;
	}
	return true;
}

bool parse_token(char** input, token_t* token){
	if (input[0][0] == '(' || input[0][0] == '+' || input[0][0] == '-' || input[0][0] == '*' 
		|| input[0][0] == '/' || input[0][0] == '^' || input[0][0] == ')') {
		return set_token_as_char(input, token);
	}
	if ((input[0][0] >= 'A' && input[0][0] <= 'Z') || input[0][0] == '_') {
		return set_token_as_function(input, token);
	}
	if (input[0][0] >= '0' && input[0][0] <= '9') {
		return set_token_as_number(input, token);
	}
	return false;
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
		}else {
			if (to_negative)
				token->num = -token->num;
			may_be_negative = (token->is_operator || (token->is_char && token->_operator == '('));
			to_negative = false;
			queue_push(new_exp, token);
		}
	}
	queue_delete(exp);
	return new_exp;
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

int execute_operator(stack* s, char _operator) {
	int num2 = delete_token(stack_pop(s));
	int num1 = delete_token(stack_pop(s));

	int res;
	switch (_operator){
	case '+':
		res = num1 + num2;
		break;
	case '-':
		res = num1 - num2;
		break;
	case '*':
		res = num1 * num2;
		break;
	case '/':
		res = num1 / num2;
		break;
	case '^':
		res = (int) pow((double) num1, (double) num2); 
		break;
	default:
		break;
	}

	stack_push(s, create_by_num(res));
	return 1;
}

int execute_function(stack* s, char* function) {
	int res;
	if (strcmp(function, "MIN") == 0) {
		int num1 = delete_token(stack_pop(s));
		int num2 = delete_token(stack_pop(s));
		res = num1;
		if (num1 > num2)
			res = num2;
	}else {
		if (strcmp(function, "MAX") == 0) {
			int num1 = delete_token(stack_pop(s));
			int num2 = delete_token(stack_pop(s));
			res = num1;
			if (num1 < num2)
				res = num2;
		}else {
			if (strcmp(function, "ABS") == 0) {
				int num1 = delete_token(stack_pop(s));
				res = num1;
				if (num1 < 0)
					res = -num1;
			}else {
				if (strcmp(function, "MOSHE") == 0)
					res = 1337;
			}
		}
	}

	stack_push(s, create_by_num(res));
	return 1;
}

int evaluate_rpn(queue* expression){
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
		rate = 1;
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
	while (!queue_is_empty(tokens)){
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
						!is_less_precedence(token, stack_top(operators_stack)))
						queue_push(output, stack_pop(operators_stack));
					stack_push(operators_stack, token);
				}
				else {
					if(token->_operator == '(')
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

//testing
int print_token(token_t* token) {
	if (token->is_char)
		printf("%c ", token->_operator);
	if (token->is_num)
		printf("%d ", token->num);
	if (token->is_function)
		printf("%s ", token->function);
	return 1;
}

int main(){
	char input[MAX_LENGTH];
	scanf_s("%s", input, MAX_LENGTH);

	char* inp = (char*)malloc(sizeof(char)*MAX_LENGTH);
	for (int i = 0; i < MAX_LENGTH; i++)
		inp[i] = input[i];

	printf("%d", evaluate_rpn(shunting_yard(parse_tokens(&inp))));
}