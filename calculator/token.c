#include "token.h"

token_t* create_by_num(int num) {
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

// return 1 if the token is not a number, and the number in the token else
int delete_token(token_t* token) {

	if (token->is_function) {
		free(token->function);
	}
	int value = 1;
	if (token->is_num)
		value = token->num;
	free(token);
	return value;
}