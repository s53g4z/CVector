#ifndef CVHCVH
#define CVHCVH

#include <stdlib.h>
#include <string.h>
#include <stdio.h>  // for CV_check() internal array printing

#define nullptr ((void *)0)
typedef unsigned char bool;
#define true 1
#define false 0
typedef long long unsigned llu;
#define LLU_MAX ~0llu

struct CVector;
typedef struct CVector CV;

CV *CV_new(llu nelem_req, llu nelem_sz);	// Return a new CV.
void CV_delete(CV *cv);						// Delete the CV.
CV *CV_push_back(CV *cv, void *ep);			// Append to the CV.
void *CV_at(CV *cv, llu index);				// Return a ptr to a CV element.
void CV_check(CV *cv);						// Run basic self-checks on CV.

#endif