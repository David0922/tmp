```
g++ -c -fPIC -o my_lib.o my_lib.cpp && gcc -shared -o my_lib.so my_lib.o && julia ./main.jl
```
