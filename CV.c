#include "CV.h"

// Definition of the CVector struct.
struct CVector {
	unsigned char *arr;
	llu nslot;  // total number of slots that can be used to hold elements
	llu nelem;
	llu elem_sz;
};

// malloc().
static void *CVmalloc(llu bytes) {
	void *p = malloc(bytes);
	if (!p)
		abort();
	return p;
}

// Abort if val1 * val2 will overflow.
static void CVprevent_llu_mul_overflow(llu val1, llu val2) {
	if (val1 > LLU_MAX / val2)
		abort();
	return;
}

// Double the CV internal storage.
static void CVextend(CV* cv) {
	CVprevent_llu_mul_overflow(cv->nslot, cv->elem_sz);
	CVprevent_llu_mul_overflow(cv->nslot * cv->elem_sz, 2);
	void *newarr = CVmalloc(cv->nslot * cv->elem_sz * 2);
	CVprevent_llu_mul_overflow(cv->nslot, cv->elem_sz);
	memcpy(newarr, cv->arr, cv->nelem * cv->elem_sz);
	free(cv->arr);
	cv->arr = newarr;
	//CVprevent_llu_mul_overflow(cv->nslot, 2);  // redundant b/c of prev check
	cv->nslot *= 2;
	return;
}

void CV_clear(CV *cv) {
	cv->nelem = 0;
}

llu CV_size(CV *cv) {
	return cv->nelem;
}

void *CV_at(CV*cv, llu index) {
	if (index >= cv->nelem)
		abort();
	CVprevent_llu_mul_overflow(index, cv->elem_sz);
	return cv->arr + index * cv->elem_sz;
}

CV* CV_push_back(CV *cv, void *ep) {
	if (cv->nslot == cv->nelem)
		CVextend(cv);
	CVprevent_llu_mul_overflow(cv->nelem, cv->elem_sz);  // redundant check?
	memcpy(cv->arr + cv->nelem * cv->elem_sz, ep, cv->elem_sz);
	cv->nelem++;
	return cv;
}

void CV_delete(CV* cv) {
	free(cv->arr);
	free(cv);
}

CV *CV_new(llu nelem_req, llu elem_sz) {
	if (nelem_req == 0)
		nelem_req++;
	CV *cv = CVmalloc(sizeof(CV));
	CVprevent_llu_mul_overflow(nelem_req, elem_sz);
	cv->arr = CVmalloc(nelem_req * elem_sz);
	cv->nslot = nelem_req;
	cv->nelem = 0;
	cv->elem_sz = elem_sz;
	
	return cv;
}

void CV_check(CV *cv, bool quiet) {
	bool okay = true;
	if (cv->nslot < cv->nelem) okay = false;
	if (cv->arr == nullptr) okay = false;
	if (cv->elem_sz == 0) okay = false;
	
	CVprevent_llu_mul_overflow(cv->nslot, cv->elem_sz);
	if (!quiet) {
		for (llu i = 0; i < cv->nslot * cv->elem_sz; i++)
			fprintf(stderr, "byte %llu: %.2x\n", i, *(cv->arr + i));
	}

	if (!okay) abort();
}
