#pragma once
#include "actor.h"
#include <string>

using namespace std;

class Shower: virtual public Actor {

public:
	Shower(int duration, string _text) : Actor(duration) { text = _text; }

protected:
	string text;
	virtual void begin();

};