#include "assert.hpp"
#include <function.hpp>

int main() {
  re::function<int()> a([]() { return 42; }), b([]() { return 12; });
  RE_ASSERT_EQ(a(), 42);
  RE_ASSERT_EQ(b(), 12);
  re::swap(a, b);
  RE_ASSERT_EQ(a(), 12);
  RE_ASSERT_EQ(b(), 42);
  a.swap(b);
  RE_ASSERT_EQ(a(), 42);
  RE_ASSERT_EQ(b(), 12);
  return 0;
}
