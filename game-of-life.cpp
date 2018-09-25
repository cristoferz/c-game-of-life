


//   PARA COMPILAR

//   g++ SFML3.cpp -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

//==================================================================================


#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 80
#define SQUARE_SIZE 4

bool matrix[SIZE][SIZE] = {
	{ false, false, false, false, false },
	{ false, false, true, false, false },
	{ false, false, false, true, false },
	{ false, true, true, true, false}
}; 


//-----------------------------------------------------------------------
void Pause (int milliseconds) {
    struct timespec ts;
    ts.tv_sec = 0;//milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void initMatrix() {
//	return;

	
    srand(time(NULL));
    for(int i=0;i<SIZE;i++) {
        for (int j=0;j<SIZE;j++) {
            matrix[i][j] = (rand()%2)==1;
	}
    }
}

int countNeighbor(int matrix[SIZE][SIZE], int x, int y) {
    int result = 0;
    for (int i=x-1;i<=x+1;i++) {
	int xc = i;
	if (xc < 0)
		xc = SIZE-1;
	if (xc >= SIZE)
		xc = 0;
        for (int j=y-1;j<=y+1;j++) {
	    int yc = j;
            if (yc<0) 
	        yc = SIZE-1;
            if (yc >= SIZE)
		yc = 0;
	    if (xc==x && yc ==y)
		continue;
            if (matrix[yc][xc])
                result++;
        }
    }
    return result;
}

void evolve() {
   int oldMatrix[SIZE][SIZE];
   for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++) {
         oldMatrix[j][i] = matrix[j][i];
      }
   

   for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++) {
         int neighbors = countNeighbor(oldMatrix, i, j);
	 if (neighbors < 2 || neighbors > 3)
             matrix[j][i] = false;
	 if (neighbors == 3)
             matrix[j][i] = true;
      }
}


//-----------------------------------------------------------------------
int Gx = 0;

void show (sf::RenderWindow *window) {

   sf::RectangleShape rect (sf::Vector2f (SQUARE_SIZE, SQUARE_SIZE));

   for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++) {
	 if (matrix[i][j]) {
		 rect.setFillColor(sf::Color(255,255,255));
	 } else {
		 rect.setFillColor(sf::Color(0,0,0));
	 }
         rect.setPosition  (i*(SQUARE_SIZE+2), j*(SQUARE_SIZE+2));
         window->draw (rect);
      }
}


//-----------------------------------------------------------------------
int main() {

   sf::RenderWindow window(sf::VideoMode(500, 500), "Game of Life");
   initMatrix();

   while (window.isOpen()) {
      evolve();
      sf::Event event;

      while (window.pollEvent(event)) 
         if ( (event.type == sf::Event::Closed) ||
             ((event.type == sf::Event::KeyPressed) &&
              (event.key.code == sf::Keyboard::Escape)
             )
            )
            return 0;

      window.clear();
       
      show (&window);
       
      window.display();
      
      Gx = (Gx + 2) % 250;
      Pause (100);
      
   }

   return 0;
}
