#include <stdbool.h>
#include <stdlib.h>

typedef struct token_t {
	bool is_num;
	bool is_char;
	bool is_function;
	bool is_operator;
	int num;
	char _operator; // also can be ( and )
	char* function;
} token_t; 

token_t* create_by_num(int num);
token_t* create_by_oprator(char _operator);
token_t* create_by_function(char* function);
int delete_token(token_t* token);
