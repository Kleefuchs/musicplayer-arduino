#ifndef NWT_MUS_DEFINES_HPP
#define NWT_MUS_DEFINES_HPP

#define BUZZER_PIN 2                        //Main Part of the Project.
#define LED1_PIN 3
#define LED2_PIN 4
#define LED3_PIN 10                         //NEEDS TO BE PWM

#define GETTRACKPROGRESS_OUTPUT_PIN 9    //NEEDS TO BE PWM //Used for RGB LED and a normal LED. Just run them in parallel (KEEP IN MIND EVERY SINGLE ONE OF THE LEDs NEEDS THEIR OWN RESISTOR)

#define START_BUTTON_PIN 13

#define PREV_BUTTON_PIN 12
#define NEXT_BUTTON_PIN 11

#define DECREASE_TEMPO_BUTTON_PIN 8
#define INCREASE_TEMPO_BUTTON_PIN 7

#define RGB_LED_GREEN 6                     //NEEDS TO BE PWM
#define RGB_LED_BLUE 5                      //NEEDS TO BE PWM

#define STARTING_TRACK 11                   //Get rickrolled L bozo //Ignore my silly comments //I MUST SOMEHOW KEEP MY SANITY

//#define DISABLE_LED                       //In here for light-sensitive people //Just Uncomment it

#define TEMPO_CHANGE_VALUE 5                //Amount by which the tempo changes on press of Tempo-Change-Button

/*
Kurze Erklärung zum DEBUG System:
Es gibt unterschiedlich starke Debug-Stufen:
Jede höher liegende aktiviert auch die weiter unten liegenden.
Prioritäten:
LIGHT_DEBUG | niedrig
DEBUG | medium
HEAVY_DEBUG | hoch
*/

#define LIGHT_DEBUG     //Empfohlen für normale Nutzung
//#define DEBUG           //Empfohlen für normale Entwicklung
//#define HEAVY_DEBUG     //Empfohlen für große Fehler bei denen man sehr verwirrt ist

#ifdef HEAVY_DEBUG
#define DEBUG
#endif

#ifdef DEBUG
#define LIGHT_DEBUG
#endif

#endif