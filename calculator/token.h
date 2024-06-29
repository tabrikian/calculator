#include "my_int.h"
#include <string.h>

typedef struct token_t {
	bool is_num;
	bool is_char;
	bool is_function;
	bool is_operator;
	my_int_t* num;
	char parenthesis_or_operator;
	char* function;
} token_t; 

token_t* copy_token(token_t* token);

char read_char_from_input(char** input);

char* read_function_from_input(char** input);

my_int_t* read_int_from_input(char** input);

bool set_token_as_char(char input, token_t* token);

bool set_token_as_function(char* input, token_t* token);

bool set_token_as_number(my_int_t* input, token_t* token);

bool parse_token(char** input, token_t* token);

token_t* create_by_num(int num);

token_t* create_by_int(my_int_t* num);

token_t* create_by_oprator(char _operator);

token_t* create_by_function(char* function);

my_int_t* delete_token(token_t* token);

int print_token(token_t* token);
