#ifndef NWT_MUS_TRACKMANAGER_HPP
#define NWT_MUS_TRACKMANAGER_HPP

#include "defines.hpp"
#include "music.hpp"
#include "util.hpp"

#define CONST_TRACKMANAGER_MUS_WHOLE_NOTE_NO_TEMPO_APPLIED (60000 * 4)

class TrackManager {
  private:
    int16_t currentTrack = STARTING_TRACK;

    int16_t tempo = trackTempo[this->currentTrack];  //Ziehe das Tempo aus der Liste an Stelle von currentTrack

    float wholeNote = CONST_TRACKMANAGER_MUS_WHOLE_NOTE_NO_TEMPO_APPLIED / this->tempo;  //Berechne die Länge einer ganzen Note basierend auf dem Tempo

    uint16_t iteration = trackStarts[this->currentTrack];  //Springe an den Anfang des Tracks an currentTrack

    bool shouldPlay = false;  //Ob es spielen soll oder nicht.

    uint8_t changeValue = TEMPO_CHANGE_VALUE; //Die Größe der Veränderung am Tempo

  public:
    uint16_t getIteration() {
      return this->iteration;
    }

    uint16_t getRelativeIterator() {
      return this->iteration - trackStarts[currentTrack];
    }

    uint16_t getTrackLength() {
      return (trackStarts[this->currentTrack + 1] - trackStarts[this->currentTrack]);
    }

    float getTrackProgress() {
      return ((float)this->getRelativeIterator() / (float) this->getTrackLength());
    }

    bool atEndOfTrack() {
      return (this->getIteration() >= trackStarts[this->getTrack() + 1]);
    }

    bool atEndOfTracks() {
      return (this->getIteration() >= util::lengthOfArray(&tracks));
    }

    void stepIteration() {
      this->iteration += 2;
    }

    void setIteration(uint16_t iteration) {
      this->iteration = iteration;
    }

    int16_t getTempo() {
      return this->tempo;
    }

    void setTempo(uint16_t newTempo) {
      this->tempo = newTempo;
      this->wholeNote = CONST_TRACKMANAGER_MUS_WHOLE_NOTE_NO_TEMPO_APPLIED / this->tempo;
    }

    void resetTrackTempo() {
      this->setTempo(trackTempo[this->currentTrack]);
    }

    void decreaseTempo() {
      if (this->tempo - 5 > 0)
          this->setTempo(this->tempo - this->changeValue);
    }

    void increaseTempo() {
      this->setTempo(this->tempo + this->changeValue);
    }

    uint16_t getTrack() {
      return this->currentTrack;
    }

    bool getShouldPlay() {
      return this->shouldPlay;
    }

    void setShouldPlayer(bool shouldPlay) {
      this->shouldPlay = shouldPlay;
    }

    void toggleShouldPlay() {
      this->shouldPlay = !this->shouldPlay;
    }

    float getWholeNote() {
      return this->wholeNote;
    }

    /*
    Updated die Werte für den neuen Track. Das selbe wie am Anfang dieser Klasse nur anpassbar und aufrufbar.
    Zudem printed es den Titel des jetzigen Tracks noch raus.
    */
    void setTrack(uint8_t newCurrentTrack) {
      this->currentTrack = newCurrentTrack;
      this->setTempo(trackTempo[this->currentTrack]);
      this->iteration = trackStarts[this->currentTrack];
      #ifdef LIGHT_DEBUG
        Serial.print("\nCurrent Track is: \"");
        for (uint16_t i = 0; i < MAX_NAME_LENGTH; i++) {
          Serial.print((char)pgm_read_byte(&trackNames[this->currentTrack][i])); //Ist warscheinlich schrecklich ineffizient. Aber schwer besser zu machen. Stunden dran verschwendet: 1
        }
        Serial.print("\" which's track id is: ");
        Serial.println(this->currentTrack);
      #endif
    }
    
    void resetTrack() {
      this->setTrack(this->currentTrack);
    }

    void jumpToBeginingOfTrack() {
      this->iteration = trackStarts[this->currentTrack]; 
    }

    void previousTrack() {
      if (this->currentTrack - 1 < 0) {
          this->setTrack(NUMBER_OF_TRACKS - 1);  //Wenn der vorherige Track unter 0 ist (Existiert Nicht.) springen wir auf den letzten Track in tracks
      } else {
          this->setTrack(this->currentTrack - 1);  //Sonst springen wir einfach nur einen nach unten.
      }
    }

    void nextTrack() {
      if (this->currentTrack + 1 > NUMBER_OF_TRACKS - 1) {
        this->setTrack(0);  //Wenn der nächste Track über dem letzten Track wäre (Existiert Nicht.) springen wir auf den ersten.
      } else {
        this->setTrack(this->currentTrack + 1);  //Sonst springen wir einfach einen nach oben.
      }
    }
};

#endif