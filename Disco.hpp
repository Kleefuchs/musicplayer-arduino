#ifndef NWT_MUS_DISCO_HPP
#define NWT_MUS_DISCO_HPP

#include "defines.hpp"
#include "music.hpp"
#include "util.hpp"
#include "SimpleLEDManager.hpp"
#include "TrackManager.hpp"
#include "NotePlayer.hpp"

class Disco {
  private:
    SimpleLEDManager<3> simpleLEDManager;
    TrackManager trackManager;
    NotePlayer notePlayer; //Constructor darf erst später gecallt werden, weil trackManager jetzt noch nicht fertig ist.
  public:

    /*
    Sobald der Constructor von Disco gecallt wird wird auch der Constructor von notePlayer gecalled.
    Muss so gemacht werden, siehe oben.
    */
    Disco() : notePlayer(&trackManager) {
    }

    void setupSimpleLEDManager() {
      SimpleLEDManagerRule tmpRules[3] = {
        {LED1_PIN, 4, 0, true},
        {LED2_PIN, 4, 0 ,false},
        {LED3_PIN, 3, 0, true}
      };
      for(uint8_t i = 0; i < util::lengthOfArray(&tmpRules); i++) {
        this->simpleLEDManager.setRule(tmpRules[i], i);
      }
    }

    void setupPins() {
      /*
      Dies ist ein 2D-Array.
      Im Prinzip hält es 13 Arrays mit einer länge von 2.
      Diese halten in index-0 den Pin und in index-1 den PinMode.
      */
      int8_t pinMapping[13][2] = {
        {START_BUTTON_PIN, INPUT_PULLUP},
        {PREV_BUTTON_PIN, INPUT_PULLUP},
        {NEXT_BUTTON_PIN, INPUT_PULLUP},
        {DECREASE_TEMPO_BUTTON_PIN, INPUT_PULLUP},
        {INCREASE_TEMPO_BUTTON_PIN, INPUT_PULLUP},
        {LED1_PIN, OUTPUT},
        {LED2_PIN, OUTPUT},
        {LED3_PIN, OUTPUT},
        {GETTRACKPROGRESS_OUTPUT_PIN, OUTPUT},
        {RGB_LED_GREEN, OUTPUT},
        {RGB_LED_BLUE, OUTPUT},
        {BUZZER_PIN, OUTPUT}
      };
      for(uint8_t i = 1; i < 14; i++) {
        pinMode(pinMapping[i][0], pinMapping[i][1]);
      }
    }

    #ifdef LIGHT_DEBUG
      void setupDebug() {
        //Wenn mindestens LIGHT_DEBUG definiert ist werden Infos über die Werte in tracks ausgegeben
        #ifdef LIGHT_DEBUG
          Serial.begin(9600);  //Starte Kommunikation mit dem Master mit einer Baudrate (Symbole pro Sekunde) von 9600
          Serial.println();
          Serial.print(NUMBER_OF_TRACKS);
          Serial.println(" Lieder im PROGMEM gespeichert");
          delay(10);
          Serial.print("Einträge für tracks im PROGMEM: ");  //Anzahl der Einträge im PROGMEM für tracks
          Serial.println(util::lengthOfArray(&tracks));        //Dividire die insgesamte Größe der tracks durch die Größe eines Eintrags in tracks
          Serial.print("Menge an PROGMEM für tracks in Nutzung: ");
          Serial.print((float)sizeof(tracks) / 1000);  // Dividire die Datengröße in Bytes durch tausend (Konversion zu KyloBytes (1000 * 8 bits))
          Serial.println(" KiloBytes");
        #endif
        #ifdef HEAVY_DEBUG
          //Falls mindestens HEAVY_DEBUG definiert ist wird der gesamte Inhalt von tracks ausgelesen.
          for (uint16_t i = 0; i < util::lengthOfArray(&tracks); i++) {
            int16_t value = (int16_t)pgm_read_word(&tracks[i]);
            Serial.println(value);  //pgm_read_word wird verwendet denn diese Funktion kann 16 bit Werte im PROGMEM lesen, aber als 16 bit Integer also müssen diese explizit int16_t umgewandelt werden.
            tone(BUZZER_PIN, value);
          }
        #endif
        #ifdef LIGHT_DEBUG
          Serial.println("Musikplayer/Disco ist jetzt bereit Musik abzuspielen");
        #endif
      }
    #endif

    void setup() {
      this->setupSimpleLEDManager();
      this->setupPins();
      #ifdef LIGHT_DEBUG
        this->setupDebug();
      #endif
    }

