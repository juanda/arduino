#include <Matriz.h>

Matriz matriz = Matriz(6, 9, 5);

int leftThreshold  = 400;
int rightThreshold = 620;
int downThreshold  = 400;
int upThreshold    = 620;

float timeRefresh  = 0.5;

void setup() {
  Serial.begin(9600);
}

void loop() {

  matriz.cleanMatrix();
  int joyUpDown = analogRead(A5);
  int joyRightLeft = analogRead(A4);

  Serial.println(joyUpDown);
  Serial.println(joyRightLeft);

  if (joyUpDown > upThreshold) {
    up();
  }else if (joyUpDown < downThreshold) {
    down();
  }else if (joyRightLeft > rightThreshold) {
    right();
  }else if (joyRightLeft < leftThreshold) {
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
