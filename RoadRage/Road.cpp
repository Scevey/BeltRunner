//Justin John
#include "Road.h"

//big 3 + deconstuctor
Road::Road()
{
}

Road::Road(Road const& other)
{
	speed = other.speed;
	m4Segment1 = other.m4Segment1;
	m4Segment2 = other.m4Segment2;
}

Road & Road::operator=(Road const & other)
{
	if (this != &other)
	{
		Release();
		Road temp(other);
		Swap(temp);
	}
	return *this;
}

Road::~Road()
{
	Release();
}


matrix4 Road::Update1(double deltatime)
{
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = deltatime; //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 

	float timeStart = 0.0f;
	float timeEnd = 2.0f;
	//banana - need to make sure on the first pass, the timer resets in half the time
	if (hit1 == false) {
		if (dTotalTime >= timeEnd) { // timeEnd/2 never triggers hit1
			dTotalTime = timeStart;
		}
	}
	else
	{
		if (dTotalTime >= timeEnd) {
			dTotalTime = timeStart;
		}
	}


	float mapValStart = 0.0f;
	float mapValEnd = 1.0f;
	//static bool hit1 = false; //////////////////////////////////////////////////////////////////////////

	// values need changing , and preferably not hardcoded
	static vector3 initStart = vector3(0.0f, 0.0f, 0.0f);
	static vector3 reStart = vector3(0.0f, 0.0f, -5.0f);

	//static vector3 v3Current; //////////////////////////////////////////////////////////////////////////
	//static vector3 v3start;   //////////////////////////////////////////////////////////////////////////
	static vector3 v3end = vector3(0.0f, 0.0f, 5.0f);

	//static float fPercent; //////////////////////////////////////////////////////////////////////////
	if (hit1 == false) {
		v3start = initStart;
		fPercent = MapValue(static_cast<float>(dTotalTime), timeStart, timeEnd / 2, mapValStart, mapValEnd);
	}
	else
	{
		v3start = reStart;
		fPercent = MapValue(static_cast<float>(dTotalTime), timeStart, timeEnd, mapValStart, mapValEnd);
	}

	//float fPercent = MapValue(static_cast<float>(dTotalTime), timeStart, timeEnd, mapValStart, mapValEnd);


	v3Currentdebug = glm::lerp(v3start, v3end, fPercent);

	//banana
	//if (v3Currentdebug.z >= v3end.z) {
	if (fPercent >= 1.0f) {
		hit1 = true;
		//fPercent = 0;
	}


	//matrix4 m4Scale = glm::scale(vector3(0.25f)); //example
	m4Segment1 = glm::translate(v3Currentdebug);
	return m4Segment1;
	//segment1->SetModelMatrix(segment, "road");
}

matrix4 Road::Update2(double deltatime)
{
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = deltatime; //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 

	float timeStart = 0.0f;
	float timeEnd = 2.0f;
	if (dTotalTime >= timeEnd) {
		dTotalTime = timeStart;
	}

	static vector3 v3Current;
	static vector3 v3start = vector3(0.0f, 0.0f, -5.0f); // values need changing , and preferably not hardcoded
	static vector3 v3end = vector3(0.0f, 0.0f, 5.0f);

	float fPercent = MapValue(static_cast<float>(dTotalTime), timeStart, timeEnd, 0.0f, 1.0f);

	v3Current = glm::lerp(v3start, v3end, fPercent);

	m4Segment2 = glm::translate(v3Current);
	return m4Segment2;
}


//utility functions
void Road::Swap(Road& other)
{
	std::swap(speed, other.speed);
	std::swap(m4Segment1, other.m4Segment1);
	std::swap(m4Segment2, other.m4Segment2);
}

void Road::Release()
{
}