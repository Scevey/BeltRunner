#pragma once
// Anthony Giallella
// Crate class - make the Crate

#ifndef __CRATE_H_
#define __CRATE_H_

#include "RE\ReEng.h"
#include "MyBoundingClass.h"

class Crate
{

	//variables, get em while they're hot
	float speed = 5.0f; // the speed at which the Crate moves backwards

	// use this to make it bounce
	vector3 position = vector3(0.0f, 0.0f, -5.0f);
	vector3 velocity = vector3(0.0f, 0.0f, 0.0f);
	vector3 accel = vector3(0.0f, 0.0f, 0.0f);

	glm::quat orientation = glm::angleAxis(0.0f,vector3(1.0f,0.0f,0.0f));

	//these variables hold the tranformations of the two segments of Crate that are loaded in
	matrix4 m4Crate = IDENTITY_M4;

public:
	//big 3
	//constructor - contructs Crates, takes in Crate models maybe?
	Crate();

	//copy constuctor - takes in one class object and spits out another just like it
	Crate(Crate const& other);

	//copy assignment operator - object -> object to swap contents from
	Crate& operator=(Crate const& other);

	//destructor - destroys an object
	~Crate(void);

	/* Changes object contents for other object's
	other -> object to swap content from */
	void Swap(Crate& other);

	matrix4 Crate::Move(double time);
private:
	void Release(void);


};

#endif //__Crate_H__

