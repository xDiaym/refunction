<h1 align="center">:zap: re::function</h1>

[![CI](https://github.com/xDiaym/refunction/actions/workflows/ci.yml/badge.svg)](https://github.com/xDiaym/refunction/actions/workflows/ci.yml)  
## What is it?
re::function is an attempt to implement `std::function` on its own.

## :warning: Warning
It's a very slow implementation. It can be unstable, so use at your own risk.

## Why
Just for fun. An exercise to rewrite a small part of the standard library.
I tried to follow a [bunch of methods](https://en.cppreference.com/w/cpp/utility/functional/function) from C++20, while using C++17.

## Installation
Clone the library or add it via git modules(recommended).
```shell
# In your repo directory
$ git submodule add https://github.com/xDiaym/refunction
```

Add in your `CMakeLists.txt` this line:
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE refunction)
```

It should be enough.

### Build params
Additional you can disable RTTI support and lose `re::function::target` and 
`re::function::target_type` methods. For that use option `NO_RTTI`.

Also, you can enable test build. Just add `BUILD_TESTS` option.

## Testing
```shell
$ ./bin/test.py
# Or in build directory
$ ctest
```

## License
Licensed under [MIT](https://github.com/xDiaym/refunction/LICENSE)
