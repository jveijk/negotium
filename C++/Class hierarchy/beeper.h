#pragma once
#include "actor.h"

class Beeper : virtual public Actor {
protected:
	int freq;
	int soundDuration;
	virtual void begin();
public:
	Beeper(int duration, int frequenty) : Actor(0) {
		freq = frequenty;
		soundDuration = duration;
	}
};