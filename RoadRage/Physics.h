#ifndef __PHYSICS_H_
#define __PHYSICS_H_

#include "RE\ReEng.h"
#include "MyBoundingClass.h"

// Physics Class
class Physics
{
protected:
	// Variables
	float maxVelocity = 1000.0f; // mad janky, setting at very high value for now
	float maxAccel = 1000.0f; // mad janky, setting at very high value for now
	float friction = 0.95f; // for now, just using a percentage

	// rotation variables
	float rotation = 0.0f;
	float rotationVel = 0.0f;
	float rotationAccel = 0.0f;

	// time variables
	float deltaTime = 0.0f;

	vector3 position = vector3(0.0f, 0.0f, 0.0f); // forward point, affected by forces
	vector3 velocity = vector3(0.0f);
	vector3 accel = vector3(0.0f);

	// Bounding Object should be included in Physics class at a later point
	matrix4 modelWorld = IDENTITY_M4;

public:
	// Big 3 Methods and Destructor

	/*
	Physics
	USAGE: Constructor
	ARGUMENT: Vector List from Mesh Manager
	OUTPUT: Class object
	*/
	Physics();

	/*
	Physics
	USAGE: Copy Constructor
	ARGUMENT: Class object to copy
	OUTPUT: class object instance
	*/
	Physics(Physics const& other);

	/*
	operator=
	USAGE: Copy Assignment Operator
	ARGUMENT: object -> object to swap contents from
	OUTPUT: ---
	*/
	Physics& operator=(Physics const& other);

	/*
	~Physics
	USAGE: Destructor
	ARGUMENT: ---
	OUTPUT: ---
	*/
	~Physics(void);

	/*
	Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(Physics& other);

	// Methods to be called by AppClass

	/*
	Update
	USAGE: Updates Physics's position based on velocity and delta time, updates bounding box
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
	void AddForce(vector3 arg_force);

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
	vector3 GetPosition(void);
	void SetPosition(vector3 arg_position);
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

protected:
	/*
	HandleRotation
	USAGE: Used within Physics update in order to update rotation
	ARGUMENT: ---
	OUTPUT: ---
	*/
	virtual void HandleRotation(void);
};

#endif //__PHYSICS_H_