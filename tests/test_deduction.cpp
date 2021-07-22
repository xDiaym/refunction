#include "assert.hpp"
#include <function.hpp>
#include <type_traits>

struct ConstNoexceptFunctor {
  int operator()() const noexcept { return 1; }
};

int func(double) { return 0; }
int main() {
  re::function f{func}; // guide #1 deduces function<int(double)>
  static_assert(std::is_same_v<decltype(f), re::function<int(double)>>);
  int i = 5;
  // guide #2 deduces function<int(double)>
  re::function g = [&](double) { return i; };
  static_assert(std::is_same_v<decltype(g), re::function<int(double)>>);

  re::function h = ConstNoexceptFunctor();
  static_assert(std::is_same_v<decltype(h), re::function<int()>>);

  RE_ASSERT_TRUE("Compiles successfully.");
  return 0;
}