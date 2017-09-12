#include "shower.h"
#include "actor.h"
#include "beeper.h"
#include "annoyer.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
	srand(time(0)); //random maken van rand()

	int notes[12] = {523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988};
	string texts[3] = { "Hi!", "Hello!", "Hey!" };
	Actor *actors[10];

	actors[0] = new Actor((rand() % 50 * 100));

	for (int i = 1; i < 4; i++) {
		actors[i] = new Shower((rand() % 50 * 100), (texts[rand() %3]));
	}
	for (int i = 4; i < 7; i++) {
		actors[i] = new Beeper((rand() % 50 * 100), (notes[rand() % 12]));
	}
	for (int i = 7; i < 10; i++) {
		actors[i] = new Annoyer((rand() % 50 * 100), (texts[rand() % 3]), (notes[rand() % 12]));
	}


	for (int i = 0; i < 10; i++) {
		cout << "Actor: " << i << endl;
		actors[i]->doYourThing();
	}

	delete [] *actors;

	return 0;
}