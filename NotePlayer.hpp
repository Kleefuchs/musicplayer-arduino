#ifndef NWT_MUS_NOTEPLAYER_HPP
#define NWT_MUS_NOTEPLAYER_HPP

#include "Note.hpp"

class NotePlayer {
  private:
    TrackManager* trackManager = nullptr;
  
  public:

    NotePlayer(TrackManager* trackManager) {
      this->trackManager = trackManager;
    }

    /*
    Diese Funktion spielt einzelne Noten ab.
    Jede Note besteht aus einer Frequenz und einem Teiler der eine die Länge einer ganzen Note durch den Wert des Teilers teilt.

    Jede gerade Zahl ist eine Frequenz und jede ungerade ein Teiler. Deswegen springt iterator am Ende der Funktion auch immer um 2 hoch.

    Vielen Dank an https://github.com/robsoncouto/arduino-songs für Inspiration und Lösungen für Probleme, die ich hatte, die ich aber mit der Hilfe dieses Projektes lösen konnte.
    */
    void play(Note note) {
      int16_t noteDuration = 0;
      if (note.divider < 0) {
        //Wenn der Teiler der jetzigen Note (iterator + 1) unter 0 ist dann ist die Spieldauer (ganze Note / Teiler der Jetzigen Note) der Note um 50% länger.
        noteDuration = (this->trackManager->getWholeNote() / abs(note.divider)) * 1.5;
      } else {
        //Sonst einfach normal abspielen
        noteDuration = this->trackManager->getWholeNote() / note.divider;  //Im Normalfall spielen wir die Note nicht 50% länger.
      }
      tone(BUZZER_PIN, note.frequency, noteDuration * 0.9);  //Spiele die Note mit gegebener Frequenz um 90% der Notendauer.
      delay(noteDuration);                                                              //Pausiere das das Programm um noteDuration.
      noTone(BUZZER_PIN);                                                               //Schalte den Ton aus.
    }

    
};

#endif