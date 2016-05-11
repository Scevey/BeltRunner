#include "MyBOManager.h"
//  MyBOManager
MyBOManager* MyBOManager::m_pInstance = nullptr;
void MyBOManager::Init(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_nObjectCount = 0;
}
void MyBOManager::Release(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		if (m_lObject[nObject] != nullptr)
		{
			delete m_lObject[nObject];
			m_lObject[nObject] = nullptr;
		}
		m_llCollidingIndices[nObject].clear();
	}
	m_lObject.clear();
	m_llCollidingIndices.clear();
}
MyBOManager* MyBOManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyBOManager();
	}
	return m_pInstance;
}
void MyBOManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
MyBOManager::MyBOManager() { Init(); }
MyBOManager::MyBOManager(MyBOManager const& other) { }
MyBOManager& MyBOManager::operator=(MyBOManager const& other) { return *this; }
MyBOManager::~MyBOManager() { Release(); };
//Accessors
MyBoundingClass* MyBOManager::GetBoundingObject(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	return GetBoundingObject(nIndex);
}
MyBoundingClass* MyBOManager::GetBoundingObject(uint a_nIndex)
{
	if (a_nIndex < m_nObjectCount)
		return m_lObject[a_nIndex];

	return nullptr;
}
//--- Non Standard Singleton Methods
void MyBOManager::AddObject(String a_sName)
{
	std::vector<vector3> lVertex = m_pMeshMngr->GetVertexList(a_sName);
	AddObject(lVertex, a_sName);
	SetModelMatrix(m_pMeshMngr->GetModelMatrix(a_sName), a_sName);
}
void MyBOManager::AddObject(std::vector<vector3> a_lVertex, String a_sName)
{
	MyBoundingClass* pObject = new MyBoundingClass(a_lVertex);
	if (pObject != nullptr)
	{
		m_lObject.push_back(pObject);//Add the Object
		m_mapIndex[a_sName] = m_nObjectCount; //Add entry to the dictionary
	}
	m_nObjectCount = m_lObject.size();
	std::vector<int> lVector;
	m_llCollidingIndices.push_back(lVector);
}
void MyBOManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sIndex)
{
	//find the object
	int nIndex = this->GetIndex(a_sIndex);
	if (nIndex < 0) //if not found return
		return;

	m_lObject[nIndex]->SetModelMatrix(a_mModelMatrix);//set the matrix for the indexed Object
}
void MyBOManager::DisplaySphere(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplaySphere(nIndex, a_v3Color);
}
void MyBOManager::DisplaySphere(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplaySphere(v3Color);
	}
	else //all objects sent
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplaySphere(v3Color);
		}
	}
}
void MyBOManager::DisplayOriented(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplayOriented(nIndex, a_v3Color);
}
void MyBOManager::DisplayOriented(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplayOriented(v3Color);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			m_lObject[nObject]->DisplayOriented(v3Color);
		}
	}
}
void MyBOManager::DisplayReAlligned(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplayReAlligned(nIndex, a_v3Color);
}
void MyBOManager::DisplayReAlligned(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplayReAlligned(v3Color);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplayReAlligned(v3Color);
		}
	}
}
void MyBOManager::Update(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		m_llCollidingIndices[nObject].clear();
	}
	static MyOctant head = MyOctant(true);

	if (buildOctree)
	{
		head.CheckForObjs();
		buildOctree = false;
	}

	if (octreeVisible)
		head.Display();

	CheckCollisions(head);
}
void MyBOManager::CheckCollisions(MyOctant &octant)
{
	if (useOctree)
	{
		uint numChildren = octant.GetNumChildren();
		if (numChildren > 0)
		{
			for (int i = 0; i < numChildren; i++)
				CheckCollisions(octant.m_pChildren[i]);
		}
		else
		{
			std::vector<int> octantObjList = octant.GetObjIndexList();
			if (octantObjList.size() < 2)
				return;
			for (uint i = 0; i < octantObjList.size() - 1; i++)
			{
				for (uint c = i + 1; c < octantObjList.size(); c++)
				{
					int obj1 = octantObjList[i];
					int obj2 = octantObjList[c];
					if (m_lObject[obj1]->IsColliding(m_lObject[obj2]))
					{

						m_llCollidingIndices[obj1].push_back(obj2);
						m_llCollidingIndices[obj2].push_back(obj1);
					}
				}
			}
		}
	}
	else {
		for (uint i = 0; i < m_nObjectCount - 1; i++)
		{
			for (uint c = i + 1; c < m_nObjectCount; c++)
			{
				if (m_lObject[i]->IsColliding(m_lObject[c]))
				{

					m_llCollidingIndices[i].push_back(c);
					m_llCollidingIndices[c].push_back(i);
				}
			}
		}
	}
}
std::vector<int> MyBOManager::GetCollidingVector(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	if (nIndex < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(static_cast<uint>(nIndex));
}
std::vector<int> MyBOManager::GetCollidingVector(uint a_nIndex)
{
	if (a_nIndex >= m_nObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return m_llCollidingIndices[a_nIndex];
}
int MyBOManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_mapIndex.find(a_sIndex);
	//If not found return -1
	if (var == m_mapIndex.end())
		return -1;
	return var->second;//Get the index
}

int MyBOManager::GetObjectCount(void) { return m_nObjectCount; };
void MyBOManager::ToggleOctreeVisibility(void)
{
	octreeVisible = !octreeVisible;
}
void MyBOManager::ToggleOctree(void)
{
	useOctree = !useOctree;
}
void MyBOManager::BuildOctree(void)
{
	buildOctree = true;
}