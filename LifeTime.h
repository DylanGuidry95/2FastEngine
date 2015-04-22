#pragma once
#include "Component.h"

//Parameters for how long and object cna stay on the screen

compDef(LifeTime)

float timer;
int totalLife;

LifeTime() : timer(0), totalLife(3) {}

compEndDef