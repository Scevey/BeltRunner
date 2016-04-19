
#ifndef __APPLICATION_H_
#define __APPLICATION_H_
#pragma once

#include "RE\ReEngAppClass.h"
#include "Vehicle.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingSphereClass.h"
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

#endif //__APPLICATION_H_