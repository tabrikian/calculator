#include "my_int.h"

my_int* init_int(int n) {
	my_int* number = (my_int*)malloc(sizeof(my_int));
	number->positive = (n >= 0);
	if (n < 0) {
		n = -n;
	}
	number->head = (i_node*)malloc(sizeof(i_node));
	number->last = number->head;
	number->amount_of_digits = 1;
	number->head->digit = n % BASE;
	n /= BASE;
	number->head->left = NULL;
	number->head->right = NULL;

	while (n > 0) {
		i_node* temp = (i_node*)malloc(sizeof(i_node));
		number->amount_of_digits++;
		temp->right = number->head;
		temp->left = NULL;
		number->head->left = temp;
		number->head = temp;
		number->head->digit = n % BASE;
		n /= BASE;
	}
	return number;
}


bool is_bigger(my_int* n1, my_int* n2) { 
	if (n1->positive && !n2->positive) {
		return true;
	}
	if (n2->positive && !n1->positive) {
		return false;
	}

	if (n1->positive && n2->positive) {
		if (n1->amount_of_digits > n2->amount_of_digits) {
			return true;
		}
		if (n1->amount_of_digits < n2->amount_of_digits) {
			return false;
		}
		i_node* i1 = n1->head;
		i_node* i2 = n2->head;
		while (i1 != n1->last && i1->digit == i2->digit) {
			i1 = i1->right;
			i2 = i2->right;
		}
		return i1->digit > i2->digit;
	}

	if (n1->amount_of_digits > n2->amount_of_digits) {
		return false;
	}
	if (n1->amount_of_digits < n2->amount_of_digits) {
		return true;
	}
	i_node* i1 = n1->head;
	i_node* i2 = n2->head;
	while (i1 != n1->last && i1->digit == i2->digit) {
		i1 = i1->right;
		i2 = i2->right;
	}
	return i1->digit < i2->digit;
}


my_int* int_add_possitive(my_int* n1, my_int* n2) {
	if (!is_bigger(n1, n2)) {
		my_int* temp = n1;
		n1 = n2;
		n2 = temp;
	}
	my_int* number = (my_int*)malloc(sizeof(my_int));
	number->positive = true;
	number->head = (i_node*)malloc(sizeof(i_node));
	number->last = number->head;
	number->amount_of_digits = 1;
	number->last->digit = (n1->last->digit + n2->last->digit) % BASE;
	number->head->left = NULL;
	number->head->right = NULL;
	int carry = (n1->last->digit + n2->last->digit) / BASE;

	i_node* i1 = n1->last->left;
	i_node* i2 = n2->last->left;
	while (i2 != NULL) {
		number->amount_of_digits++;
		i_node* temp = (i_node*)malloc(sizeof(i_node));
		temp->digit = (i1->digit + i2->digit + carry) % BASE;
		carry = (i1->digit + i2->digit + carry) / BASE;
		temp->right = number->head;
		temp->left = NULL;
		number->head = temp;
		i1 = i1->left;
		i2 = i2->left;
	}
	while (i1 != NULL) {
		number->amount_of_digits++;
		i_node* temp = (i_node*)malloc(sizeof(i_node));
		temp->digit = (i1->digit + carry) % BASE;
		carry = (i1->digit + carry) / BASE;
		temp->right = number->head;
		temp->left = NULL;
		number->head = temp;
		i1 = i1->left;
	}
	if (carry != 0) {
		number->amount_of_digits++;
		i_node* temp = (i_node*)malloc(sizeof(i_node));
		temp->digit = carry % BASE;
		temp->right = number->head;
		temp->left = NULL;
		number->head = temp;
	}
	return number;
}


