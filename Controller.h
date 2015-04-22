#pragma once 
#include "Component.h"

/*
	Component base macro for controlls and modifiable variables for the Entities
*/

compDef(Controller)

char  forward, reverse, turn_Left, turn_Right, fire; //Movement direction
float speed, torque; 
int topSpeed;

float firingDelay; //Fire delay between shots
float firingTimer; //Timer for shots

void clear()
{
	forward = reverse = turn_Left = turn_Right = fire = 0; //Sets the directions default to zero
}

//Default construtor for the controller
//Sets default controls and defaults for the othere variables
Controller() : speed(300), torque(1), firingDelay(1), firingTimer(0),
turn_Left('A'), turn_Right('D'), forward('W'), reverse('S'), fire('C')
{}


compEndDef
