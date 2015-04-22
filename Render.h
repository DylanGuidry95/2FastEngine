#pragma once
#include "Component.h"

compDef(Render)

float frame;
float frameRate;
std::string shader, texture, mesh;

Render() : frame(0), frameRate(8) {}

compEndDef