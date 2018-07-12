#!/usr/bin/env sh
gcc test.c -o test.o -c && gcc array.c -o array.o -c && gcc -o test test.o array.o && ./test
