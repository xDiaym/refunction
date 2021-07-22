#ifndef REFUNCTION_ASSERT_HPP
#define REFUNCTION_ASSERT_HPP

#include <cstdlib>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#define STR_IMPL(x) #x
#define STR(x) STR_IMPL(x)

#ifdef __FUNCSIG__
#define __RE_FUNC_SIG__ __FUNCSIG__
#else
#define __RE_FUNC_SIG__ __PRETTY_FUNCTION__
#endif

namespace re::test {

struct meta_info {
  size_t line;
  const char *file;
  const char *date;
  const char *function;
};

struct assertion_result {
  bool success;
  std::string message;
};

template <typename T1, typename T2, typename Comparator>
assertion_result compare(Comparator cmp, T1 first, std::string first_repr,
                         T2 second, std::string second_repr, std::string expr) {
  std::stringstream ss;
  ss << first_repr << " " << expr << " " << second_repr << " (" << first << " "
     << expr << " " << second << ").";
  return assertion_result{cmp(first, second), ss.str()};
}

void assert(const assertion_result &result, meta_info meta) {
  if (result.success) {
    return;
  }
  std::cerr << "Test failed in " << meta.file << "(" << meta.line << "). "
            << "In function " << meta.function << " at " << meta.date
            << std::endl
            << result.message;
  std::exit(EXIT_FAILURE);
}

} /* namespace re::test */

#define _COLLECT_METAINFO()                                                    \
  re::test::meta_info { __LINE__, __FILE__, __DATE__, __RE_FUNC_SIG__ }

#define RE_ASSERT(result) re::test::assert((result), _COLLECT_METAINFO())

#define RE_ASSERT_EQ(x, y)                                                     \
  RE_ASSERT(re::test::compare(std::equal_to<>(), x, STR(x), y, STR(y), "=="))

#define RE_ASSERT_TRUE(x)                                                      \
  RE_ASSERT((re::test::assertion_result{                                       \
      static_cast<bool>(x), std::string(STR(x) " should be true.")}))

#define RE_THROWS(expr, exception_)                                            \
  do {                                                                         \
    bool exception_was_thrown = false;                                         \
    try {                                                                      \
      expr;                                                                    \
    } catch (exception_) {                                                     \
      exception_was_thrown = true;                                             \
    } catch (...) {                                                            \
    }                                                                          \
    RE_ASSERT((re::test::assertion_result{                                     \
        exception_was_thrown,                                                  \
        std::string(STR(expr) " should throw " STR(exception) ".")}));         \
  } while (false)

#endif /* REFUNCTION_ASSERT_HPP */
