#pragma once

class Actor {
protected:
	int duration;
	virtual void begin();
	void end();
public:
	void doYourThing();
	Actor(int duration);
	Actor() {};
};