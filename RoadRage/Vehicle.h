/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_
#pragma once

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingSphereClass.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Vehicle
{
	vector3 position; //position of vehicle on screen
	int speed; //do we need speed?
	int velocity; //change to float or double?

	int getSpeed(); //get speed
	int getVelocity(); //get velocity
	
	int accelerate(int vel); //take velocity and accelerate, return adjusted velocity
	void move(int vel); //take velocity and move vehicle
	void brake(); //slow down car or stop it completely?

public:
	Vehicle(); //constructor
	~Vehicle(void); //destructor
};

#endif //__APPLICATION_H_