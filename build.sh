set -eu

mkdir -p bin
gcc -g -std=c11 -Wall -Wextra -pedantic src/*.c -Iinclude -o bin/mvm && ./bin/mvm 