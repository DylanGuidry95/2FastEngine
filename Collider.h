#pragma once
#include "Component.h"
#include "ccollisionutils.h"
#include <list>


/*
	Class that holds the basics for the collider
		holds the varibales and constructors
*/
compDef(Collider)

int faction; //faction for the Entity
Shape shape; //Entity shape of collision


std::list<Entity *> contacts;

Collider() : faction(0) {} //Default constructor

compEndDef