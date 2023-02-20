#!/bin/sh

cc='clang++ -std=c++17'
release_flags='-O3 -fPIC -pipe -Wall -Wextra -fno-exceptions'
debug_flags='-O1 -pipe -Wall -Wextra -fsanitize=address'

mode="$1"
Run() { echo "$@"; $@; }

case "$mode" in
	'r')
		Run $cc $release_flags main.cc -o test.bin && Run ./test.bin ;;
	'd')
		Run $cc $debug_flags main.cc -o test.bin && Run ./test.bin ;;
	*) printf 'build.sh [r|d]\n\tr   release\n\td   debug\n';;
esac

