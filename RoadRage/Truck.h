
#ifndef __TRUCK_H_
#define __TRUCK_H_

#define MINTARGETDISTANCE .1
#define ROADWIDTH 10

#include "RE\ReEngAppClass.h"
#include "Vehicle.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingClass.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class Truck : public Vehicle
{
	//what different variables does the Truck need?
	//VARIABLES
	vector3 target;

public:
	Truck(); //constructor
	Truck(vector3 theTarget);
	~Truck(void); //destructor
	void TruckUpdate(double deltaTime);
};

#endif //__TRUCK_H_