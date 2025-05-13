#ifndef NWT_MUS_SIMPLELEDMANAGERRULE_HPP
#define NWT_MUS_SIMPLELEDMANAGERRULE_HPP

struct SimpleLEDManagerRule {
  uint8_t PIN;
  uint8_t modulus;
  uint8_t result;
  bool state;
};

#endif