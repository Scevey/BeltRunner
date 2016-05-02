// Paul Lampanaro
// Vehicle Class will serve as parent for Truck & Car classes

#ifndef __VEHICLE_H_
#define __VEHICLE_H_

#include "RE\ReEng.h"
#include "MyBoundingClass.h"
#include "Physics.h"

// Vehicle Class
class Vehicle: public Physics
{
	bool isTurning;

public:
	bool getTurning() {
		return isTurning;
	}
	void setTurning(bool turning) {
		isTurning = turning;
	}
protected:
	virtual void HandleRotation(void);

};

#endif //__VEHICLE_H__
