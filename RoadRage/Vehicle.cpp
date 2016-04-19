// Paul Lampanaro
#include "Vehicle.h"

void Vehicle::Init(void)
{
	length = 5.0f; // length from positionForward and positionRear
	maxVelocity = 3.0f;
	maxAccel = 1.0f;
	friction = 0.90f; // for now, just using a percentage

	deltaTime = 0.0f;
	totalTime = 0.0f;

	posForward = vector3(0.0f, 0.0f, 0.0f); // forward point, affected by forces
	posRear = vector3(0.0f, -length, 0.0f); // rear point, lerps to stay in line with positionForward
	axis = posForward - posRear; // vector formed by two position points
	velocity = vector3(0.0f);
	accel = vector3(0.0f);

	// Bounding Object should be included in Vehicle class at a later point
	modelWorld = IDENTITY_M4;
}

void Vehicle::Swap(Vehicle& other)
{
	std::swap(posForward, other.posForward);
	std::swap(posRear, other.posRear);
	std::swap(axis, other.axis);
	std::swap(velocity, other.velocity);
	std::swap(accel, other.accel);

	std::swap(deltaTime, other.deltaTime);
	std::swap(totalTime, other.totalTime);

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

	deltaTime = other.deltaTime;
	totalTime = other.totalTime;

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
	deltaTime = static_cast<float>(arg_deltaTime);
	totalTime += deltaTime;

	if (totalTime > swingTime)
	{
		totalTime -= swingTime;
	}

	// add acceleration to velocity 
	velocity += accel;

	// if velocity is greater than maxVelocity, limit
	if (velocity.length() >= maxVelocity)
	{
		float temp = velocity.length();
		// velocity = glm::normalize(velocity);
		velocity = vector3(velocity.x / temp, velocity.y / temp, velocity.z / temp);
		velocity *= maxVelocity;
		// velocity = vector3(velocity.x * maxVelocity, velocity.y * maxVelocity, velocity.z * maxVelocity);
	}

	// add to position, ignore y, based on deltaTime
	// posForward += vector3(velocity.x, 0.0f, velocity.y) * deltaTime; // I dunno what we should do with this right now
	posForward += velocity * deltaTime;

	// apply friction to velocity
	velocity *= friction;

	// reset acceleration
	accel = vector3(0.0f);

	// find ideal location of posRear, or the rear Axel
	vector3 rear = vector3(posForward.x, posForward.y - length, posForward.z);

	// if they are not equal, lerp the posRear over
	if (rear != posRear)
	{
		// swingTime = std::abs(rear.y - posRear.y);
		float lerpPercent = MapValue(totalTime, 0.0f, swingTime, 0.0f, 1.0f);
		posRear = glm::lerp(posRear, rear, lerpPercent);
	}

	// update the axis of the vehicle
	axis = posForward - posRear;
	vector3 straightAxis = posForward - rear;

	// angle between axis of vehicle and desired axis
	// float rotationAngle = glm::angle(axis, straightAxis);
	float rotationAngle = glm::orientedAngle(glm::normalize(axis), glm::normalize(straightAxis), posForward);

	// update the model matrix
	modelWorld = glm::rotate(rotationAngle, vector3(0.0f, 1.0f, 0.0f)) * glm::translate(posForward);
}

void Vehicle::AddForce(vector3 arg_force)
{
	vector3 force = arg_force;

	// limit force applied by maxAccel
	if (force.length() >= maxAccel)
	{
		float temp = force.length();
		force = vector3(force.x / temp, force.y / temp, force.z / temp);
		force *= maxAccel;
	}

	// add to acceleration
	accel += force * deltaTime;
}

matrix4 Vehicle::GetModelMatrix(void)
{
	return modelWorld;
}

/*
vector3 angleBetween(vector3 a, vector3 b, vector3 origin)
{
vector3 da = glm::normalize(a - origin);
vector3 db = glm::normalize(b - origin);
return glm::acos(glm::dot(da, db));
}
*/

