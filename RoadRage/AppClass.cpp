#include "AppClass.h"
#include "Vehicle.h"

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingSphereClass example"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3OP = vector3(-2.5f, 0.0f, 0.0f);
	m_v3OT = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve");
	m_BSCPlayer = new MyBoundingSphereClass(vertexList);

	m_pPlayer = new PrimitiveClass();
	m_fRadiusP = m_BSCPlayer->GetRadius();
	m_v3CenterP = m_BSCPlayer->GetCenter();
	m_pPlayer->GenerateSphere(m_fRadiusP, 10, REGREEN);


	//Creeper
	vertexList = m_pMeshMngr->GetVertexList("Creeper");
	m_BSCTruck = new MyBoundingSphereClass(vertexList);
	m_fRadiusT = m_BSCTruck->GetRadius();
	m_v3CenterT = m_BSCTruck->GetCenter();
	m_pTruck = new PrimitiveClass();
	m_pTruck->GenerateSphere(m_fRadiusT, 10, REGREEN);

	m_pCameraMngr->SetPositionTargetAndView(vector3(0,10,10),vector3(0,0,0),vector3(0,1,0));
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3OP) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3OT), "Creeper");
	m_BSCPlayer->SetModelMatrix(glm::translate(m_v3OP) * ToMatrix4(m_qArcBall));
	m_BSCTruck->SetModelMatrix(glm::translate(m_v3OT));
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	

	//Collision check goes here
	

	m_m4Player = m_pMeshMngr->GetModelMatrix("Steve") * glm::translate(m_v3CenterP);
	if (m_BSCPlayer->GetVisibility()) {
		if (m_BSCPlayer->IsColliding(m_BSCTruck))
			m_pMeshMngr->AddSphereToQueue(m_m4Player * glm::scale(vector3(m_fRadiusP * 2.0f)), m_BSCPlayer->GetColor(), WIRE);
		else
			m_pMeshMngr->AddSphereToQueue(m_m4Player * glm::scale(vector3(m_fRadiusP * 2.0f)), m_BSCPlayer->GetColor(), WIRE);
	}
	m_m4Truck = m_pMeshMngr->GetModelMatrix("Creeper") * glm::translate(m_v3CenterT);
	if (m_BSCPlayer->IsColliding(m_BSCTruck))
		m_pMeshMngr->AddSphereToQueue(m_m4Truck * glm::scale(vector3(m_fRadiusT * 2.0f)), m_BSCTruck->GetColor(), WIRE);
	else
		m_pMeshMngr->AddSphereToQueue(m_m4Truck * glm::scale(vector3(m_fRadiusT * 2.0f)), m_BSCTruck->GetColor(), WIRE);

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	if (m_BSCPlayer->IsColliding(m_BSCTruck))
		m_pMeshMngr->PrintLine("They are colliding! >_<", RERED);
	else
		m_pMeshMngr->PrintLine("They are not colliding! =)", REGREEN);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	if (m_pPlayer != nullptr)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;

	}
	if (m_pTruck != nullptr)
	{
		delete m_pTruck;
		m_pTruck = nullptr;

	}
	if (m_BSCPlayer != nullptr)
	{
		delete m_BSCPlayer;
		m_BSCPlayer = nullptr;

	}
	if (m_BSCTruck != nullptr)
	{
		delete m_BSCTruck;
		m_BSCTruck = nullptr;

	}
	super::Release(); //release the memory of the inherited fields
}