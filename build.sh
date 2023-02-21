#!/bin/sh

cc='clang++ -std=c++17'
cflags='-fPIC'
release_flags='-O3 -pipe -Wall -Wextra -fno-exceptions'
debug_flags='-O1 -pipe -Wall -Wextra -fsanitize=address'

mode="$1"
Run() { echo "$@"; $@; }

case "$mode" in
	'r')
		Run $cc $cflags $release_flags main.cc -o test.bin && Run ./test.bin ;;
	'd')
		Run $cc $cflags $debug_flags main.cc -o test.bin && Run ./test.bin ;;
	*) printf 'build.sh [r|d]\n\tr   release\n\td   debug\n';;
esac

