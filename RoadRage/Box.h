#pragma once
#ifndef __APPLICATION_H_
#define __APPLICATION_H_
#pragma once

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingSphereClass.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Box
{
	vector3 position; //position of vehicle on screen
	int speed; //do we need speed?
	int velocity; //change to float or double?

	int getSpeed(); //get speed
	int getVelocity(); //get velocity

	// method to load the box
	void loadBox()
	{

	}

public:
	Box(); //constructor
	~Box(void); //destructor
};

#endif //__APPLICATION_H_