#include "assert.hpp"
#include <function.hpp>

int main() {
  re::function<void()> f(nullptr);
  RE_THROWS(f(), re::bad_function_call);
  return 0;
}
