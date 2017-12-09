gcc -shared -o libhello.so -fPIC src/main.c -Iinclude;
LD_PRELOAD=./libhello.so $@