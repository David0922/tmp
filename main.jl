mutable struct S2
  msg::Cstring
  print_arr::Ptr{Cvoid}
  fib::Ptr{Ptr{Cint}}
end

mutable struct S1
  s2::Ptr{S2}
end

println("----------")

function f()
  ccall((:f, "./my_lib.so"), Ptr{S1}, ())
end

s1 = unsafe_load(f())
s2 = unsafe_load(s1.s2)

println("s2.msg = ", unsafe_string(s2.msg))

println("----------")

function print_arr(arr)
  ccall(s2.print_arr, Cvoid, (Ptr{Cint}, Cint), arr, length(arr))
end

function fib(n)
  res = ccall(s2.fib, Ptr{Cint}, (Cint,), n)
  unsafe_wrap(Array{Cint}, res, n)
end

arr = Cint[5, 6, 5, 6, 2]
println("arr in julia: ", arr)
print_arr(arr)

println("fib(10) = ", fib(10))

println("----------")

function fill_arr(xxa)
  ccall((:fill_arr, "./my_lib.so"), Cvoid, (Ptr{Ptr{Cint}},), xxa)
end

function print_global_arr()
  ccall((:print_global_arr, "./my_lib.so"), Cvoid, ())
end

function set_global_arr_at_idx(idx, val)
  ccall((:set_global_arr_at_idx, "./my_lib.so"), Cvoid, (Cint, Cint), idx, val)
end

n = 15
xxa = Ref{Ptr{Cint}}()
fill_arr(xxa)
xa = unsafe_wrap(Array{Cint}, xxa[], n)
println("filled: ", xa)

xa[10] = -1
println("xa after modification in julia: ", xa)
print_global_arr()

set_global_arr_at_idx(12, -2)
println("xa after modification in C++: ", xa)
print_global_arr()
