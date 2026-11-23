set -eu

mkdir -p bin
gcc -g -std=c11 -Wall -Wextra -pedantic -Wswitch-enum -fsanitize=address,undefined mvm/*.c -Iinclude -o bin/mvm
gcc -g -std=c11 -Wall -Wextra -pedantic -Wswitch-enum -fsanitize=address,undefined masm/*.c -Iinclude -o bin/masm