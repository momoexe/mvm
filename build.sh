set -eu

mkdir -p bin
gcc -g -std=c11 -Wall -Wextra -pedantic -Wswitch-enum src/*.c -Iinclude -o bin/mvm && ./bin/mvm