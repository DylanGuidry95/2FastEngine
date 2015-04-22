#pragma once
#include "SystemDef.h"

sysDef(GravityAttract)

//rigidbody.addForce(gravity attractor variable)
bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->rigidbody && e->gravity && e->transform;
}

void update(Entity *e)
{
	float dt = core(Time).getDeltaTime();
	e->rigidbody->addForce(e->gravity->pull * dt);
}

sysEndDef