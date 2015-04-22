
#pragma once

#include "Transform.h"
#include "Rigidbody.h"
#include "Render.h"
#include "Controller.h"
#include "Collider.h"
#include "Dependent.h"
#include "LifeTime.h"
#include "Gravity.h"
#include "TextRender.h"
#include "traffic.h"
#include <string>

//Declares all the objects as part of the Entity class 

#define entityFree(e)  do { \
						compFree(e, transform); \
						compFree(e, rigidbody); \
						compFree(e, render); \
						compFree(e, controller); \
						compFree(e, collider); \
						compFree(e, dependent); \
						compFree(e, lifeTime); \
						compFree(e, gravity); \
						compFree(e, textRender); \
						compFree(e, traffic); \
						e->active = false; \
						} while (0)


struct Entity
{
	std::string name;
	bool active;
	bool newEntity;
	bool deleteEntity;

	int factoryIndex;
	//Redefines the class names
	Transform *transform;
	Rigidbody *rigidbody;
	Render    *render;
	Controller *controller;
	Collider *collider;
	Dependent *dependent;
	LifeTime *lifeTime;
	Gravity *gravity;
	TextRender *textRender;
	trafficConfig *traffic;

	//Default constructor for the Entity
	Entity(int UID) : factoryIndex(UID), active(false), newEntity(true), deleteEntity(false),
		transform(0),
		rigidbody(0),
		render(0),
		controller(0),
		collider(0),
		dependent(0),
		lifeTime(0),
		gravity(0),
		textRender(0),
		traffic(0) { }
};