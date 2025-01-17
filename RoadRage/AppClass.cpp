#include "AppClass.h"
#include "Vehicle.h"

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Road Rage"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	//m_pSystem->SetWindowResolution(RESOLUTIONS::CV_720x1280_9x16_HD);
	//m_pSystem->SetWindowHeight(1280);
	//m_pSystem->SetWindowWidth(720);
}

void AppClass::InitVariables(void)
{
	//Initialize positions

	//Load Models
	m_pMeshMngr->LoadModel("car.obj", "Player");
	m_pMeshMngr->LoadModel("Truck.obj", "Truck");
	m_pMeshMngr->LoadModel("crate.obj", "Crate");
	m_pMeshMngr->LoadModel("Road.obj", "Steve2"); //banana
	m_pMeshMngr->LoadModel("Road.obj", "Creeper2");
	road = new Road();
	testVehicle = new Vehicle();
	otherTestVehicleTotallyNotATruck = new Truck(vector3(0.0f, 0.0f, -8.0f));
	crate = new Crate(otherTestVehicleTotallyNotATruck->GetPosition());
	m_pBOMngr = MyBOManager::GetInstance();
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Player"), "Player");
	//m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Truck"), "Truck");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Crate"), "Crate");

	//game state variables
	score = 0.0;
	life = 100;
	losses = 0;
	highScore = 0.0;
	displayHUD = true;

	//camera mumbo jumbo [banana]
	vector3 camPos = vector3(2.0f, 7.0f, 9.0f);
	vector3 camTar = vector3(2.0f, 0.0f, 0.0f);
	vector3 camUp = vector3(0.0f, 1.0f, 0.0f);
	m_pCameraMngr->SetPositionTargetAndView(camPos, camTar, camUp);
	//end camera mumbo jumbo

	//String sRoute = m_pSystem->m_pFolder->GetFolderData();
	//sRoute += m_pSystem->m_pFolder->GetFolderAudio();

	//////Background music
	//music.openFromFile(sRoute + "music.mp3");

	//number of collisions
	collisions = 0;
}

void AppClass::Update(void)
{
		//Update the system's time
		m_pSystem->UpdateTime();

		// find elapsed time [banana]
		double deltaTime = m_pSystem->LapClock();

		//increase score with time
		score += deltaTime;

		//Update the mesh manager's time without updating for collision detection
		m_pMeshMngr->Update();

		//First person camera movement
		if (m_bFPC == true)
			CameraRotation();

		ArcBall();

		// Update Vehicle
		otherTestVehicleTotallyNotATruck->TruckUpdate(deltaTime);
		testVehicle->Update(deltaTime);
		crate->SetNewStart(otherTestVehicleTotallyNotATruck->GetPosition());
		//boundaries will abstract into a method later
		vector3 posV = testVehicle->GetPosition();
		testVehicle->CheckBounds(posV);

		std::vector<int> crateCollision = m_pBOMngr->GetCollidingVector("Player");
		vector3 posC = crate->GetPosition();

		if (crateCollision.size() > 0)
		{
			vector3 collisionForce = vector3(posC.x - posV.x, posC.y - posV.y, posC.z - posV.z);
			// collisionForce = glm::clamp(collisionForce, 2, 3);
			crate->AddForce(collisionForce);
		}

		// Set model matrices
		matrix4 testMove = road->Update1(deltaTime);
		m_pMeshMngr->SetModelMatrix(testMove, "Steve2");
		testMove = road->Update2(deltaTime);
		m_pMeshMngr->SetModelMatrix(testMove, "Creeper2");
		testMove = crate->Move(deltaTime);


		//Set the model matrices for both objects and Bounding Spheres
		m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 0.5f, 0.0f)) * testVehicle->GetModelMatrix()/* * ToMatrix4(m_qArcBall)*/, "Player");
		m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f, 0.5f, 0.0f)) * otherTestVehicleTotallyNotATruck->GetModelMatrix(), "Truck");
		m_pMeshMngr->SetModelMatrix(testMove, "Crate");

		m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Player"), "Player");
		m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Truck"), "Truck");
		m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Crate"), "Crate");

		m_pBOMngr->Update();//Update collision detection
		//m_pBOMngr->DisplaySphere(-1, REWHITE);
		if (m_pBOMngr->getOctVis())
		{
			m_pBOMngr->DisplayReAlligned();
			m_pBOMngr->DisplayOriented(-1, REWHITE);
		}

		//Indicate the FPS
		int nFPS = m_pSystem->GetFPS();

		//Adds all loaded instance to the render list
		m_pMeshMngr->AddInstanceToRenderList("ALL");

		//print info into the console
		printf("FPS: %d            \r", nFPS);//print the Frames per Second

		//Print info on the screen
		m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
		m_pMeshMngr->PrintLine("Hold H: Toggle HUD");

		if (displayHUD == true)
		{
		m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
		m_pMeshMngr->PrintLine("Hold B: Build Octree");

		m_pMeshMngr->Print("O: Toggle Octree On:");
		m_pMeshMngr->PrintLine(std::to_string(m_pBOMngr->getOctOn()), REPURPLE);

		m_pMeshMngr->Print("V: Toggle Octree Visible:");
		m_pMeshMngr->PrintLine(std::to_string(m_pBOMngr->getOctVis()), REPURPLE);
		}

		std::vector<int> list = m_pBOMngr->GetCollidingVector(0);

		m_pMeshMngr->PrintLine(std::to_string(testVehicle->getTurning()), REPURPLE);


		if (list.size() > 0)
		{
			m_pMeshMngr->PrintLine("They are colliding! >_<", RERED);

			//decrease score when colliding
			//score -= 0.1;

			//update count of collisions
			collisions++;
			life--;
		}
		else
		{

		}

		//if life hits 0, increment losses and reset everything
		if (life <= 0)
		{
			if (score > highScore)
			{
				highScore = score;
			}
			score = 0;
			life = 100;
			losses++;
		}

		if(displayHUD == true)
		{
			m_pMeshMngr->PrintLine("They are not colliding! =)", REGREEN);
			m_pMeshMngr->Print("FPS: ");
			m_pMeshMngr->Print(std::to_string(nFPS), RERED);

			m_pMeshMngr->Print("High Score: ");
			m_pMeshMngr->PrintLine(std::to_string(highScore));

			m_pMeshMngr->Print("Score: ");
			m_pMeshMngr->PrintLine(std::to_string(score));

			m_pMeshMngr->Print("Life: ");
			m_pMeshMngr->PrintLine(std::to_string(life));

			m_pMeshMngr->Print("Losses: ");
			m_pMeshMngr->PrintLine(std::to_string(losses));

			m_pMeshMngr->Print("Collisions: ");
			m_pMeshMngr->PrintLine(std::to_string(collisions));
		}

}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		//m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
		break;
	}

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList();
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{

	if (m_pOctreeHead != nullptr)
	{
		delete m_pOctreeHead;
		m_pOctreeHead = nullptr;
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
	if (crate != nullptr)
	{
		delete crate;
		crate= nullptr;
	}
	super::Release(); //release the memory of the inherited fields
}