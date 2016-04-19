
#ifndef __APPLICATION_H_
#define __APPLICATION_H_
#pragma once

#include "RE\ReEngAppClass.h"
#include "Vehicle.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingSphereClass.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Truck : public Vehicle
{
	//what different variables does the Truck need?

public:
	Truck(); //constructor
	~Truck(void); //destructor
};

#endif //__APPLICATION_H_