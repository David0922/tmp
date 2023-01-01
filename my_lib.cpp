#include <cassert>
#include <iostream>

using namespace std;

void print_arr(int* arr, int n) {
  cout << "print_arr from C++: ";
  for (int i = 0; i < n; ++i) cout << arr[i] << ' ';
  cout << endl;
}

int* fib(int n) {
  assert(n >= 2);

  int* res = new int[n];

  res[0] = 0;
  res[1] = 1;

  for (int i = 2; i < n; ++i) res[i] = res[i - 2] + res[i - 1];

  return res;
}

struct S2 {
  const char* msg;
  void (*print_arr)(int*, int);
  int* (*fib)(int);
};

struct S1 {
  S2* s2;
};

int global_arr_len = 20;
int* global_arr = fib(global_arr_len);

extern "C" {
S1* f() {
  S1* s1 = new S1();
  S2* s2 = new S2();

  s1->s2 = s2;

  s2->msg = "happy new year";
  s2->print_arr = print_arr;
  s2->fib = fib;

  return s1;
}

void fill_arr(int** arr) { *arr = global_arr; }

void print_global_arr() { print_arr(global_arr, global_arr_len); }

void set_global_arr_at_idx(int idx, int val) {
  assert(idx < global_arr_len);
  global_arr[idx] = val;
}
}

int main() {
  int n = 10;

  S2 s2 = *(f()->s2);

  // s2.print_arr(s2.fib(n), n);

  int* arr = nullptr;
  fill_arr(&arr);
  s2.print_arr(arr, n);
}
