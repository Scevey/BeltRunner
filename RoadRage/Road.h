#pragma once
// Justin John
// Road class - make the road

#ifndef __ROAD_H_
#define __ROAD_H_

#include "RE\ReEng.h"
#include "MyBoundingClass.h"

class Road
{

	//variables, get em while they're hot
	float speed = 5.0f; // the speed at which the road moves backwards

	/*
	//banana
	vector3 v3Currentdebug;
	
	vector3 v3start;*/
	float fPercent;
	double dTotalTime = -1.0;
	
	bool hit1 = false;

	//these variables hold the tranformations of the two segments of road that are loaded in
	matrix4 m4Segment1 = IDENTITY_M4;
	matrix4 m4Segment2 = IDENTITY_M4;

public:
	//big 3
	//constructor - contructs roads, takes in road models maybe?
	Road();

	//copy constuctor - takes in one class object and spits out another just like it
	Road(Road const& other);

	//copy assignment operator - object -> object to swap contents from
	Road& operator=(Road const& other);

	//destructor - destroys an object
	~Road(void);

	/* Changes object contents for other object's
	other -> object to swap content from */
	void Swap(Road& other);

	matrix4 Road::Update1(double time);
	matrix4 Road::Update2(double time);

	/*
	//banana
	float getCurrentDebug() {
		return v3Currentdebug.z;
	}
	
	float getStartDebug() {
		return v3start.z;
	}*/
	float getfPercDebug() {
		return fPercent;
	}
	bool getHitDebug() {
		return hit1;
	}
	float getTimeEndDebug() {
		return dTotalTime;
	}


private:
	void Release(void);


};

#endif //__ROAD_H__

