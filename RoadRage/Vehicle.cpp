// Paul Lampanaro
#include "Vehicle.h"

void Vehicle::HandleRotation(void)
{
	// apply rotation acceleration to velocity
	rotationAccel = -(velocity.x * 0.01f);

	// if not turning, realign
	if (true)
	{
		if (rotation < 0.0f)
		{
			rotationVel += 0.08f; // right now hardcoded
		}
		else if (rotation > 0.0f)
		{
			rotationVel -= 0.08f; // right now hardcoded
		}
	}

	rotationVel += rotationAccel;

	// apply rotation velocity to rotation angle
	rotation += rotationVel;

	// do this just in case
	rotation = fmod(rotation, 360.0f);

	// apply friction
	rotationVel *= friction;

	// reset rotation acceleration
	rotationAccel = 0.0f;
}