    /*
    Diese Funktion kümmert sich um das Lichtspiel.
    */
    void playLED() {
      #ifndef DISABLE_LED
        this->simpleLEDManager.applyRules(this->trackManager.getIteration()); //Basierend auf der jetzigen Zahl sollen die festgelegten SimpleLEDManagerRule Regeln angewendet werden.
        analogWrite(GETTRACKPROGRESS_OUTPUT_PIN, this->trackManager.getTrackProgress() * 255);
        //RGB Led:
        analogWrite(RGB_LED_GREEN, (this->trackManager.getTrack() * util::lengthOfArray(&tracks)) % 255);  //Der Grün-Wert ist höher umso weiter hinten der Track ist (in der Liste)
        analogWrite(RGB_LED_BLUE, this->trackManager.getTempo() % 255);                                           //Der Blau-Wert ist der Rest von tempo geteilt durch 255 (keine Kommazahlen weil es ja ein Rest ist).
      #endif
    }

    /*
    Diese Funktion spielt einzelne Noten ab.
    Jede Note besteht aus einer Frequenz und einem Teiler der eine die Länge einer ganzen Note durch den Wert des Teilers teilt.

    Jede gerade Zahl ist eine Frequenz und jede ungerade ein Teiler. Deswegen springt iterator am Ende der Funktion auch immer um 2 hoch.

    Vielen Dank an https://github.com/robsoncouto/arduino-songs für Inspiration und Lösungen für Probleme, die ich hatte, die ich aber mit der Hilfe dieses Projektes lösen konnte.
    */
    void play() {
      int16_t noteDuration = 0;
      #ifdef DEBUG
        //Falls mindestens DEBUG definiert ist wird jede Iteration der Iterator (Jetzige Stelle in tracks) angegeben.
        Serial.print(this->trackManager.getIteration());
        Serial.println();
      #endif
      if (this->trackManager.atEndOfTrack() OR this->trackManager.atEndOfTracks()) {   //Überprüft ob iteration hinter der der letzten Note des Tracks ist, oder außerhalb der ingesamten Menge der Noten.
        this->trackManager.jumpToBeginingOfTrack();                                    //Wenn dieser Fall eintritt wird iterator wieder an den Anfang des jetzigen Tracks zurückgesetzt.
      }
      this->playLED();
      Note tmpNote = {(int16_t) pgm_read_word(&tracks[this->trackManager.getIteration()]), (int16_t) pgm_read_word(&tracks[this->trackManager.getIteration() + 1])};  //Kreirt eine Note aus ZWEI nebeneinander liegenden Werten aus dem PROGMEM. 
      this->notePlayer.play(tmpNote); //Die temporäre Note wird abgespielt
      this->trackManager.stepIteration();
    }

    void stop() {
      this->simpleLEDManager.setLEDs(LOW); //Alle LEDs die vom SimpleLEDManager gemanaged werden, werden auf LOW gestellt
      noTone(BUZZER_PIN);  //Stoppe den Buzzer
    }

    void buttonLogic() {
      //Stop/Start
      if (digitalRead(START_BUTTON_PIN) == LOW) {  //Wenn der Start Knopf gedrückt wird, wird shouldPlay auf das Gegenteil von shouldPlay gestellt also invertiert. (Stop/Start)
        this->trackManager.toggleShouldPlay();
        delay(500);
      }

      //Reset + PREV/NEXT

      //Es leuchten auch LEDs beim umschalten.

      if ((digitalRead(PREV_BUTTON_PIN) == LOW) & (digitalRead(NEXT_BUTTON_PIN) == LOW)) {
        this->trackManager.resetTrack();
      } else {
        if (digitalRead(PREV_BUTTON_PIN) == LOW) {
          this->trackManager.previousTrack();
          this->simpleLEDManager.setLED(LED2_PIN, HIGH);
          delay(500);
        }

        if (digitalRead(NEXT_BUTTON_PIN) == LOW) {
          this->trackManager.nextTrack();
          this->simpleLEDManager.setLED(LED1_PIN, HIGH);
          delay(500);
        }
      }

      //Tempo:
      if ((digitalRead(DECREASE_TEMPO_BUTTON_PIN) == LOW) & (digitalRead(INCREASE_TEMPO_BUTTON_PIN) == LOW)) {
        this->trackManager.resetTrackTempo();
      } else {
        if (digitalRead(DECREASE_TEMPO_BUTTON_PIN) == LOW) {
          this->trackManager.decreaseTempo();  
        }
        if (digitalRead(INCREASE_TEMPO_BUTTON_PIN) == LOW) {
          this->trackManager.increaseTempo();
        }
      }
    }

    /*
    In dieser Funktion werden die Knöpfe abgefragt und die Musik wird basierend auf den mit den Knöpfen erlangten Werten abgespielt, oder auch nicht. (shouldPlay)
    */
    void loop() {
      this->buttonLogic();
      if (this->trackManager.getShouldPlay() == true) {
        this->play();  //Wenn shouldPlay wahr ist wird die play Funktion aufgerufen.
      } else {
        this->stop();  //Sonst wird alles gestoppt.
      }
    }
};

#endif