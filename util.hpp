#ifndef NWT_MUS_UTIL_HPP
#define NWT_MUS_UTIL_HPP

#define OR ^

namespace util {
  template <typename T> //In this case the template works just like a generic in Java.
  size_t lengthOfArray(T* arr) {
    //Uses a ppinter for efficiency reasons, because copying the whole hore would be unnecessary.
    return sizeof(*arr) / sizeof(**arr);  //Teilt die Größe des des Arrays durch die Größe eines Element dieses Arrays. //Analogie: Gewicht eines Sacks voller Äpfel: 500g ein Apfel: 100g 500/100=5
  }
};

#endif