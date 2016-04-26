/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MyBoundingClass_H_
#define __MyBoundingClass_H_

#include "RE\ReEng.h"


//System Class
class MyBoundingClass
{
	vector3 m_v3Color = REWHITE;
	bool isVisible = true;
	float m_fRadius = 0.0f; //Radius of the Bounding Sphere
	vector3 m_v3Size = vector3(0.0f);
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Sphere Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Sphere Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Sphere Class
	std::vector<vector3> m_lVertexList;

public:
	/*
	 MyBoundingClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyBoundingClass(std::vector<vector3> a_lVectorList);
	/*
	 MyBoundingClass
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyBoundingClass(MyBoundingClass const& other);
	/*
	 operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyBoundingClass& operator=(MyBoundingClass const& other);
	/*
	 ~MyBoundingClass
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyBoundingClass(void);

	/*
	 Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
		other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyBoundingClass& other);

	/*
	 SetToWorldMatrix
	USAGE: Sets the Bounding Sphere into world coordinates
	ARGUMENTS:
		matrix4 a_m4ToWorld -> Model to World matrix
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	void SetColor(vector3 a_Color);
	void ToggleVisible();
	/*
	 GetCenter
	USAGE: Gets the Bounding Sphere's center in world coordinates
	ARGUMENTS: ---
	OUTPUT: vector3 -> Center's of the sphere in world coordinates
	*/
	vector3 GetCenter(void);
	vector3 GetColor(void);
	vector3 GetMax(void);
	vector3 GetMin(void);
	matrix4 GetModelMatrix(void);
	void UpdatePosition(vector3 a_v3Input);
	/*
	 GetRadius
	USAGE: Gets the Bounding Sphere's radius
	ARGUMENTS: ---
	OUTPUT: float -> radius of the Bounding Sphere
	*/
	float GetRadius(void);
	bool  GetVisibility();
	vector3 GetSize(void);
	
	/*
	 IsColliding
	USAGE: Asks if there is a collision with another Bounding sphere Object
	ARGUMENTS: 
		MyBoundingClass* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingClass* const a_pOther);
	
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

	void GenerateVertexList(std::vector<vector3> a_lVectorList);
	void CalculateMinMax(void);
};

#endif //__MyBoundingClass_H__