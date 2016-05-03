#include "MyBoundingClass.h"
//  MyBoundingClass
void MyBoundingClass::Init(void)
{
	m_fRadius = 0.0f;
	m_m4ToWorld = IDENTITY_M4;
	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);
	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
}
void MyBoundingClass::Swap(MyBoundingClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}
void MyBoundingClass::Release(void)
{

}
//The big 3
MyBoundingClass::MyBoundingClass(std::vector<vector3> a_lVectorList)
{
	Init();
	
	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list, also build axes list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		// build min and max points
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;

	/*
	m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	m_v3Size.z = glm::distance(vector3(0.0f, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
	*/

	//list of verteces in model space, probabaklty for bounding box, also probably
	m_lVertexList = std::vector<vector3>(8);
	m_lVertexList[leftBottomBack] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z); //left bottom back
	m_lVertexList[leftBottomFront] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z); //left bottom front
	m_lVertexList[leftTopBack] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z); //left top back
	m_lVertexList[leftTopFront] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z); //left top front
	m_lVertexList[rightBottomBack] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z); //right bottom back
	m_lVertexList[rightBottomFront] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z); //right bottom front
	m_lVertexList[rightTopBack] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z); //right top back
	m_lVertexList[rightTopFront] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z); //right top front
}
MyBoundingClass::MyBoundingClass(MyBoundingClass const& other)
{

	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;

	m_pMeshMngr = other.m_pMeshMngr;
}
MyBoundingClass& MyBoundingClass::operator=(MyBoundingClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBoundingClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingClass::~MyBoundingClass() { Release(); };

//Accessors
vector3 MyBoundingClass::GetCenter(void) { return m_v3Center; } // need to ask about that\vector3 MyBOClass::GetCenterGlobal(void) { return m_v3CenterG; }
vector3 MyBoundingClass::GetHalfWidth(void) { return m_v3HalfWidth; }
vector3 MyBoundingClass::GetHalfWidthG(void) { return m_v3HalfWidthG; }
float MyBoundingClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingClass::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 MyBoundingClass::GetColor(void) { return m_v3Color; }
vector3 MyBoundingClass::GetSize(void) { return m_v3Size; }
vector3 MyBoundingClass::GetMin(void) { return m_v3Min; }
vector3 MyBoundingClass::GetMax(void) { return m_v3Max; }
vector3 MyBoundingClass::GetMinG(void) { return m_v3MinG; }
vector3 MyBoundingClass::GetMaxG(void) { return m_v3MaxG; }
std::vector<vector3> MyBoundingClass::GetVertexList(void) { return m_lVertexList; }

// Modifiers
void MyBoundingClass::SetModelMatrix(matrix4 a_m4ToWorld) {
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the Object
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinG.x = v3Corner[nVertex].x;
		else if (m_v3MaxG.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = v3Corner[nVertex].x;

		if (m_v3MinG.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinG.y = v3Corner[nVertex].y;
		else if (m_v3MaxG.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = v3Corner[nVertex].y;

		if (m_v3MinG.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinG.z = v3Corner[nVertex].z;
		else if (m_v3MaxG.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = v3Corner[nVertex].z;
	}
	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterG, m_v3MaxG);
}
void MyBoundingClass::SetColor(vector3 a_color) { m_v3Color = a_color; }

//--- Non Standard Singleton Methods
bool MyBoundingClass::IsColliding(MyBoundingClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 vMin1 = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 vMax1 = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 vMin2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 vMax2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	vector3 v3Center = vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));

	vector3 v3CenterO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Center, 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	//first check the bounding sphere, if that is not colliding we can guarantee that there are no collision
	if ((m_fRadius + a_pOther->m_fRadius) < glm::distance(m_v3CenterG, a_pOther->m_v3CenterG))
		return false;

	bool bAreColliding = true;

	//Check for X
	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		bAreColliding = false;
	if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		bAreColliding = false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		bAreColliding = false;
	if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		bAreColliding = false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		bAreColliding = false;
	if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		bAreColliding = false;

	// SAT
	std::vector<vector3> object1 = m_lVertexList;
	std::vector<vector3> object2 = a_pOther->GetVertexList();

	for (uint i = 0; i < 8; i++)
	{
		object1[i] = vector3(m_m4ToWorld * vector4(object1[i], 1.0f));
		object2[i] = vector3(a_pOther->m_m4ToWorld * vector4(object2[i], 1.0f));
	}

	if (bAreColliding) {
		vector3 obj1NormX = object1[leftBottomBack] - object1[rightBottomBack];
		if (!CheckAxisSAT(object1, object2, obj1NormX)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 obj1NormY = object1[leftBottomBack] - object1[leftTopBack];
		if (!CheckAxisSAT(object1, object2, obj1NormY)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 obj1NormZ = object1[leftBottomBack] - object1[leftBottomFront];
		if (!CheckAxisSAT(object1, object2, obj1NormZ)) {
			bAreColliding = false;
			return bAreColliding;
		}


		vector3 obj2NormX = object2[leftBottomBack] - object2[rightBottomBack];
		if (!CheckAxisSAT(object1, object2, obj2NormX)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 obj2NormY = object2[leftBottomBack] - object2[leftTopBack];
		if (!CheckAxisSAT(object1, object2, obj2NormY)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 obj2NormZ = object2[leftBottomBack] - object2[leftBottomFront];
		if (!CheckAxisSAT(object1, object2, obj2NormZ)) {
			bAreColliding = false;
			return bAreColliding;
		}


		vector3 cross1x1 = glm::cross(obj1NormX, obj2NormX);
		if (!CheckAxisSAT(object1, object2, cross1x1)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 cross1x2 = glm::cross(obj1NormX, obj2NormY);
		if (!CheckAxisSAT(object1, object2, cross1x2)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 cross1x3 = glm::cross(obj1NormX, obj2NormZ);
		if (!CheckAxisSAT(object1, object2, cross1x3)) {
			bAreColliding = false;
			return bAreColliding;
		}


		vector3 cross2x1 = glm::cross(obj1NormY, obj2NormX);
		if (!CheckAxisSAT(object1, object2, cross2x1)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 cross2x2 = glm::cross(obj1NormY, obj2NormY);
		if (!CheckAxisSAT(object1, object2, cross2x2)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 cross2x3 = glm::cross(obj1NormY, obj2NormZ);
		if (!CheckAxisSAT(object1, object2, cross2x3)) {
			bAreColliding = false;
			return bAreColliding;
		}


		vector3 cross3x1 = glm::cross(obj1NormZ, obj2NormX);
		if (!CheckAxisSAT(object1, object2, cross3x1)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 cross3x2 = glm::cross(obj1NormZ, obj2NormY);
		if (!CheckAxisSAT(object1, object2, cross3x2)) {
			bAreColliding = false;
			return bAreColliding;
		}

		vector3 cross3x3 = glm::cross(obj1NormZ, obj2NormZ);
		if (!CheckAxisSAT(object1, object2, cross3x3)) {
			bAreColliding = false;
			return bAreColliding;
		}
	}

	return bAreColliding;
}

bool MyBoundingClass::CheckAxisSAT(std::vector<vector3> a_lVertices, std::vector<vector3> a_lOtherVertices, vector3 axis)
{
	float max1;
	float min1;
	float max2;
	float min2;

	//project each vec3 in the first object onto the axis, saving min and max values
	for (int c = 0; c < a_lVertices.size(); c++) {
		vector3 vert = a_lVertices[c];
		float projectedVert = glm::dot(vert, axis);// / glm::length(vert);
		if (c == 0 || projectedVert > max1)
			max1 = projectedVert;
		if (c == 0 || projectedVert < min1)
			min1 = projectedVert;
	}

	//do the same for the second object
	for (int c = 0; c < a_lOtherVertices.size(); c++) {
		vector3 vert = a_lOtherVertices[c];
		float projectedVert = glm::dot(vert, axis);// / glm::length(vert);
		if (c == 0 || projectedVert > max2)
			max2 = projectedVert;
		if (c == 0 || projectedVert < min2)
			min2 = projectedVert;
	}

	//if the ranges overlap, return true
	return !(max1 < min2 || max2 < min1);
}

void MyBoundingClass::DisplaySphere(vector3 a_v3Color)
{
	m_pMeshMngr->AddSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(vector3(m_fRadius * 2.0f)), a_v3Color, WIRE);
}
void MyBoundingClass::DisplayOriented(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}
void MyBoundingClass::DisplayReAlligned(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterG) *
		glm::scale(m_v3HalfWidthG * 2.0f), a_v3Color, WIRE);
}