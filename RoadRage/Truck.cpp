#include "Truck.h"

Truck::Truck(void) {
	
}
Truck::Truck(vector3 theTarget) {
	position = theTarget;
	target = theTarget;
	maxAccel = .3;
}
Truck::~Truck(void) {

}

void Truck::TruckUpdate(double deltaTime) {
	vector3 toTarget = position - target;
	if (glm::length(toTarget) < MINTARGETDISTANCE)
		target = vector3(((double)rand() / RAND_MAX)*(ROADWIDTH)+(-ROADWIDTH / 2), 0, target.z);
	AddForce(-toTarget);
	Update(deltaTime);
}
