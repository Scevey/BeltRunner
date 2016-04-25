#include "AppClass.h"
#include "Vehicle.h"

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingClass example"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	// m_v3OP = vector3(0.0f, 0.0f, 5.0f); // replaced by Vehicle class
	m_v3OT = vector3(0.0f, 0.5f, -5.0f);

	//Load Models
	m_pMeshMngr->LoadModel("car.obj", "Player");
	m_pMeshMngr->LoadModel("Truck.obj", "Truck");

	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve2"); //banana
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper2");
	road = new Road();

	testVehicle = new Vehicle();

	// Player
	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve");
	m_BSCPlayer = new MyBoundingClass(vertexList);

	// Truck
	vertexList = m_pMeshMngr->GetVertexList("Creeper");
	m_BSCTruck = new MyBoundingClass(vertexList);

	//camera mumbo jumbo [banana]
	vector3 camPos = vector3(0.0f, 10.0f, 10.0f);
	vector3 camTar = vector3(0.0f, 0.0f, 0.0f);
	vector3 camUp = vector3(0.0f, 1.0f, 0.0f);
	m_pCameraMngr->SetPositionTargetAndView(camPos, camTar, camUp);
	//end camera mumbo jumbo
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	// find elapsed time [banana]
	double deltaTime = m_pSystem->LapClock();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	// Update Vehicle
	testVehicle->Update(deltaTime);

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(testVehicle->GetModelMatrix() * ToMatrix4(m_qArcBall), "Player");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3OT), "Truck");
	m_BSCPlayer->SetModelMatrix(testVehicle->GetModelMatrix() * ToMatrix4(m_qArcBall));
	m_BSCTruck->SetModelMatrix(glm::translate(m_v3OT));
	
	matrix4 testMove = road->Update1(deltaTime);

	// Set model matrices
	m_pMeshMngr->SetModelMatrix(testMove, "Steve2");
	testMove = road->Update2(deltaTime);
	m_pMeshMngr->SetModelMatrix(testMove, "Creeper2");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	
	//Collision check goes here
	m_pMeshMngr->AddSphereToQueue(
		m_BSCPlayer->GetModelMatrix() *
		glm::translate(vector3(m_BSCPlayer->GetCenter())) *
		glm::scale(vector3(m_BSCPlayer->GetRadius()) * 2.0f),
		m_BSCPlayer->GetColor(), WIRE);

	m_pMeshMngr->AddCubeToQueue(
		m_BSCPlayer->GetModelMatrix() *
		glm::translate(vector3(m_BSCPlayer->GetCenter())) *
		glm::scale(vector3(m_BSCPlayer->GetSize())),
		m_BSCPlayer->GetColor(), WIRE);

	m_pMeshMngr->AddSphereToQueue(
		m_BSCTruck->GetModelMatrix() *
		glm::translate(vector3(m_BSCTruck->GetCenter())) *
		glm::scale(vector3(m_BSCTruck->GetRadius()) * 2.0f),
		m_BSCTruck->GetColor(), WIRE);

	m_pMeshMngr->AddCubeToQueue(
		m_BSCTruck->GetModelMatrix() *
		glm::translate(vector3(m_BSCTruck->GetCenter())) *
		glm::scale(vector3(m_BSCTruck->GetSize())),
		m_BSCTruck->GetColor(), WIRE);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	/* Road debug
	m_pMeshMngr->PrintLine(std::to_string(road->getCurrentDebug()), REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(road->getHitDebug()), REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(road->getStartDebug()), REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(road->getfPercDebug()), REYELLOW);
	*/

	/* Vehicle debug
	vector3 debug = testVehicle->GetPosition();
	m_pMeshMngr->PrintLine(std::to_string(debug.x), REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(debug.y), REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(debug.z), REYELLOW);
	*/

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

	if (road != nullptr) 
	{ 
		delete road; 
		road = nullptr; 
	} // banana

	if (testVehicle != nullptr)
	{
		delete testVehicle;
		testVehicle = nullptr;
	}

	super::Release(); //release the memory of the inherited fields
}