/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MyBoundingClass_H_
#define __MyBoundingClass_H_

#include "RE\ReEng.h"

//enumerator
enum points {
	leftBottomBack,
	leftBottomFront,
	leftTopBack,
	leftTopFront,
	rightBottomBack,
	rightBottomFront,
	rightTopBack,
	rightTopFront
};

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
	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the Object Class
	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton
	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides
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
	//void UpdatePosition(vector3 a_v3Input);
	/*
	 GetRadius
	USAGE: Gets the Bounding Sphere's radius
	ARGUMENTS: ---
	OUTPUT: float -> radius of the Bounding Sphere
	*/
	float GetRadius(void);
	//bool  GetVisibility();
	vector3 GetSize(void);
	vector3 GetCenterGlobal(void);
	vector3 GetHalfWidth(void);
	vector3 GetMinG(void);
	vector3 GetMaxG(void);
	vector3 GetHalfWidthG(void);
	/*
	 IsColliding
	USAGE: Asks if there is a collision with another Bounding sphere Object
	ARGUMENTS: 
		MyBoundingClass* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingClass* const a_pOther);
	bool CheckAxisSAT(std::vector<vector3> a_lVertices, std::vector<vector3> a_lOtherVertices, vector3 axis);
	/*
	USAGE: Gets vertex list
	ARGUMENTS: ---
	OUTPUT: Vertex list
	*/
	std::vector<vector3> GetVertexList(void);
	void DisplaySphere(vector3 a_v3Color = REDEFAULT);
	void DisplayOriented(vector3 a_v3Color = REDEFAULT);
	void DisplayReAlligned(vector3 a_v3Color = REDEFAULT);
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