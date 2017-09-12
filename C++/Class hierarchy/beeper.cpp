#include "beeper.h"
#include <windows.h> 
#include <iostream>

using namespace std;

void Beeper::begin(){
	cout << "*beep!*" << endl;
	Beep(freq, soundDuration);
}
