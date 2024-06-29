#include "token.h"

token_t* copy_token(token_t* token) {
	if (token->is_num) {
		return create_by_int(int_copy(token->num));
	}
	if (token->is_char) {
		return create_by_oprator(token->parenthesis_or_operator);
	}
	if (token->is_function) {
		return create_by_function(token->function);
	}
	return NULL;
}


char read_char_from_input(char** input) {
	char result = *input[0];
	*input = *input + 1;
	return result;
}


char* read_function_from_input(char** input) {
	char* result = *input[0];
	int index = 0;
	while ((input[0][index] >= 'A' && input[0][index] <= 'Z') || input[0][index] == '_') {
		index++;
	}
	result = (char*)malloc(sizeof(char) * (index + 1));
	result[index] = 0;
	for (int i = 0; i < index; i++) {
		result[i] = *(*input + i);
	}
	*input = *input + index;
	return result;
}


my_int_t* read_int_from_input(char** input) {
	if (!(input[0][0] >= '0' && input[0][0] <= '9')) {
		*input = *input + 1;
	}
	int num = 0;
	while (input[0][0] >= '0' && input[0][0] <= '9') {
		num *= 10;
		num += input[0][0] - '0';
		*input = *input + 1;
	}
	return init_int(num);
}


bool set_token_as_char(char input, token_t* token) {
	token->is_char = true;
	token->is_num = false;
	token->is_function = false;
	token->parenthesis_or_operator = input;
	token->is_operator = (token->parenthesis_or_operator != '(' && token->parenthesis_or_operator != ')');
	return true;
}


bool set_token_as_function(char* input, token_t* token) {
	token->is_function = true;
	token->is_num = false;
	token->is_char = false;
	token->is_operator = false;
	
	token->function = (char*)malloc((strlen(input)+1)*sizeof(char));
	for (int i = 0; i <= strlen(input); i++) {
		token->function[i] = input[i];
	}
	return true;
}


bool set_token_as_number(my_int_t* input, token_t* token) {
	token->is_num = true;
	token->is_function = false;
	token->is_char = false;
	token->is_operator = false;

	token->num = input;
	return true;
}


bool parse_token(char** input, token_t* token) {
	if (input[0][0] == '(' || input[0][0] == '+' || input[0][0] == '-' || input[0][0] == '*'
		|| input[0][0] == '/' || input[0][0] == '^' || input[0][0] == ')') {
		return set_token_as_char(read_char_from_input(input), token);
	}
	if ((input[0][0] >= 'A' && input[0][0] <= 'Z') || input[0][0] == '_') {
		char* func = read_function_from_input(input);
		bool res = set_token_as_function(func, token);
		free(func);
		return res;
	}
	if (input[0][0] >= '0' && input[0][0] <= '9') {
		return set_token_as_number(read_int_from_input(input), token);
	}
	return false;
}


token_t* create_by_num(int num) {
	return create_by_int(init_int(num));
}


token_t* create_by_int(my_int_t* num) {
	token_t* token = (token_t*)malloc(sizeof(token_t));
	if (token == NULL)
		return NULL;

	set_token_as_number(num, token);
	return token;
}


token_t* create_by_oprator(char parenthesis_or_operator) {
	token_t* token = (token_t*)malloc(sizeof(token_t));
	if (token == NULL)
		return NULL;

	set_token_as_char(parenthesis_or_operator, token);
	return token;
}


token_t* create_by_function(char* function) {
	token_t* token = (token_t*)malloc(sizeof(token_t));
	if (token == NULL)
		return NULL;

	set_token_as_function(function, token);
	return token;
}


// return null if the token is not a number, and the number in the token else
 my_int_t* delete_token(token_t* token) {

	if (token->is_function) {
		free(token->function);
	}
	my_int_t* value = NULL;
	if (token->is_num)
		value = token->num;
	free(token);
	return value;
}


 int print_token(token_t* token) {
	 if (token->is_char)
		 printf("%c", token->parenthesis_or_operator);
	 if (token->is_num)
		 print_int(token->num);
	 if (token->is_function)
		 printf("%s", token->function);
	 printf(" ");
	 return 1;
 }

