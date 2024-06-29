#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define BASE 10

typedef struct node {
	int digit;
	struct node* right;
	struct node* left;
} i_node;

typedef struct my_int_t { // head 1 2 3 last
	i_node* head; // most significant digit
	i_node* last; // least significant digit
	bool positive;
	int amount_of_digits;
} my_int_t;

my_int_t* init_int(int n);

bool is_zero(my_int_t* n);

bool is_bigger(my_int_t* n1, my_int_t* n2); // return n1 > n2

my_int_t* int_add_possitive(my_int_t* n1, my_int_t* n2); // add two numbers nuder the assumption there are possitive

my_int_t* int_sub_possitive(my_int_t* n1, my_int_t* n2); // sub two numbers nuder the assumption there are possitive

my_int_t* int_add(my_int_t* n1, my_int_t* n2); // add any two numbers

my_int_t* int_sub(my_int_t* n1, my_int_t* n2); // sub any two numbers

my_int_t* shift_left_inplace(my_int_t* n); // multiply by the base (add zero on the right)

my_int_t* shift_right_inplace(my_int_t* n); // divide by the base (delete the last digit)

my_int_t* int_mul(my_int_t* n1, my_int_t* n2); // multiply any two numbers

my_int_t* int_div(my_int_t* n1, my_int_t* n2); // divide any two numbers (ignor the reminder)

my_int_t* int_mod(my_int_t* n1, my_int_t* n2); // compute modulo (used for is_even, but we can extend it)

bool is_even(my_int_t* n);

my_int_t* int_pow(my_int_t* n1, my_int_t* n2); // compute n1**n2

my_int_t* int_abs(my_int_t* n);

my_int_t* int_copy(my_int_t* n);

my_int_t* int_min(my_int_t* n1, my_int_t* n2);

my_int_t* int_max(my_int_t* n1, my_int_t* n2);

my_int_t* int_minus_inplace(my_int_t* n);

int print_int(my_int_t* n);

int delete_int(my_int_t* n);
