#!/bin/sh

if [ ! -f ./tests/libCV.so ]; then
	printf "Building library ...";
	cd ./implm &&
	gcc -c -Wall -Werror -O2 -fpic CV.c &&
	gcc -shared -o libCV.so CV.o &&
	mv libCV.so ../tests/ &&
	cd .. || {
		printf 'ERROR: could not cd out';
		exit 2;
	}
	printf " done.\n";
fi

printf "Building test program ...";
cd tests &&
gcc -O0 -g -Wall -Wextra -o 1 main.c -L. -lCV -Wl,-rpath=. &&
printf " done.\n";
