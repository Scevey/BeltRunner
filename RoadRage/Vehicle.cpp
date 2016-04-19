// Paul Lampanaro
#include "Vehicle.h"

void Vehicle::Init(void)
{
	posForward = vector3(0.0f);
	posRear = vector3(0.0f);
	axis = vector3(0.0f);
	velocity = vector3(0.0f);
	accel = vector3(0.0f);

	modelWorld = IDENTITY_M4;

	maxVelocity = 0.0f;
	maxAccel = 0.0f;
	friction = 0.0f;
}

void Vehicle::Swap(Vehicle& other)
{ 
	std::swap(posForward, other.posForward);
	std::swap(posRear, other.posRear);
	std::swap(axis, other.axis);
	std::swap(velocity, other.velocity);
	std::swap(accel, other.accel);

	std::swap(modelWorld, other.modelWorld);

	std::swap(maxVelocity, other.maxVelocity);
	std::swap(maxAccel, other.maxAccel);
	std::swap(friction, other.friction);
}

void Vehicle::Release()
{
}

// Big 3
Vehicle::Vehicle()
{	
}

Vehicle::Vehicle(Vehicle const& other)
{
	posForward = other.posForward;
	posRear = other.posRear;
	axis = other.axis;
	velocity = other.velocity;
	accel = other.accel;

	modelWorld = other.modelWorld;

	maxVelocity = other.maxVelocity;
	maxAccel = other.maxAccel;
	friction = other.friction;
}

Vehicle& Vehicle::operator=(Vehicle const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Vehicle temp(other);
		Swap(temp);
	}
	return *this;
}

Vehicle::~Vehicle()
{
	Release();
}

void Vehicle::Update(double arg_deltaTime)
{
	// handle time
	float swingTime = 5.0f; // figure out a way to set this once, hardcoded for now
	float deltaTime = static_cast<float>(arg_deltaTime);
	static float totalTime = 0.0f;
	totalTime += deltaTime;

	if (totalTime > swingTime)
	{
		totalTime = 0.0f;
	}

	// add acceleration to velocity 
	velocity += accel;
	
	// if velocity is greater than maxVelocity, limit
	if (glm::length(velocity) >= maxVelocity)
	{
		velocity = glm::normalize(velocity);
		velocity *= maxVelocity;
	}

	// add to position, ignore y, based on deltaTime
	posForward += vector3(velocity.x, 0.0f, velocity.y) * deltaTime;

	// apply friction to velocity
	velocity *= friction;

	// reset acceleration
	accel = vector3(0.0f);

	// find idea location of posRear, or the rear Axel
	vector3 rear = vector3(posForward.x, posForward.y - length, posForward.z);

	// if they are not equal, lerp the posRear over
	if (rear != posRear)
	{
		// swingTime = std::abs(rear.y - posRear.y);
		float lerpPercent = MapValue(deltaTime, 0.0f, swingTime, 0.0f, 1.0f);
		posRear = glm::lerp(posRear, rear, lerpPercent);
	}

	// update the axis of the vehicle
	axis = posForward - posRear;
	vector3 straightAxis = posForward - rear;

	// angle between axis of vehicle and desired axis
	float rotationAngle = glm::angle(glm::normalize(axis), glm::normalize(straightAxis));

	// update the model matrix
	modelWorld =  glm::rotate(rotationAngle, vector3(0.0f, 1.0f, 0.0f)) * glm::translate(posForward);
}

void Vehicle::AddForce(vector3 arg_force, double arg_deltaTime)
{
	float deltaTime = static_cast<float>(arg_deltaTime);

	vector3 force = arg_force;

	// limit force applied by maxAccel
	if (glm::length(force) >= maxAccel)
	{
		force = glm::normalize(force);
		force *= maxAccel;
	}

	// add to acceleration
	accel += force * deltaTime;
}

matrix4 Vehicle::GetModelMatrix(void)
{
	return modelWorld;
}

