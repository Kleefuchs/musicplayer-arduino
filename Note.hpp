#ifndef NWT_MUS_NOTE_HPP
#define NWT_MUS_NOTE_HPP

/*
Simples Struct mit einer Frequenz (unsigned 16 bit integer) und einem Anteil (divider), einer ganzen Note. (viertel Note, halbe Note etc.)
*/
struct Note {
  uint16_t frequency;
  int16_t divider;
};

#endif