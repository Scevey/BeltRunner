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
	m_lVertexList == std::vector<vector3>();
	
	GenerateVertexList(a_lVectorList);
	CalculateMinMax();

	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
	m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	m_v3Size.z = glm::distance(vector3(0.0f, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
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
vector3 MyBoundingClass::GetCenter(void) { return vector3(/*m_m4ToWorld * */vector4(m_v3Center, 1.0f)); } // need to ask about that\vector3 MyBOClass::GetCenterGlobal(void) { return m_v3CenterG; }
vector3 MyBoundingClass::GetHalfWidth(void) { return m_v3HalfWidth; }
vector3 MyBoundingClass::GetHalfWidthG(void) { return m_v3HalfWidthG; }
float MyBoundingClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingClass::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 MyBoundingClass::GetColor(void) { return m_v3Color; }
vector3 MyBoundingClass::GetSize(void) { return m_v3Size; }
vector3 MyBoundingClass::GetMin(void) { return vector3(/*m_m4ToWorld * */vector4(m_v3Min, 1.0f)); }
vector3 MyBoundingClass::GetMax(void) { return vector3(/*m_m4ToWorld * */vector4(m_v3Max, 1.0f)); }
vector3 MyBoundingClass::GetMinG(void) { return m_v3MinG; }
vector3 MyBoundingClass::GetMaxG(void) { return m_v3MaxG; }
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
	if (glm::distance(m_v3Center, a_pOther->m_v3Center) > (m_fRadius + a_pOther->m_fRadius))
		return false;
	CalculateMinMax();
	a_pOther->CalculateMinMax();
	bool bAreColliding = true;
	vector3 vMin1 = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 vMax1 = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
	vector3 vMin2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 vMax2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));
	if ((m_fRadius + a_pOther->m_fRadius) < glm::distance(m_v3CenterG, a_pOther->m_v3CenterG))
		return false;
	//Check for X
	if (vMax1.x < vMin2.x)
		bAreColliding = false;
	if (vMin1.x > vMax2.x)
		bAreColliding = false;

	//Check for Y
	if (vMax1.y < vMin2.y)
		bAreColliding = false;
	if (vMin1.y > vMax2.y)
		bAreColliding = false;

	//Check for Z
	if (vMax1.z < vMin2.z)
		bAreColliding = false;
	if (vMin1.z > vMax2.z)
		bAreColliding = false;

	if (bAreColliding)
	{
		SetColor(RERED);
		a_pOther->SetColor(RERED);
	}
	else
	{
		SetColor(REWHITE);
		a_pOther->SetColor(REWHITE);
	}

	return bAreColliding;

	
}

void MyBoundingClass::GenerateVertexList(std::vector<vector3> a_lVectorList) {

	uint nVertexCount = a_lVectorList.size();
	vector3 min;
	vector3 max;
	if (nVertexCount > 0)
	{
		min = a_lVectorList[0];
		max = a_lVectorList[0];
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		vector3 vec = a_lVectorList[i];
		if (vec.x > max.x)
			max.x = vec.x;
		else if (vec.x < min.x)
			min.x = vec.x;

		if (vec.y > max.y)
			max.y = vec.y;
		else if (vec.y < min.y)
			min.y = vec.y;

		if (vec.z > max.z)
			max.z = vec.z;
		else if (vec.z < min.z)
			min.z = vec.z;
	}
	//min = static_cast<vector3>(glm::inverse(m_m4ToWorld) * vector4(min, 1.0f));
	//max = static_cast<vector3>(glm::inverse(m_m4ToWorld) * vector4(max, 1.0f));

	m_lVertexList.push_back(vector3(min.x, min.y, min.z));
	m_lVertexList.push_back(vector3(min.x, min.y, max.z));
	m_lVertexList.push_back(vector3(min.x, max.y, min.z));
	m_lVertexList.push_back(vector3(min.x, max.y, max.z));
	m_lVertexList.push_back(vector3(max.x, min.y, min.z));
	m_lVertexList.push_back(vector3(max.x, min.y, max.z));
	m_lVertexList.push_back(vector3(max.x, max.y, min.z));
	m_lVertexList.push_back(vector3(max.x, max.y, max.z));
}

void MyBoundingClass::CalculateMinMax(void) {
	uint nVertexCount = m_lVertexList.size();
	vector3 min;
	vector3 max;
	if (nVertexCount > 0)
	{
		min = static_cast<vector3>(m_m4ToWorld * vector4(m_lVertexList[0], 1.0f));
		max = static_cast<vector3>(m_m4ToWorld * vector4(m_lVertexList[0], 1.0f));
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		vector3 vec = static_cast<vector3>(m_m4ToWorld * vector4(m_lVertexList[i], 1.0f));
		if (vec.x > max.x)
			max.x = vec.x;
		else if (vec.x < min.x)
			min.x = vec.x;

		if (vec.y > max.y)
			max.y = vec.y;
		else if (vec.y < min.y)
			min.y = vec.y;

		if (vec.z > max.z)
			max.z = vec.z;
		else if (vec.z < min.z)
			min.z = vec.z;
	}
	m_v3Min = static_cast<vector3>(glm::inverse(m_m4ToWorld) * vector4(min, 1.0f));
	m_v3Max = static_cast<vector3>(glm::inverse(m_m4ToWorld) * vector4(max, 1.0f));
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