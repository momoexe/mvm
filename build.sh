set -eu

mkdir -p bin
gcc -g -std=c11 -Wall -Wextra -pedantic -Wswitch-enum mvm/*.c -Iinclude -o bin/mvm
gcc -g -std=c11 -Wall -Wextra -pedantic -Wswitch-enum masm/*.c mvm/file_io.c -Iinclude -o bin/masm