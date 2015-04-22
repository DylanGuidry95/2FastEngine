#pragma once 
#include "SystemDef.h"
#include "Core.h"

sysDef(LapCounter)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e && e->active && e->controller && e->collider;
}

void update(Entity *e)
{
	
}

sysEndDef