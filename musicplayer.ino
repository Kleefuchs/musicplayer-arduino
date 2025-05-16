/*
Technologische Erfahrungen:

Ich (Samuel Brecht (Kleefuchs)) habe mich in diesem Projekt vor allem an die Limitationen des Arduinos angepasst und um diese herumprogrammiert.
Ich habe z. B. spezifischere Datentypen die sich auf 16 bit beschränken verwendet um Speicher zu Sparen. Zudem habe ich die Objektorientierte-Programmierung zurückgeschraubt weil diese nicht so effizient war.
Ich habe in diesem Projekt sehr starke Nutzung vom PROGMEM gemacht einem Speicher-Chip welcher 64 KB Daten halten kann, aber einem das Leben etwas schwerer macht und langsamer ist.

Programmierstil:

Ich habe keine automatische Formatierung verwendet, weil ich glaube, dass ich meinen Code besser organisieren kann als das Programm.
Man sieht zwar viele if Statement in meinem Code, aber ich habe versucht diese nicht besonders tief zu machen damit man nicht anfängt die geschweiften Klammern zu zählen, weil man sich orientieren muss.
Ich habe einige Code-Schnippsel in extra Funktionen abgespaltet um mir die Möglichkeit den Code mehrfach wieder zu verwenden zu geben und ihn generell besser zu organisieren.
Bezüglich meiner vielen Kommentare: Diese habe ich eingefügt damit ich meinen Mitschülern den Code besser erklären kann.
Ich bin mir ziemlich sicher, dass mein Code okayisch geschrieben ist weil ich habe die neusten Teile erst eine Woche nachdem ich ihn geschrieben habe kommentiert und viele Teile sind noch älter.

Steuerung:
Der linkeste Knopf ist da zum Starten und Pausieren.
Die beiden Knöpfe rechts davon sind da, um das vorherige/nächste Lied abzuspielen, wenn man aber beide gleichzeitig drückt, resettet man das Lied.
Die rechtesten Knöpfe sind da um das Tempo um 5 zu senken oder zu erhöhen (-5/+5) (Im Normalfall lässt sich in defines.hpp ändern), wenn man beide gleichzeitig drückt, resettet man nur das Tempo des Liedes.
*/


#include "Disco.hpp"

Disco disco;

void setup() {
  disco.setup();
}

void loop() {
  disco.loop();
}
