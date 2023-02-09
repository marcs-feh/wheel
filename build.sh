#!/bin/sh

cc='clang++ -std=c++17'
release_flags='-O3 -pipe -Wall -Wextra -fno-exceptions'
debug_flags='-O1 -pipe -Wall -Wextra -fsanitize=address'

mode="$1"

case "$mode" in
	'r')
		$cc $release_flags main.cc -o main.bin && ./main.bin ;;
	'd')
		$cc $debug_flags main.cc -o main.bin && ./main.bin ;;
	*) printf 'build.sh [r|d]\n\tr   release\n\td   debug\n';;
esac

