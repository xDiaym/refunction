#include "assert.hpp"
#include <function.hpp>

int main() {
  re::function<void()> f(nullptr);
  RE_ASSERT_EQ(static_cast<bool>(f), false);
  f = []() {};
  RE_ASSERT_EQ(static_cast<bool>(f), true);
  return 0;
}