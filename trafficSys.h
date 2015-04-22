#pragma once 
#include "SystemDef.h"
#include "Core.h"

sysDef(trafficSys)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e && e->render && e->traffic;
}

void update(Entity *e)
{
	if (e->render->frame >= 2 && e->traffic->gate1 && e->traffic->gate2)
			{
				entityFree(e->traffic->gate1);
				entityFree(e->traffic->gate2);
				e->render->frameRate = 8;
				e->render->texture = "Flag";
				e->render->mesh = "flagMesh";
			}
}

sysEndDef