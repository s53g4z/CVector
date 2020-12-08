
#include "CV.h"

// int version of CV_at
int iat(CV *cv, llu index) {
	return *(int *)CV_at(cv, index);
}

// int* version of CV_at
int *ipat(CV *cv, llu index) {
	return (int *)CV_at(cv, index);
}

// Print the ints in a CV.
void i_cv_print(CV *cv, llu sz) {
	for (llu i = 0; i < sz; i++)
		fprintf(stderr, "Integer %2llu: %5d\n", i, iat(cv, i));
	fprintf(stderr, "\n");
}

// Assert.
void aq(llu okay) {
	if (!okay)
		abort();
}

// Generic CV test 1.
void test_cv_1(void) {
	CV* cv = CV_new(0, sizeof(int));
	int x = 5, y = 68, z = 855;
	CV_push_back(CV_push_back(CV_push_back(cv, &x), &y), &z);;
	
	i_cv_print(cv, 3);
	*ipat(cv, 1) = 2727;
	i_cv_print(cv, 3);
	
	CV_check(cv, true);
	CV_delete(cv);
}

// Copy the elements of an array of long long to a CV.
void add_arr_to_cv(CV* cv, long long *arr, llu sz) {
	for (llu i = 0; i < sz; i++)
		CV_push_back(cv, &arr[i]);
}

// Generic CV test 2.
void test_cv_2(void) {
	CV* cv = CV_new(1, sizeof(long long));
	long long arr[] = { 14748, 22074, 2291, 16121, 31332 };
	add_arr_to_cv(cv, arr, sizeof(arr)/sizeof(arr[0]));
	i_cv_print(cv, sizeof(arr)/sizeof(arr[0]));
	
	long long arr2[] = { 20034, 25541, 17462, 24214, 1015 };
	add_arr_to_cv(cv, arr2, sizeof(arr2)/sizeof(arr2[0]));
	i_cv_print(cv, (sizeof(arr) + sizeof(arr2)) / sizeof(long long));

	CV_check(cv, true);
	CV_delete(cv);
}

// Print a CV full of long long elements.
void ll_cv_print(CV* cv) {
	for (llu i = 0; i < CV_size(cv); i++)
		fprintf(stderr, "%lld ", *(long long *)CV_at(cv, i));
	fprintf(stderr, "\n");
}

// Test inserting into a CV at index idx with starting size start_size.
void test_cv_3__insert(llu start_size, llu idx) {
	CV *cv = CV_new(start_size, sizeof(long long));
	long long arr[] = { 25957, 29292, -62, 8875, 15, 5243, 11913, -79, 24482, 2 };
	for (llu i = 0; i < 10; i++)
		CV_insert(cv, idx, &arr[i]);

	aq(10 + idx == CV_size(cv));
	ll_cv_print(cv);
	
	CV_check(cv, true);
	CV_delete(cv);
}

// Test inserting into a CV at multiple indices with starting size start_size.
void test_cv_4__insert(llu start_size) {
	CV *cv = CV_new(start_size, sizeof(long long));
	long long arr[] = { 17545, 7971, 21525, 25602, 18500 };
	add_arr_to_cv(cv, arr, 5);  // populate CV

	// test inserting at random spots
	long long arr2[] = { 28830, 8119, 19615, 23474, 7978 };
	CV_insert(cv, 3, &arr2[2]);
	CV_insert(cv, 1, &arr2[4]);
	CV_insert(cv, 10, &arr2[0]);
	
	aq(11 == CV_size(cv));
	ll_cv_print(cv);
	CV_check(cv, true);
	CV_delete(cv);
	
	// more testing by inserting at random spots
	cv = CV_new(start_size, sizeof(long long));
	long long arr3[] = { 4, 5, 6, 7, 8 };
	add_arr_to_cv(cv, arr3, 5);
	long long arr4[] = { 3, 66 };
	CV_insert(cv, 0, &arr4[0]);
	CV_insert(cv, 3, &arr4[1]);
	
	ll_cv_print(cv);
	CV_check(cv, true);
	CV_delete(cv);
}

// Test CV_erase(). The element at index is erased.
void test_cv_5__erase(llu start_size, llu index) {
	CV *cv = CV_new(start_size, sizeof(long long));
	aq(CV_size(cv) == 0);
	long long arr[] = { 70, 71, 72, 55, 73, 74, 75, 32770, 76 };
	add_arr_to_cv(cv, arr, sizeof(arr)/sizeof(arr[0]));
	
	CV_erase(cv, 3);
	ll_cv_print(cv);
	CV_erase(cv, index);
	ll_cv_print(cv);
	CV_check(cv, true);
	aq(CV_size(cv) == 7);
	CV_delete(cv);
}

void test_cv_3__runner(void) {
	test_cv_3__insert(0, 0);
	test_cv_3__insert(1, 0);
	test_cv_3__insert(2, 0);
	test_cv_3__insert(0, 1);
	test_cv_3__insert(0, 100);
	test_cv_3__insert(1, 100);
	test_cv_3__insert(3, 100);
}

void test_cv_4__runner(void) {
	test_cv_4__insert(0);
	test_cv_4__insert(1);
	test_cv_4__insert(2);
	test_cv_4__insert(50);
}

void test_cv_5__runner(void) {
	test_cv_5__erase(0, 6);
	test_cv_5__erase(1, 6);
	test_cv_5__erase(77, 6);
	
	test_cv_5__erase(0, 7);
	test_cv_5__erase(1, 7);
	test_cv_5__erase(81, 7);
	
	test_cv_5__erase(0, 0);
	test_cv_5__erase(1, 0);
	test_cv_5__erase(9, 0);
}

int main(int argc, char *argv[]) {
	argv[0][0] += argc - argc;
	test_cv_1();
	test_cv_2();
	test_cv_3__runner();
	test_cv_4__runner();
	test_cv_5__runner();
}
