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

	m4Crate = glm::translate(v3Current);
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