#include "assert.hpp"
#include <function.hpp>
#include <functional>

int f(int, int) { return 1; }
int g(int, int) { return 2; }

int main() {
  re::function<int(int, int)> func = std::plus<int>();
  RE_ASSERT_TRUE(func.target<std::plus<int>>());

  func = std::minus<int>();
  RE_ASSERT_TRUE(func.target<std::minus<int>>());

  func = f;
  auto fptr = func.target<int (*)(int, int)>();
  RE_ASSERT_EQ(*fptr, &f);
  RE_ASSERT_EQ((*fptr)(0, 0), 1);

  func = g;
  auto gptr = func.target<int (*)(int, int)>();
  RE_ASSERT_EQ(*gptr, &g);
  RE_ASSERT_EQ((*gptr)(0, 0), 2);

  return 0;
}
