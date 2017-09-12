#include "actor.h"
#include <iostream>
#include <Windows.h>

using namespace std;


Actor::Actor(int duration) : duration(duration) {}
	
	
	
void Actor::begin()
{
	cout << "I'm just a simple actor..." << endl;
}

void Actor::end()
{
	system("cls");


}

void Actor::doYourThing()
{
	begin();
	Sleep(duration);
	end();
}
