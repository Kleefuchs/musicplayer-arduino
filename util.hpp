#ifndef NWT_MUS_UTIL_HPP
#define NWT_MUS_UTIL_HPP

#define OR ^

namespace util {
  template <typename T>
  size_t lengthOfArray(T* arr) {
    return sizeof(*arr) / sizeof(**arr);
  }
};

#endif