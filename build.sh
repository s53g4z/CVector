#!/bin/sh

if ! [ -f ./tests/libCV.so ]; then
	cd ./implm &&
	gcc -c -Wall -Werror -O2 -fpic CV.c &&
	gcc -shared -o libCV.so CV.o &&
	mv libCV.so ../tests/ &&
	cd .. || {
		printf 'ERROR: could not cd out';
		exit 2;
	}
fi

cd tests &&
gcc -O0 -g -Wall -Wextra -o 1 main.c -L. -lCV -Wl,-rpath=.
