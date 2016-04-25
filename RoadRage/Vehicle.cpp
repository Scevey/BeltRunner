// Paul Lampanaro
#include "Vehicle.h"

void Vehicle::Init(void)
{
	length = 5.0f; // length from positionForward and positionRear
	maxVelocity = 1000.0f;
	maxAccel = 1000.0f;
	friction = 0.95f; // for now, just using a percentage
	rotation = 0.0f;

	deltaTime = 0.0f;

	posForward = vector3(0.0f, 0.0f, 0.0f); // forward point, affected by forces
	velocity = vector3(0.0f);
	accel = vector3(0.0f);

	// Bounding Object should be included in Vehicle class at a later point
	modelWorld = IDENTITY_M4;
}

void Vehicle::Swap(Vehicle& other)
{
	std::swap(posForward, other.posForward);
	std::swap(velocity, other.velocity);
	std::swap(accel, other.accel);
	std::swap(rotation, other.rotation);

	std::swap(deltaTime, other.deltaTime);

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
	velocity = other.velocity;
	accel = other.accel;
	rotation = other.rotation;

	deltaTime = other.deltaTime;

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
	deltaTime = static_cast<float>(arg_deltaTime);

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

	// add to position, based on deltaTime
	posForward += velocity * deltaTime;

	// apply friction to velocity
	velocity *= friction;

	// ROTATION

	// apply rotation acceleration to velocity
	rotationAccel = -(velocity.x * 0.01f);

	// if not turning, realign
	if (accel == vector3(0.0f))
	{
		if (rotation < 0.0f)
		{
			rotationVel += 0.2f; // right now hardcoded
		}
		else if(rotation > 0.0f)
		{
			rotationVel -= 0.2f; // right now hardcoded
		}
	}
	
	rotationVel += rotationAccel;

	// apply rotation velocity to rotation angle
	rotation += rotationVel;

	// do this just in case
	rotation = fmod(rotation, 360.0f);

	// apply friction
	rotationVel *= friction;

	// update the model matrix
	modelWorld = glm::translate(posForward) * glm::rotate(rotation, vector3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(90.0f, vector3(1.0f, 0.0f, 0.0f)); // last rotation is temporary until we get new model

	// reset acceleration
	accel = vector3(0.0f);
	rotationAccel = 0.0f;
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
	accel += force;
}

matrix4 Vehicle::GetModelMatrix(void)
{
	return modelWorld;
}

vector3 Vehicle::GetPosition(void)
{
	return posForward;
}
