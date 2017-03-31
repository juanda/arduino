#include <Matriz.h>
#include "pitches.h"

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3

Matriz matriz = Matriz(6, 9, 5);

int leftThreshold  = 400;
int rightThreshold = 620;
int downThreshold  = 400;
int upThreshold    = 620;

int pinBuzzer      = 10;
float timeRefresh  = 1.5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // suena tono tirorii!
  playTirori();

  int count = 0;
  int loose = 0;
  while (!loose) {

    matriz.cleanMatrix();
    randomSeed(analogRead(0));

    int arrows[100];

    arrows[count] = getNextArrow();

    showAllArrows(arrows, count);
    matriz.cleanMatrix();

    count++;

    int i_count = 0;

    while (1) {
      int i_arrow = askForArrow();

      if (i_arrow != arrows[i_count]) { // perdiste!
        playOoooh();
        loose = 1;
      }

      playOk();
      i_count++;

      if (i_count == count) { // has pasado toda la secuencia, pasas al siguiente nivel
        playWin();
        break;
      }
    }
    if (count == 100) break; // Ñapita
  }

}

void playUp() {
  playNote(NOTE_C6, 8);
}

void playDown() {
  playNote(NOTE_E6, 8);
}

void playRight() {
  playNote(NOTE_G6, 8);
}

void playLeft() {
  playNote(NOTE_C7, 8);
}

void playWin() {
  int melody[] = {
    NOTE_C7, NOTE_G7, NOTE_G7, NOTE_A6, NOTE_G7, 0, NOTE_B6, NOTE_C7
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

  playMusic(melody, noteDurations, 8);

}

void playOk() {
  playNote(NOTE_G7, 8);
}

void playOoooh() {
  int melody[] = {
    NOTE_G7, NOTE_E7, NOTE_C7, NOTE_C6
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 4, 4, 2
  };

  playMusic(melody, noteDurations, 4);
}

void playTirori() {
  int melody[] = {
    NOTE_C7, NOTE_E7, NOTE_G7
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 4, 2
  };

  playMusic(melody, noteDurations, 3);
}

void playNote(int note, int duration) {
  int melody[] = {
    note
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    duration
  };

  playMusic(melody, noteDurations, 1);
}

void playMusic(int melody[], int noteDurations[], int numOfNotes) {
  for (int thisNote = 0; thisNote < numOfNotes; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(pinBuzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(pinBuzzer);
  }
}

int askForArrow() {
  int joyUpDown;
  int joyRightLeft;
  int result;
  while (1) {
    joyUpDown = analogRead(A5);
    joyRightLeft = analogRead(A4);
    if (joyUpDown > upThreshold) {
      result = UP;
      playUp();
      break;
    } else if (joyUpDown < downThreshold) {
      result = DOWN;
      playDown();
      break;
    } else if (joyRightLeft > rightThreshold) {
      result = RIGHT;
      playRight();
      break;
    } else if (joyRightLeft < leftThreshold) {
      result = LEFT;
      playLeft();
      break;
    }
    delay(500);
  }

  return result;
}

void showAllArrows(int arrows[], int count) {
  for (int i = 0; i <= count; i++) {
    matriz.cleanMatrix();
    delay(500);
    showArrow(arrows[i]);
  }
}

void showArrow(int a) {
  Serial.println(a);
  if (a == UP)    up();
  if (a == RIGHT) right();
  if (a == DOWN)  down();
  if (a == LEFT)  left();

}

int getNextArrow() {
  int a = random(0, 4);
  return a;
}

void controlArrow(int joyUpDown, int joyRightLeft) {
  if (joyUpDown > upThreshold) {
    up();
  } else if (joyUpDown < downThreshold) {
    down();
  } else if (joyRightLeft > rightThreshold) {
    right();
  } else if (joyRightLeft < leftThreshold) {
    left();
  }
}

void printPatron(int a[5][7]) {

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      if (a[i][j] == 0) {
        matriz.deletePixel(i + 1, j + 1);
      } else {
        matriz.newPixel(i + 1, j + 1);
      }
    }
  }
  matriz.printMatrix(timeRefresh);
}

void right() {
  int p[5][7] = {
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0}
  };

  printPatron(p);
}

void left() {

  int p[5][7] = {
    {0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0}
  };

  printPatron(p);
}

void up() {
  int p[5][7] = {
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0}
  };

  printPatron(p);
}

void down() {
  int p[5][7] = {
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0}
  };

  printPatron(p);
}
