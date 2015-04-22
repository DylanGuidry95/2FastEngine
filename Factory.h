#pragma once
#include "Core.h"
#include "Entity.h"

coreDef(Factory)

std::vector<Entity> m_entities;

Entity *newEntity()
{
	for (int i = 0; i < m_entities.size(); ++i)
		if (!m_entities[i].active && !m_entities[i].newEntity)
		{
			m_entities[i].newEntity = true;
			return &m_entities[i];
		}

	m_entities.push_back(Entity(m_entities.size()));
	return &m_entities.back();
}

bool step()
{
	for (int i = 0; i < m_entities.size(); ++i)
	{
		// new entities now allowed to update for the next frame
		if (m_entities[i].newEntity)
		{
			m_entities[i].active = true;
			m_entities[i].newEntity = false;			
		}
		// old entities allowed to be removed for next frame
		if (m_entities[i].deleteEntity)
		{
			m_entities[i].active = false;
			m_entities[i].deleteEntity = false;
		}
	}
	return true;
}

bool init() 
{
	m_entities.reserve(64);
	return true; 
}
bool term() { return true; }

public:

	std::vector<Entity> &getEntities() { return m_entities; }

	void FreeEntity(Entity *e)
	{
		e->deleteEntity = true;
	}

	Entity *MakeTank(float x, float y, int faction, char up = 'W', char down = 'S', char left = 'A' , char right = 'D', char tLeft = 'Q', char tRight = 'E', char Fire = 'C')
	{
		Entity *tank = newEntity();
		Entity *turret = newEntity();
		Entity *collider = newEntity();
		Entity *light = newEntity();

		compMake(tank, controller);
		compMake(tank, collider);
		compMake(tank, transform);
		compMake(tank, rigidbody);
		compMake(tank, render);
		compMake(tank, dependent);

		compMake(turret, controller);
		compMake(turret, transform);
		compMake(turret, render);
		compMake(turret, rigidbody);
		compMake(turret, collider);

			tank->dependent->child = turret;

			tank->transform->m_local = makeRotation((1, 1.6));

			tank->transform->position().x = x;
			tank->transform->position().y = y;
			tank->transform->position().z = 0;

			tank->controller->forward = up;
			tank->controller->reverse = down;
			tank->controller->turn_Left = left;
			tank->controller->turn_Right = right;
			tank->controller->fire = 0;

			tank->collider->faction = faction;
			tank->controller->topSpeed = 420;
			tank->controller->torque = 3;
			tank->collider->shape = MakeCircle(0, 0, 15);
			//tank->collider->shape = MakeRect(0, 0, -30, -60, 30, 60); 
			tank->rigidbody->mass = .1;
			tank->rigidbody->drag = 1;

			///Turret info
			turret->controller->speed = 0;
			turret->controller->torque = 5;
			turret->rigidbody->drag = 10;
			turret->collider->faction = tank->collider->faction;
			//turret->collider->shape = MakeCircle(0, 0, 0);
			turret->collider->shape.type = Shape::eNone;
			turret->controller->turn_Left = tLeft;
			turret->controller->turn_Right = tRight;
			turret->controller->fire = Fire;

			turret->transform->m_parent = tank->transform;
			turret->name = turret->render->mesh;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			////Render data
			tank->render->shader = "Texture";
			turret->render->shader = "Texture";
			turret->render->mesh = "Turret";
			if (faction == 1)
			{
				tank->render->mesh = "Car";
				tank->render->texture = "Car1texture";
				turret->render->texture = "Car1Turret";
			}
			else
			{
				tank->render->mesh = "Car";
				tank->render->texture = "Car2texture";
				turret->render->texture = "Car2Turret";
			}
			tank->name = tank->render->mesh;

			return tank;
		
/////////////////////////////////////////////////////////

	}


	Entity *MakeBullet(Transform *source, int faction, float speed)
	{
		Entity *bullet = newEntity();

		bullet->name = "Bullet";

		compMake(bullet, transform);
		compMake(bullet, render);
		compMake(bullet, collider);
		compMake(bullet, rigidbody);
		compMake(bullet, controller);
		compMake(bullet, lifeTime);

		bullet->transform->m_local = source->m_global;
		bullet->render->mesh = "Bullet";
		bullet->render->shader = "Flat";
		bullet->collider->faction = faction;
		bullet->collider->shape = MakeCircle(0,0,5);
		//bullet->collider->shape = MakeRect(0, 0, -20, -10, 20, 40);
		bullet->rigidbody->velocity = bullet->transform->up() * speed;

		bullet->rigidbody->drag = 0;
		bullet->rigidbody->mass = .1;
		bullet->lifeTime->totalLife = 15;

		bullet->controller->clear();

	    return bullet;
	}

	Entity *MakeBorder(float x, float y, vec3 n)
	{
		Entity *wall = newEntity();

		compMake(wall, collider);
		compMake(wall, transform);

		wall->transform->position().x = x;
		wall->transform->position().y = y;
		wall->transform->position().z = 0;

		wall->collider->faction = 0;

		wall->collider->shape = MakePlane(0, 0, n);

		return wall;
	}

	Entity *makeLine(float x, float y, vec3 n)
	{
		Entity *line = newEntity();

		compMake(line, collider);
		compMake(line, transform);

		line->transform->position().x = x;
		line->transform->position().y = y;
		line->transform->position().z = 0;

		line->collider->shape = MakePlane(0,0,n);

		return line;
	}

	Entity *makeCenter(float x, float y)
	{
		Entity *center = newEntity();

		compMake(center, collider);
		compMake(center, transform);

		center->transform->position().x = x;
		center->transform->position().y = y;
		center->transform->position().z = 0;

		center->collider->shape = MakeRect(0, 0, -325, -160, 350, 160);

		return center;
	}

	Entity *makeBG(float x, float y)
	{
		Entity *BG = newEntity();

		compMake(BG, transform);
		compMake(BG, render);

		BG->render->texture = "Track";
		BG->render->mesh = "TrackMesh";
		BG->render->shader = "Texture";

		BG->transform->position().x = x;
		BG->transform->position().y = y;
		BG->transform->position().z = 0;

		return BG;
	}

	Entity *makeLight(float x, float y, Entity *gate1, Entity *gate2)
	{
		Entity *light = newEntity();

		compMake(light, transform);
		compMake(light, render);
		compMake(light, traffic);

		light->render->texture = "Light";
		light->render->mesh = "lightMesh";
		light->render->shader = "Texture";

		light->traffic->gate1 = gate1;
		light->traffic->gate2 = gate2;
		light->render->frameRate = 1;

		light->transform->position().x = x;
		light->transform->position().y = y;
		light->transform->position().z = 0;

		return light;
	}

	Entity *makeText(float x, float y, std::string text, int w = 16, int h = 24, Transform *parent = nullptr)
	{
		Entity *e = newEntity();

		compMake(e, transform);
		compMake(e, textRender);

		e->transform->m_local = makeScale(vec3Make(w,h,1));

		e->textRender->text = text;

		e->transform->m_parent = parent;
		e->transform->position().x = x;
		e->transform->position().y = y;
		e->transform->position().z = 0;

		return e;
	}

	Entity *makeGate(float x, float y, vec3 n)
	{
		Entity *gate = newEntity();

		compMake(gate, collider);
		compMake(gate, transform);

		gate->transform->position().x = x;
		gate->transform->position().y = y;
		gate->transform->position().z = 0;

		gate->collider->shape = MakePlane(0, 0, n);

		gate->collider->faction = 3;

		return gate;
	}

coreEndDef