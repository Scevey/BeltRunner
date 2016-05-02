//Anthony Giallella
#include "Crate.h"

//big 3 + deconstuctor
Crate::Crate()
{
}

Crate::Crate(Crate const& other)
{
	speed = other.speed;
	m4Crate= other.m4Crate;
}

Crate & Crate::operator=(Crate const & other)
{
	if (this != &other)
	{
		Release();
		Crate temp(other);
		Swap(temp);
	}
	return *this;
}

Crate::~Crate()
{
	Release();
}


matrix4 Crate::Move(double deltatime)
{
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = deltatime; //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 

	float timeStart = 0.0f;
	float timeEnd = 3.0f;
	if (dTotalTime >= timeEnd) {
		dTotalTime = timeStart;
	}

	static vector3 v3Current;
	static vector3 v3start = vector3(0.0f, 0.0f, -5.0f); // values need changing , and preferably not hardcoded
	static vector3 v3end = vector3(0.0f, 0.0f, 5.0f);

	float fPercent = MapValue(static_cast<float>(dTotalTime), timeStart, timeEnd, 0.0f, 1.0f);

	v3Current = glm::lerp(v3start, v3end, fPercent);

	position = vector3(v3Current.x, position.y, v3Current.z);

	// rough bouncing motion, should change to full physics
	if (position.y <= 0)
	{
		velocity += vector3(0.0f, 5.0f, 0.0f);
	}

	// bounce the cube
	position += velocity * static_cast<float>(dDeltaTime);

	// reduce velocity
	velocity *= 0.95f;

	// gravity is one mean mutha'
	position -= vector3(0.0f, 1.0f, 0.0f) * static_cast<float>(dDeltaTime);

	// make it spin - not working?
	orientation = orientation * glm::angleAxis(1.0f, vector3(1.0f, 0.0f, 0.0f));

	m4Crate = glm::mat4_cast(orientation) * glm::translate(position) * glm::translate(vector3(0.0f, 0.5f, 0.0f));

	return m4Crate;
}


//utility functions
void Crate::Swap(Crate& other)
{
	std::swap(speed, other.speed);
	std::swap(m4Crate, other.m4Crate);
}

void Crate::Release()
{
}