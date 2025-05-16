#ifndef NWT_MUS_SIMPLELEDMANAGERRULE_HPP
#define NWT_MUS_SIMPLELEDMANAGERRULE_HPP

/*
Simple Regel für den SimpleLEDManager
PIN ist der anzuspielende PIN als unsigned 8 bit integer.
modulus ist ein Kriterium durch welche Zahl der Iterator teilbar sein muss. Ist ein unsigned 8 bit Integer
result ist ein Kriterium was der Rest bei der Division durch modulus sein muss, als unsigned 8 bit Integer
state ist an oder aus. Wenn beide Kriterien erfüllt werden soll das der Zustand der LED sein.
*/

struct SimpleLEDManagerRule {
  uint8_t PIN;
  uint8_t modulus;
  uint8_t result;
  bool state;
};

#endif