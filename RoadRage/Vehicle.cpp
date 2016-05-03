// Paul Lampanaro
#include "Vehicle.h"

void Vehicle::HandleRotation(void)
{
	// apply rotation acceleration to velocity
	rotationAccel = -(velocity.x * 0.04f);

	float retunVal;

	if (isTurning == false) {
		retunVal = 0.16f;
		if (rotation < 1.0f && rotation > -1.0f) {
			rotation = 0.0f;
			rotationAccel = 0.0f;
			rotationVel = 0.0f;
		}
	}
	else {
		retunVal = 0.08f;
	}

	// if not turning, realign
	//if (isTurning)
	if (true)
	{
		//positive banana
		if (rotation <= 30.0f && rotation > 15.0f)
		{
			rotationVel -= 0.32f; // right now hardcoded
		}
		if (rotation <= 15.0f && rotation >=  0.0f)
		{
			rotationVel -= retunVal; // right now hardcoded
		}
		/*
		if (rotation < 0.0f && rotation > 0.0f)
		{
			rotationVel += 0.08f; // right now hardcoded
		}*/

		//negative banana
		if (rotation >= -30.0f && rotation < -15.0f)
		{
			rotationVel += 0.32f; // right now hardcoded
		}
		if (rotation >= -15.0f && rotation <= 0.0f)
		{
			rotationVel += retunVal; // right now hardcoded
		}
		/*
		else if (rotation > 0.0f)
		{
			rotationVel -= 0.08f; // right now hardcoded
		}*/
	}


	//if (isTurning = false)
	//{
	//	//positive banana
	//	if (rotation <= 90.0f && rotation > 45.0f){ rotationVel -= 0.16f; }
	//	if (rotation <= 45.0f && rotation >= 0.0f){ 
	//		rotationVel -= 0.08f; 
	//		if (rotation == 0.0f) {
	//			rotationAccel = 0.0f;
	//			rotationVel = 0.0f;
	//		}
	//	}

	//	//negative banana
	//	if (rotation >= -90.0f && rotation < -45.0f){ rotationVel += 0.16f; }
	//	if (rotation >= -45.0f && rotation <= 0.0f){ 
	//		rotationVel += 0.08f; 
	//		if (rotation == 0.0f) {
	//			rotationAccel = 0.0f;
	//			rotationVel = 0.0f;
	//		}
	//	}
	//}

	rotationVel += rotationAccel;

	// apply rotation velocity to rotation angle
	rotation += rotationVel;

	// do this just in case
	rotation = fmod(rotation, 360.0f);


	//banana
	if (rotation > 30.0f) {
		rotation = 30.0f;
	}
	if (rotation < -30.0f) {
		rotation = -30.0f;
	}


	// apply friction
	rotationVel *= friction;

	// reset rotation acceleration
	rotationAccel = 0.0f;
}

