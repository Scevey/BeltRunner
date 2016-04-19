<<<<<<< HEAD
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
=======
// Paul Lampanaro
// Vehicle Class will serve as parent for Truck & Car classes

#ifndef __VEHICLE_H_
#define __VEHICLE_H_

#include "RE\ReEng.h"
#include "MyBoundingSphereClass.h"

// Vehicle Class
class Vehicle
{
	// Variables
	float length = 5.0f; // length from positionForward and positionRear
	float maxVelocity = 3.0f;
	float maxAccel = 1.0f;
	float friction = 0.90f; // for now, just using a percentage

	vector3 posForward = vector3(0.0f, 0.0f, 0.0f); // forward point, affected by forces
	vector3 posRear = vector3(0.0f, -length, 0.0f); // rear point, lerps to stay in line with positionForward
	vector3 axis = posForward - posRear; // vector formed by two position points
	vector3 velocity = vector3(0.0f);
	vector3 accel = vector3(0.0f);

	// Bounding Object should be included in Vehicle class at a later point
	matrix4 modelWorld = IDENTITY_M4;

public:
	// Big 3 Methods and Destructor

	/*
	Vehicle
	USAGE: Constructor
	ARGUMENT: Vector List from Mesh Manager
	OUTPUT: Class object
	*/
	Vehicle();

	/*
	Vehicle
	USAGE: Copy Constructor
	ARGUMENT: Class object to copy
	OUTPUT: class object instance
	*/
	Vehicle(Vehicle const& other);

	/*
	operator=
	USAGE: Copy Assignment Operator
	ARGUMENT: object -> object to swap contents from
	OUTPUT: ---
	*/
	Vehicle& operator=(Vehicle const& other);

	/*
	~Vehicle
	USAGE: Destructor
	ARGUMENT: ---
	OUTPUT: ---
	*/
	~Vehicle(void);

	/*
	Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(Vehicle& other);

	// Methods to be called by AppClass

	/*
	Update
	USAGE: Updates vehicle's position based on velocity and delta time, updates bounding box
	ARGUMENT: Delta time
	OUTPUT: ---
	*/
	void Update(double arg_deltaTime);

	/*
	AddForce
	USAGE: Adds force to current velocity based on deltaTime, capped by maxAccel
	ARGUMENT: Vector of force, deltaTime
	OUTPUT: ---
	*/
	void AddForce(vector3 arg_force, double arg_deltaTime);

	/* Miscellaneous methods, will define later

	vector3 GetPosition(void);
	void SetModelMatrix(matrix4 arg_matrixWorld);
	void SetVelocity(float arg_maxVelocity);
	void SetDirection(vector3 arg_direction);
	void SetPosition(vector3 arg_position);
	void SetMaxAccel(float arg_maxAccel);
	void SetMaxVelocity(float arg_maxVelocity);
	void SetFriction(float arg_friction);

	*/
	matrix4 GetModelMatrix(void);

private:
	/*
	Release
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	Init
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__VEHICLE_H__
>>>>>>> origin/master
