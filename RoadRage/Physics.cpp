// Paul Lampanaro
#include "Physics.h"

void Physics::Init(void)
{
	maxVelocity = 1000.0f;
	maxAccel = 1000.0f; // janky right now
	friction = 0.95f; // for now, just using a percentage

	rotation = 0.0f;
	rotationVel = 0.0f;
	rotationAccel = 0.0f;

	deltaTime = 0.0f;

	position = vector3(0.0f, 0.0f, 0.0f); // forward point, affected by forces
	velocity = vector3(0.0f);
	accel = vector3(0.0f);

	// Bounding Object should be included in Physics class at a later point
	modelWorld = IDENTITY_M4;
}

void Physics::Swap(Physics& other)
{
	std::swap(maxVelocity, other.maxVelocity);
	std::swap(maxAccel, other.maxAccel);
	std::swap(friction, other.friction);

	std::swap(rotation, other.rotation);
	std::swap(rotationVel, other.rotationVel);
	std::swap(rotationAccel, other.rotationAccel);

	std::swap(deltaTime, other.deltaTime);

	std::swap(position, other.position);
	std::swap(velocity, other.velocity);
	std::swap(accel, other.accel);

	std::swap(modelWorld, other.modelWorld);
}

void Physics::Release()
{
}

// Big 3
Physics::Physics()
{
	maxVelocity = 50.0f; // 0-100 is the sweet spot 
	maxAccel = 0.5f; // 0 - 1.0 is the sweet spot
}

Physics::Physics(Physics const& other)
{
	maxVelocity = other.maxVelocity;
	maxAccel = other.maxAccel;
	friction = other.friction;

	rotation = other.rotation;
	rotationVel = other.rotationVel;
	rotationAccel = other.rotationAccel;

	deltaTime = other.deltaTime;

	position = other.position;
	velocity = other.velocity;
	accel = other.accel;

	modelWorld = other.modelWorld;
}

Physics& Physics::operator=(Physics const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Physics temp(other);
		Swap(temp);
	}
	return *this;
}

Physics::~Physics()
{
	Release();
}

void Physics::Update(double arg_deltaTime)
{
	// handle time
	deltaTime = static_cast<float>(arg_deltaTime);

	// add acceleration to velocity 
	velocity += accel;

	// use clamp instead of whatever else I was doing
	velocity = glm::clamp(velocity, -maxVelocity, maxVelocity);

	// add to position, based on deltaTime
	position += velocity * deltaTime;

	// apply friction to velocity
	velocity *= friction;

	// handle rotation
	HandleRotation();

	// handle quaternion rotation
	orientation = orientation * glm::angleAxis(0.1f, velocity);

	// update the model matrix
	modelWorld = glm::translate(position) * glm::rotate(rotation, vector3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(90.0f, vector3(1.0f, 0.0f, 0.0f)); // last rotation is temporary until we get new model

	// reset acceleration
	accel = vector3(0.0f);
}

void Physics::AddForce(vector3 arg_force)
{
	vector3 force = arg_force;

	// use clamp instead
	force = glm::clamp(force, -maxAccel, maxAccel);

	// add to acceleration
	accel += force;
}

matrix4 Physics::GetModelMatrix(void)
{
	return modelWorld;
}

vector3 Physics::GetPosition(void)
{
	return position;
}
void Physics::SetPosition(vector3 n_position)
{
	position = n_position;
}

void Physics::HandleRotation(void)
{}

void Physics::CheckBounds(vector3 posV) {
	if (posV.x >= 8.0f) {
		posV.x = 8;
	}
	if (posV.z >= 5.0f) {
		posV.z = 5;
	}
	if (posV.x <= -5.0f) {
		posV.x = -5;
	}
	if (posV.z <= -5.0f) {
		posV.z = -5;
	}
	SetPosition(posV);
}
