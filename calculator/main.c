#include "main.h"


int execute_operator(stack_t* s, char _operator) {
	my_int_t* num2 = delete_token(stack_t_pop(s));
	my_int_t* num1 = delete_token(stack_t_pop(s));


	my_int_t* res = NULL;
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
	stack_t_push(s, create_by_int(res));
	return 1;
}


int execute_function(stack_t* s, char* function) {
	my_int_t* res = NULL;
	if (strcmp(function, "MIN") == 0) {
		my_int_t* num1 = delete_token(stack_t_pop(s));
		my_int_t* num2 = delete_token(stack_t_pop(s));
		res = int_min(num1, num2);
		delete_int(num1);
		delete_int(num2);
	}
	else {
		if (strcmp(function, "MAX") == 0) {
			my_int_t* num1 = delete_token(stack_t_pop(s));
			my_int_t* num2 = delete_token(stack_t_pop(s));
			res = int_max(num1, num2);
			delete_int(num1);
			delete_int(num2);
		}
		else {
			if (strcmp(function, "ABS") == 0) {
				my_int_t* num = delete_token(stack_t_pop(s));
				res = int_abs(num);
				delete_int(num);
			}
			else {
				if (strcmp(function, "MOSHE") == 0)
					res = init_int(1337);
			}
		}
	}

	stack_t_push(s, create_by_int(res));
	return 1;
}


my_int_t* evaluate_rpn(queue_t* expression) {
	stack_t* s = init_stack_t();
	while (!queue_t_is_empty(expression)) {
		if (queue_t_top(expression)->is_num) {
			stack_t_push(s, queue_t_pop(expression));
		} else{
			if (queue_t_top(expression)->is_char)
				execute_operator(s, queue_t_top(expression)->parenthesis_or_operator);
			if (queue_t_top(expression)->is_function)
				execute_function(s, queue_t_top(expression)->function);

			delete_token(queue_t_pop(expression));
		}
	}
	token_t* res = stack_t_pop(s);
	stack_t_delete(s);
	return delete_token(res);
}


int op_rate(token_t* op) {
	int rate;
	switch (op->parenthesis_or_operator) {
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


int handel_chars(token_t* token, stack_t* operators_stack_t, queue_t* output) {
	if (token->is_operator) {
		while (!stack_t_is_empty(operators_stack_t) &&
			!(stack_t_top(operators_stack_t)->parenthesis_or_operator == '(') &&
			is_less_precedence(stack_t_top(operators_stack_t), token))
			queue_t_push(output, stack_t_pop(operators_stack_t));
		stack_t_push(operators_stack_t, token);
	}
	else {
		if (token->parenthesis_or_operator == '(')
			stack_t_push(operators_stack_t, token);
		else {
			while (!stack_t_is_empty(operators_stack_t) &&
				!(stack_t_top(operators_stack_t)->parenthesis_or_operator == '('))
				queue_t_push(output, stack_t_pop(operators_stack_t));
			delete_token(stack_t_pop(operators_stack_t));
			delete_token(token);
		}
	}
	return 1;
}

queue_t* shunting_yard(queue_t* tokens) {
	queue_t* output = init_queue_t();
	stack_t* operators_stack_t = init_stack_t();
	while (!queue_t_is_empty(tokens)) {
		token_t* token = queue_t_pop(tokens);
		if (token->is_num)
			queue_t_push(output, token);
		else {
			if (token->is_function)
				stack_t_push(operators_stack_t, token);
			else {
				handel_chars(token, operators_stack_t, output);
			}
		}
	}
	while (!stack_t_is_empty(operators_stack_t))
		queue_t_push(output, stack_t_pop(operators_stack_t));

	queue_t_delete(tokens);
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
