#ifndef FUNCTION_FUNCTION_HPP
#define FUNCTION_FUNCTION_HPP

#include <stdexcept>
#include <utility>
#if !defined(RE_FUNCTION_NO_RTTI)
#include <typeinfo>
#endif

namespace re {

class bad_function_call : public std::exception {
  const char *what() const noexcept override { return "Bad function call."; }
};

template <typename> class function;

template <typename Ret, typename... Args> class function<Ret(Args...)> {
public:
  using result_type = Ret;

  function() noexcept : callable(nullptr) {}
  function(std::nullptr_t) noexcept : callable(nullptr) {}
  function(const function &other)
      : callable(new callable_impl<Ret(Args...)>(other.callable)) {}
  function(function &&other) noexcept { std::swap(callable, other.callable); }
  template <typename Func>
  function(Func &&func)
      : callable(new callable_impl<Func>(std::forward<Func>(func))) {}
  /** Special constructor for function pointers. */
  function(Ret (*fptr)(Args...))
      : callable(new callable_impl<Ret (*)(Args...)>(std::move(fptr))) {}

  function &operator=(const function &other) {
    if (&other != this) {
      function(other).swap(*this);
    }
    return *this;
  }

  function &operator=(function &&other) {
    std::swap(callable, other.callable);
    return *this;
  }

  function &operator=(std::nullptr_t) noexcept {
    delete callable;
    callable = nullptr;
    return *this;
  }

  template <class F> function &operator=(F &&f) {
    function(std::forward<F>(f)).swap(*this);
    return *this;
  }

  template <class F> function &operator=(std::reference_wrapper<F> f) noexcept {
    function(f).swap(*this);
    return *this;
  }

  result_type operator()(Args &&... args) const {
    if (callable == nullptr) {
      throw bad_function_call();
    }
    return callable->call(std::forward<Args>(args)...);
  }

  explicit operator bool() const noexcept { return callable != nullptr; }

  void swap(function<Ret(Args...)> &other) noexcept {
    std::swap(callable, other.callable);
  }

#if !defined(RE_FUNCTION_NO_RTTI)
  const std::type_info &target_type() const noexcept {
    return callable->target_type();
  }

  template <typename T> T *target() noexcept {
    if (typeid(T) == callable->target_type()) {
      return reinterpret_cast<T *>(callable->get_ptr_to_callable());
    }
    return nullptr;
  }

  template <typename T> const T *target() const noexcept {
    if (typeid(T) == callable->target_type()) {
      return reinterpret_cast<const T *>(callable->get_ptr_to_callable());
    }
    return nullptr;
  }
#endif

  ~function() { delete callable; }

private:
  class callable_base {
  public:
    /** Functors can change their state, so the method is not marked as const */
    virtual Ret call(Args &&... args) = 0;

#if !defined(RE_FUNCTION_NO_RTTI)
    virtual const std::type_info &target_type() const noexcept = 0;
    virtual void *get_ptr_to_callable() noexcept = 0;
    virtual const void *get_ptr_to_callable() const noexcept = 0;
#endif

    virtual ~callable_base() {}
  };

  template <typename Impl> class callable_impl : public callable_base {
  public:
    explicit callable_impl(Impl &&impl_) : impl(std::move(impl_)) {}
    callable_impl(const callable_impl &other) : impl(other.impl) {}

    Ret call(Args &&... args) override {
      return impl(std::forward<Args>(args)...);
    }

#if !defined(RE_FUNCTION_NO_RTTI)
    const std::type_info &target_type() const noexcept override {
      return typeid(impl);
    }

    void *get_ptr_to_callable() noexcept override { return &impl; }
    const void *get_ptr_to_callable() const noexcept override { return &impl; }
#endif

  private:
    Impl impl;
  };

  callable_base *callable;
};

namespace {

template <typename> struct func_trait;

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...)> {
  using type = Ret(Args...);
};

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...) const> {
  using type = Ret(Args...);
};

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...) noexcept> {
  using type = Ret(Args...);
};

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...) const noexcept> {
  using type = Ret(Args...);
};

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...) &> {
  using type = Ret(Args...);
};

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...) & noexcept> {
  using type = Ret(Args...);
};

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...) const &> {
  using type = Ret(Args...);
};

template <typename T, typename Ret, typename... Args>
struct func_trait<Ret (T::*)(Args...) const &noexcept> {
  using type = Ret(Args...);
};

} // namespace

template <typename Ret, typename... Args>
function(Ret (*)(Args...))->function<Ret(Args...)>;

template <typename F>
function(F)->function<typename func_trait<decltype(&F::operator())>::type>;

template <class R, class... Args>
void swap(function<R(Args...)> &lhs, function<R(Args...)> &rhs) noexcept {
  lhs.swap(rhs);
}

} /* namespace re */

#endif /* FUNCTION_FUNCTION_HPP */
