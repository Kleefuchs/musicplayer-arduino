#ifndef NWT_MUS_SIMPLELEDMANAGER_HPP
#define NWT_MUS_SIMPLELEDMANAGER_HPP

#include "SimpleLEDManagerRule.hpp"
#include "util.hpp"

/*
Diese Klasse managed die simplen LEDS (Alle mit einer Farbe die auf Modulus-Basis umgeschalten werden.)
*/

template <size_t arraySize>
class SimpleLEDManager {
  SimpleLEDManagerRule rules[arraySize];
  public:
    void setRule(SimpleLEDManagerRule rule, size_t index) {
      this->rules[index] = rule;
    }

    size_t getRulesSize() {
      return util::lengthOfArray(&this->rules);
    }

    /*
    Überprüft ob die Zahl die angegebenen Kriterien erfüllt, oder nicht. Wenn ja dann wird es auf den vorgegebenen state gesetzt.
    State und Kriterien werden von mehreren SimpleLEDManagerRule Regeln vorgegeben.
    */
    void applyRules(uint16_t number) {
      for(uint16_t i = 0; i < this->getRulesSize(); i++) {
        SimpleLEDManagerRule* rule = &this->rules[i];
        if(number % rule->modulus == rule->result) {
          digitalWrite(rule->PIN, rule->state);
        } else {
          digitalWrite(rule->PIN, !rule->state);
        }
      }
    }

    /*
    A way to set LEDs, which are managed by this Manager
    Has a simple check wheter or not the given Pin is managed by this Manager as long as zumindest DEBUG angeschaltet ist.
    Ich weiß wie schrecklich diese Preprocessor usage ist, aber wenn man die Preprocessor "Befehle" ignoriert kann man es verstehen. Danach versteht man es auch mit Preprocessor.
    */
    void setLED(uint8_t Pin, bool state) {
      #ifndef DISABLE_LED
        #ifdef DEBUG
        for(uint8_t i = 0; i < this->getRulesSize(); i++) {
          SimpleLEDManagerRule* rule = &this->rules[i];
          if(Pin==rule->PIN) {
        #endif
            digitalWrite(Pin, state);
            return;
        #ifdef DEBUG
          }
        }
          Serial.print(Pin);
          Serial.println(" not managed by this Manager");
        #endif
      #endif
    }

    /*
    Setz alle gemanagedten LEDs auf einen angegebenen State.
    */
    void setLEDs(bool state) {
      #ifndef DISABLE_LED
        for(uint16_t i = 0; i < this->getRulesSize(); i++) {
          SimpleLEDManagerRule* rule = &this->rules[i];
          this->setLED(rule->PIN, state);
        }
      #endif
    }

};

#endif