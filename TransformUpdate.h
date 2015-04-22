#pragma once
#include "SystemDef.h"
#include "crenderutils.h"

sysDef(TransformUpdate)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->transform;
}


void update(Entity *e)
{
	 e->transform->getGlobal();
}


sysEndDef