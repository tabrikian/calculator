#include "token.h"

bool set_token_as_char(char** input, token_t* token) {
	token->is_char = true;
	token->is_num = false;
	token->is_function = false;
	token->_operator = *input[0];
	token->is_operator = (token->_operator != '(' && token->_operator != ')');
	*input = *input + 1;
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
	token->function = (char*)malloc(sizeof(char) * (index + 1));
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

	if (!(input[0][0] >= '0' && input[0][0] <= '9')) {
		*input = *input + 1;
	}
	int num = 0;
	while (input[0][0] >= '0' && input[0][0] <= '9') {
		num *= 10;
		num += input[0][0] - '0';
		*input = *input + 1;
	}
	token->num = init_int(num);
	return true;
}


bool parse_token(char** input, token_t* token) {
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


token_t* create_by_num(int num) {
	return create_by_int(init_int(num));
}


token_t* create_by_int(my_int* num) {
	token_t* token = (token_t*)malloc(sizeof(token_t));
	if (token == NULL)
		return NULL;

	token->is_num = true;
	token->is_function = false;
	token->is_char = false;
	token->is_operator = false;
	token->num = num;
	return token;
}


token_t* create_by_oprator(char _operator) {
	token_t* token = (token_t*)malloc(sizeof(token_t));
	if (token == NULL)
		return NULL;

	token->is_char = true;
	token->is_num = false;
	token->is_function = false;
	token->is_operator = (_operator != '(' && _operator != ')');
	token->_operator = _operator;
	return token;
}


token_t* create_by_function(char* function) {
	token_t* token = (token_t*)malloc(sizeof(token_t));
	if (token == NULL)
		return NULL;

	token->is_function = true;
	token->is_num = false;
	token->is_char = false;
	token->is_operator = false;

	token->function = function;
	return token;
}


// return null if the token is not a number, and the number in the token else
 my_int* delete_token(token_t* token) {

	if (token->is_function) {
		free(token->function);
	}
	my_int* value = NULL;
	if (token->is_num)
		value = token->num;
	free(token);
	return value;
}


 int print_token(token_t* token) {
	 if (token->is_char)
		 printf("%c", token->_operator);
	 if (token->is_num)
		 print_int(token->num);
	 if (token->is_function)
		 printf("%s", token->function);
	 printf(" ");
	 return 1;
 }

