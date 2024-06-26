#include "my_int.h"

typedef struct token_t {
	bool is_num;
	bool is_char;
	bool is_function;
	bool is_operator;
	my_int* num;
	char _operator; // also can be ( and )
	char* function;
} token_t; 

bool set_token_as_char(char** input, token_t* token);

bool set_token_as_function(char** input, token_t* token);

bool set_token_as_number(char** input, token_t* token);

bool parse_token(char** input, token_t* token);

token_t* create_by_num(int num);

token_t* create_by_int(my_int* num);

token_t* create_by_oprator(char _operator);

token_t* create_by_function(char* function);

my_int* delete_token(token_t* token);

int print_token(token_t* token);
