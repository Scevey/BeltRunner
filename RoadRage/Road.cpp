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
	//static float fPercent = 0.0f;
	//static bool hit1 = false;

	//Calculate delta and total times
	//static double dTotalTime = -1.0; //Total time of the simulation
	double dDeltaTime = deltatime; //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 

	float timeStart = 0.0f;
	float timeEnd = 2.0f;
	
	if (dTotalTime >= timeEnd) {
		dTotalTime -= timeEnd;
	}

	static double dTotalTimeINIT = 0.0;
	dTotalTimeINIT += dDeltaTime;
	if (dTotalTimeINIT >= 1.0f) {
		dTotalTimeINIT = timeStart;
		hit1 = true;
	}

	//static bool hit1 = false;

	// values need changing , and preferably not hardcoded
	static vector3 initStart = vector3(0.0f, 0.0f, 0.0f);
	static vector3 reStart = vector3(0.0f, 0.0f, -28.0f);

	static vector3 v3Current;
	static vector3 v3start;
	static vector3 v3end = vector3(0.0f, 0.0f, 28.0f);
	//static float fPercent;
	
	if (hit1)
	{
		v3start = reStart;
		fPercent = MapValue(static_cast<float>(dTotalTime), 0.0f, 2.0f, 0.0f, 1.0f);
	}
	else 
	{
		v3start = initStart;
		fPercent = dTotalTimeINIT;
	}

	//v3Currentdebug = glm::lerp(v3start, v3end, fPercent);
	v3Current = glm::lerp(v3start, v3end, fPercent);

	/*
	//static float fPercent; //////////////////////////////////////////////////////////////////////////
	if (hit1 == false) {
		v3start = initStart;
		fPercent = MapValue(static_cast<float>(dTotalTimeINIT), 0.0f, 1.0f, 0.0f, 1.0f);
		v3Currentdebug = glm::lerp(initStart, v3end, fPercent);
	}
	else
	{
		v3start = reStart;
		fPercent = MapValue(static_cast<float>(dTotalTime), 0.0f, 2.0f, 0.0f, 1.0f);
		v3Currentdebug = glm::lerp(reStart, v3end, fPercent);
	}*/

	//float fPercent = MapValue(static_cast<float>(dTotalTime), timeStart, timeEnd, mapValStart, mapValEnd);


	//v3Currentdebug = glm::lerp(v3start, v3end, fPercent);

	//banana
	//if (v3Current.z >= v3end.z) {
	//if (v3Current == v3end) {
	
	/*
	//if (fPercent >= 0.95f) {
	if (dTotalTime >= 2.0f) {
		hit1 = true;
		//fPercent = 0;
	}
	
	if (fPercent >= 1.0f) {
		dTotalTime = timeStart;
		hit1 = true;
	}*/

	m4Segment1 = glm::translate(v3Current) * glm::translate(0.0f,-0.05f,0.0f);
	return m4Segment1;
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
		dTotalTime -= timeEnd;
	}

	static vector3 v3Current;
	static vector3 v3start = vector3(0.0f, 0.0f, -28.0f); // values need changing , and preferably not hardcoded
	static vector3 v3end = vector3(0.0f, 0.0f, 28.0f);

	float fPercent2 = MapValue(static_cast<float>(dTotalTime), timeStart, timeEnd, 0.0f, 1.0f);

	v3Current = glm::lerp(v3start, v3end, fPercent2);

	m4Segment2 = glm::translate(v3Current) * glm::translate(0.0f, -0.05f, 0.0f);
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