
#ifndef __TRUCK_H_
#define __TRUCK_H_

#include "RE\ReEngAppClass.h"
#include "Vehicle.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingClass.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Truck : public Vehicle
{
	//what different variables does the Truck need?

public:
	Truck(); //constructor
	~Truck(void); //destructor
};

#endif //__TRUCK_H_