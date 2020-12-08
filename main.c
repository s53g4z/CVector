
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
		fprintf(stderr, "Integer %.2llu: %5d\n", i, iat(cv, i));
	fprintf(stderr, "\n");
}

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

void add_arr_to_cv(CV* cv, long long *arr, llu sz) {
	for (llu i = 0; i < sz; i++)
		CV_push_back(cv, &arr[i]);
}

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

int main(int argc, char *argv[]) {
	argv[0][0] += argc - argc;
	test_cv_1();
	test_cv_2();
}
