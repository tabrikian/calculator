#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define BASE 10

typedef struct node {
	int digit;
	struct node* right;
	struct node* left;
} i_node;

typedef struct my_int { // head 1 2 3 last
	i_node* head; // most significant digit
	i_node* last; // least significant digit
	bool positive;
	int amount_of_digits;
} my_int;

my_int* init_int(int n);

bool is_zero(my_int* n);

bool is_bigger(my_int* n1, my_int* n2);

my_int* int_add_possitive(my_int* n1, my_int* n2);

my_int* int_sub_possitive(my_int* n1, my_int* n2);

my_int* int_add(my_int* n1, my_int* n2);

my_int* int_sub(my_int* n1, my_int* n2);

my_int* shift_left_inplace(my_int* n);

my_int* shift_right_inplace(my_int* n);

my_int* int_mul(my_int* n1, my_int* n2);

my_int* int_div(my_int* n1, my_int* n2);

my_int* int_mod(my_int* n1, my_int* n2);

bool is_even(my_int* n);

my_int* int_pow(my_int* n1, my_int* n2);

my_int* int_abs(my_int* n);

my_int* int_copy(my_int* n);

my_int* int_min(my_int* n1, my_int* n2);

my_int* int_max(my_int* n1, my_int* n2);

my_int* int_minus_inplace(my_int* n);

int print_int(my_int* n);

int delete_int(my_int* n);
