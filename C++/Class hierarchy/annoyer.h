#pragma once
#include "shower.h"
#include "beeper.h"
#include <string>

using namespace std;

class Annoyer : public Shower, public Beeper {
	virtual void begin();
public:
	Annoyer(int _duration, string text, int freqenty) : Shower(0, text), Beeper(_duration, freqenty) { duration = 0; }

};
