
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
		fprintf(stderr, "Integer %.2llu: %d\n", i, iat(cv, i));
}

void fn(void) {
	CV* cv = CV_new(0, sizeof(int));
	int x = 5, y = 68;
	CV_push_back(CV_push_back(cv, &x), &y);
	fprintf(stderr, "%d, %d\n", iat(cv, 0), iat(cv, 1));
	*ipat(cv, 1) = 2727;
	fprintf(stderr, "%d, %d\n", iat(cv, 0), iat(cv, 1));
	CV_check(cv);
	i_cv_print(cv, 2);
	CV_delete(cv);
}

int main(int argc, char *argv[]) {
	argv[0][0] += argc - argc;
	fn();
}
