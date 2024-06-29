#include <string.h>
#include <math.h>
#include "queue.h"

#define MAX_LENGTH 1000

int execute_operator(stack_t* s, char _operator);

int execute_function(stack_t* s, char* function);

int op_rate(token_t* op);

my_int_t* evaluate_rpn(queue_t* expression);

bool is_less_precedence(token_t* op1, token_t* op2);

int handel_chars(token_t* token, stack_t* operators_stack_t, queue_t* output);

queue_t * shunting_yard(queue_t * tokens); 
