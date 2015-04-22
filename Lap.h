#pragma once 
#include "Component.h"


compDef(Lap)

int numberOfLaps;
float lapnumber;

Entity *line;

Lap() : numberOfLaps(3), lapnumber(0) {}

compEndDef