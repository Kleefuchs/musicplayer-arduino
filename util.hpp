#ifndef NWT_MUS_UTIL_HPP
#define NWT_MUS_UTIL_HPP

#define OR ^

namespace util {
  template <typename T>
  size_t lengthOfArray(T* arr) {
    return sizeof(*arr) / sizeof(**arr);  //Teilt die Größe des des Arrays durch die Größe eines Element dieses Arrays. //Analogie: Gewicht eines Sacks voller Äpfel: 500g ein Apfel: 100g 500/100=5
  }
};

#endif