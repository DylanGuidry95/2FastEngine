#pragma once 
#include "SystemDef.h"

sysDef(RigidbodyDynamics)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e) 
{
	return e && e->active && e->rigidbody && e->transform;
}

void update(Entity *e) 
{
	auto &pos = e->transform->position();
	auto &rot = e->transform->m_local;
	auto &vel = e->rigidbody->velocity;
	auto &force = e->rigidbody->force;
	auto &drag = e->rigidbody->drag;
	auto &mass = e->rigidbody->mass;
	auto &aM = e->rigidbody->angularMomentum;
	auto &tor = e->rigidbody->torque;
	float dt = core(Time).getDeltaTime();


	e->transform->m_local = makeRotation(e->rigidbody->angularMomentum * -1 * dt)
		* e->transform->m_local
		* makeTranslation(e->rigidbody->velocity * dt);

	vec3 a_damp = (vel * -1) * drag;
	vec3 a_acc = (force + a_damp) * (1 / mass);
	vel = vel + a_acc * dt;
	force = vec3Zero();

	float damp = (aM * -1) * drag;
	float acc = (tor + damp) * (1 / mass);
	aM = aM + acc * dt;
	tor = 0;
}

sysEndDef