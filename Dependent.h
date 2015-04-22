#pragma once
#include "Component.h"

//Dependants of the parent if any
compDef(Dependent)

Entity *child;

Dependent() : child(0) {}

compEndDef