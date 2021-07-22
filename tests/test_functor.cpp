#ifndef REFUNCTION_TEST_FUNCTOR_CPP
#define REFUNCTION_TEST_FUNCTOR_CPP

#include "assert.hpp"
#include <function.hpp>

struct Functor {
  int operator()() { return v++; }

  int v;
};

int main() {
  re::function<int()> f = Functor{0};
  RE_ASSERT_EQ(f(), 0);
  RE_ASSERT_EQ(f(), 1);
  return EXIT_SUCCESS;
}

#endif /* REFUNCTION_TEST_FUNCTOR_CPP */