my_int* int_sub_possitive(my_int* n1, my_int* n2) {
	bool possitive = true;
	if (is_bigger(n2, n1)) {
		my_int* temp = n1;
		n1 = n2;
		n2 = temp;
		possitive = false;
	}
	my_int* number = (my_int*)malloc(sizeof(my_int));
	number->positive = possitive;
	number->head = (i_node*)malloc(sizeof(i_node));
	number->last = number->head;
	number->amount_of_digits = 1;
	number->head->left = NULL;
	number->head->right = NULL;
	bool need_carry = (n1->last->digit < n2->last->digit);
	number->last->digit = need_carry*BASE + n1->last->digit - n2->last->digit;
	bool used_carry = need_carry;

	i_node* i1 = n1->last->left;
	i_node* i2 = n2->last->left;
	while (i2 != NULL) {
		number->amount_of_digits++;
		i_node* temp = (i_node*)malloc(sizeof(i_node));
		need_carry = (i1->digit < i2->digit + used_carry);
		temp->digit = need_carry * BASE + i1->digit - i2->digit - used_carry;
		used_carry = need_carry;
		temp->right = number->head;
		temp->left = NULL;
		number->head = temp;
		i1 = i1->left;
		i2 = i2->left;
	}
	while (i1 != NULL) {
		number->amount_of_digits++;
		i_node* temp = (i_node*)malloc(sizeof(i_node));
		need_carry = (i1->digit < used_carry);
		temp->digit = need_carry * BASE + i1->digit - used_carry;
		used_carry = need_carry;
		temp->right = number->head;
		temp->left = NULL;
		number->head = temp;
		i1 = i1->left;
	}
	i_node* temp = number->head;
	while (number->amount_of_digits > 1 && number->head->digit == 0){
		number->amount_of_digits--;
		number->head = number->head->right;
		number->head->left = NULL;
		free(temp);
		temp = number->head;
	}
	return number;
}


my_int* int_add(my_int * n1, my_int * n2) {
	if (!n1->positive && !n2->positive) {
		my_int* demo1 = int_minus_inplace(int_copy(n1));
		my_int* demo2 = int_minus_inplace(int_copy(n2));
		my_int* result = int_add_possitive(demo1, demo2);
		int_minus_inplace(result);
		delete_int(demo1);
		delete_int(demo2);
		return result;
	}
	if (!n1->positive) {
		n1, n2 = n2, n1;
	}
	if (!n2->positive) {
		my_int* demo = int_minus_inplace(int_copy(n2));
		my_int* result = int_sub_possitive(n1, demo);
		delete_int(demo);
		return result;
	}
	return int_add_possitive(n1, n2);
}


my_int* int_sub(my_int* n1, my_int* n2) {
	if (!n1->positive && !n2->positive) {
		my_int* demo1 = int_minus_inplace(int_copy(n1));
		my_int* demo2 = int_minus_inplace(int_copy(n2));
		my_int* result = int_sub_possitive(demo1, demo2);
		int_minus_inplace(result);
		delete_int(demo1);
		delete_int(demo2);
		return result;
	}
	if (!n1->positive) {
		n1, n2 = n2, n1;
	}
	if (!n2->positive) {
		my_int* demo = int_minus_inplace(int_copy(n2));
		my_int* result = int_add_possitive(n1, demo);
		delete_int(demo);
		return result;
	}
	return int_sub_possitive(n1, n2);
}


my_int* int_mul(my_int* n1, my_int* n2) { return NULL; }


my_int* int_div(my_int* n1, my_int* n2) { return NULL; }


my_int* int_pow(my_int* n1, my_int* n2) { return NULL; }


my_int* int_abs(my_int* n) { 
	my_int* ret = int_copy(n);
	ret->positive = true;
	return ret;
}


my_int* int_copy(my_int* n) {
	my_int* number = (my_int*)malloc(sizeof(my_int));
	number->positive = n->positive;
	number->amount_of_digits = n->amount_of_digits;

	number->head = (i_node*)malloc(sizeof(i_node));
	number->last = number->head;
	number->head->digit = n->last->digit;
	number->head->left = NULL;
	number->head->right = NULL;

	i_node* n_digit = n->last;
	while (n_digit != n->head) {
		n_digit = n_digit->left;
		i_node* temp = (i_node*)malloc(sizeof(i_node));
		temp->right = number->head;
		temp->left = NULL;
		number->head->left = temp;
		number->head = temp;
		number->head->digit = n_digit->digit;
	}
	return number;
}


my_int* int_min(my_int* n1, my_int* n2) { 
	if (is_bigger(n1, n2)) {
		return int_copy(n2);
	}
	return int_copy(n1);
}


my_int* int_max(my_int* n1, my_int* n2) { 
	if (is_bigger(n1, n2)) {
		return int_copy(n1);
	}
	return int_copy(n2);
}


my_int* int_minus_inplace(my_int* n) { 
	n->positive = !n->positive;
	return n;
}


int print_int(my_int* n) {
	if (!n->positive) {
		printf("-");
	}
	int count = 0;
	i_node* temp = n->head;
	while (temp != NULL) {
		count++;
		printf("%d", temp->digit);
		temp = temp->right;
	}
	if (count != n->amount_of_digits) {
		printf("bad %d %d", count, n->amount_of_digits);
	}
	return 1;
}


int delete_int(my_int* n) { 
	i_node* temp = n->head;
	while (n->head != NULL){
		n->head = n->head->right;
		free(temp);
		temp = n->head;
	}
	return 1; 
}
