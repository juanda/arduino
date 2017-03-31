#include <Matriz.h>

Matriz matriz = Matriz(6, 9, 5);

int pinLeft = 2;
int pinRight = 3;
float timeRefresh = 0.5;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);

}

void loop() {
  
  matriz.cleanMatrix();
  int _left = digitalRead(pinLeft);
  int _right = digitalRead(pinRight);
  
  up();
  right();
  down();
  left();
 
}

void printPatron(int a[5][7]) {

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {      
      if (a[i][j] == 0) {
        matriz.deletePixel(i+1, j+1);
      } else {
        matriz.newPixel(i+1, j+1);
      }
    }
  }
  matriz.printMatrix(timeRefresh);
}

void right() {
   int p[5][7] = {
    {0,0,0,0,1,0,0},
    {0,0,0,0,0,1,0},
    {1,1,1,1,1,1,1},
    {0,0,0,0,0,1,0},
    {0,0,0,0,1,0,0}
  };

  printPatron(p);
}

void left() {

  int p[5][7] = {
    {0,0,1,0,0,0,0},
    {0,1,0,0,0,0,0},
    {1,1,1,1,1,1,1},
    {0,1,0,0,0,0,0},
    {0,0,1,0,0,0,0}
  };

  printPatron(p);
}

void up() {
  int p[5][7] = {
    {0,0,0,1,0,0,0},
    {0,0,1,1,1,0,0},
    {0,1,0,1,0,1,0},
    {0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0}
  };

  printPatron(p);
}

void down() {
  int p[5][7] = {
    {0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0},
    {0,1,0,1,0,1,0},
    {0,0,1,1,1,0,0},
    {0,0,0,1,0,0,0}
  };

  printPatron(p);
}
