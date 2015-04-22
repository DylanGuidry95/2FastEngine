#pragma once
#include "SystemDef.h"
#include "ccollisionutils.h"
#include "Core.h"

sysDef(StaticCollision)

bool init() { return true; }
bool term() { return true; }

float snap(float min, float max, float value)
{
	if (value < min || value > max) return value;

	return abs(value - min) < abs(value - max) ? min : max;
}

bool condition(Entity *e)
{
	return e->active && e->collider;	// make sure that e is the rigidbody
}

bool specCondition(Entity *e, Entity *o)
{
	return e->rigidbody && !o->rigidbody || !e->rigidbody && o->rigidbody;
}

void update(Entity *e)
{
	for each (auto o in e->collider->contacts)	// for each contact that DOESN'T have a rigidbody
		if (condition(o) && specCondition(e,o) && e->factoryIndex < o->factoryIndex)
		{
			auto &Collider = o->collider->shape;
			auto &E_Collider = e->collider->shape;
			vec3 N;

			if (Collider.type == Shape::ePlane)
				N = Collider.plane.normal;
			else
				N = E_Collider.plane.normal;

			if (E_Collider.type == Shape::eCircle && Collider.type == Shape::eCircle)
				N = normal((E_Collider.circle.position + e->transform->position()) - (Collider.circle.position + o->transform->position()));

			if (E_Collider.type == Shape::eRect && Collider.type == Shape::eRect)
			{
				e->collider->shape.orgin = e->transform->position();
				o->collider->shape.orgin = o->transform->position();
				N = AABBNormal(e->collider->shape.orgin + e->collider->shape.position + e->collider->shape.rect.min,
							   e->collider->shape.orgin + e->collider->shape.position + e->collider->shape.rect.max,
							   o->collider->shape.orgin + o->collider->shape.position + o->collider->shape.rect.min,
							   o->collider->shape.orgin + o->collider->shape.position + o->collider->shape.rect.max);
			}


			if (E_Collider.type == Shape::eRect && Collider.type == Shape::eCircle)
			{
				float minX = E_Collider.rect.min.x + e->transform->position().x;
				float minY = E_Collider.rect.min.y + e->transform->position().y;

				float maxX = E_Collider.rect.max.x + e->transform->position().x;
				float maxY = E_Collider.rect.max.y + e->transform->position().y;

				vec3 cps = Collider.circle.position + o->transform->position();

				float pX = clamp(minX, maxX, cps.x);
				float pY = clamp(minY, maxY, cps.y);

				float sX = snap(minX, maxX, pX);
				float sY = snap(minY, maxY, pY);

				if (abs(sX - pX) < abs(sY - pY))
					pX = sX; //is colliding in the x
				else
					pY = sY; //is colling in the y

				if (pX == minX) 
				{ N = vec3Make(-1,  0, 0); }
				else if (pX == maxX)
				{ N = vec3Make( 1,  0, 0); }
				else if (pY == minY) 
				{ N = vec3Make( 0, -1, 0); }
				else if (pY == maxY) 
				{ N = vec3Make( 0, 1, 0); }

				vec3 corner = vec3Make(0,0,0);
				if (vec3Distance(vec3Make(minX, minY, 0), cps) < Collider.circle.radius) 
					corner = vec3Make(minX, minY,0);		//top right
				else if (vec3Distance(vec3Make(minX, maxY, 0), cps) < Collider.circle.radius) 
					corner = vec3Make(minX, maxY, 0);	//bot right
				else if (vec3Distance(vec3Make(maxX, minY, 0), cps) < Collider.circle.radius) 
					corner = vec3Make(maxX, minY, 0); //top left
				else if (vec3Distance(vec3Make(maxX, maxY, 0), cps) < Collider.circle.radius) 
					corner = vec3Make(maxX, maxY, 0); //bot left

				if (corner.x != 0 || corner.y != 0)
				{
					N = normal(cps - corner);
				}
			}

			if (E_Collider.type == Shape::eCircle && Collider.type == Shape::eRect)
			{
				float minX = Collider.rect.min.x + o->transform->position().x;
				float minY = Collider.rect.min.y + o->transform->position().y;

				float maxX = Collider.rect.max.x + o->transform->position().x;
				float maxY = Collider.rect.max.y + o->transform->position().y;

				vec3 cps = E_Collider.circle.position + e->transform->position();

				float pX = clamp(minX, maxX, cps.x);
				float pY = clamp(minY, maxY, cps.y);

				float sX = snap(minX, maxX, pX);
				float sY = snap(minY, maxY, pY);

				if (abs(sX - pX) < abs(sY - pY))
					pX = sX; //is colliding in the x
				else
					pY = sY; //is colling in the y

				if (pX == minX)
				{
					N = vec3Make(-1, 0, 0);
				}
				else if (pX == maxX)
				{
					N = vec3Make(1, 0, 0);
				}
				else if (pY == minY)
				{
					N = vec3Make(0, -1, 0);
				}
				else if (pY == maxY)
				{
					N = vec3Make(0, 1, 0);
				}

				vec3 corner = vec3Make(0, 0, 0);
				if (vec3Distance(vec3Make(minX, minY, 0), cps) < E_Collider.circle.radius)
					corner = vec3Make(minX, minY, 0);		//top right
				else if (vec3Distance(vec3Make(minX, maxY, 0), cps) < E_Collider.circle.radius)
					corner = vec3Make(minX, maxY, 0);	//bot right
				else if (vec3Distance(vec3Make(maxX, minY, 0), cps) < E_Collider.circle.radius)
					corner = vec3Make(maxX, minY, 0); //top left
				else if (vec3Distance(vec3Make(maxX, maxY, 0), cps) < E_Collider.circle.radius)
					corner = vec3Make(maxX, maxY, 0); //bot left

				if (corner.x != 0 || corner.y != 0)
				{
					N = normal(cps - corner);
				}
			}



			if (e->rigidbody)
			{
				vec3 P = N * vec3Dot(e->rigidbody->velocity / -1, N);
				e->rigidbody->velocity = P * 2 + e->rigidbody->velocity;
			}
			else
			{
				vec3 P = N * vec3Dot(o->rigidbody->velocity / -1, N);
				o->rigidbody->velocity = P * 2 + o->rigidbody->velocity;
			}
		}
}

sysEndDef