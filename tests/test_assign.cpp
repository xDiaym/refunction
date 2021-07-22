#include "assert.hpp"
#include <function.hpp>
#include <functional>
#include <iostream>

struct Functor {
  int operator()(int value) { return value + a; }

  int a;
};

int function(int value) { return value; }

int main() {
  re::function<int(int)> f = [](int value) { return 42; };
  RE_ASSERT_EQ(f(0), 42);
  f = Functor{1};
  RE_ASSERT_EQ(f(0), 1);
  f = function;
  RE_ASSERT_EQ(f(0), 0);
  return 0;
}