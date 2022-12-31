mutable struct S2
  msg::Cstring
  print_arr::Ptr{Cvoid}
  fib::Ptr{Ptr{Cint}}
end

mutable struct S1
  s2::Ptr{S2}
end

function f()
  ccall((:f, "./my_lib.so"), Ptr{S1}, ())
end

s1 = unsafe_load(f())
s2 = unsafe_load(s1.s2)

println("s2.msg = ", unsafe_string(s2.msg))

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
