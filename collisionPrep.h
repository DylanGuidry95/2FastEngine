#pragma once
#include "SystemDef.h"

sysDef(collisionPrep)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->collider;
}

void update(Entity *e)
{
	e->collider->contacts.clear();
}

sysEndDef