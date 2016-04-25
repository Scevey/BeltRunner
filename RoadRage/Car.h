
#ifndef __CAR_H_
#define __CAR_H_

#include "RE\ReEngAppClass.h"
#include "Vehicle.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingClass.h"
#include <iostream>

using namespace std;
using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Car : public Vehicle
{
	int lane;
	string playerName; //do we need this?

public:
	Car(); //constructor
	~Car(void); //destructor
};

#endif //__CAR_H_