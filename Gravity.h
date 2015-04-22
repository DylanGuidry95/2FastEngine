#pragma once
#include "Component.h"
#include "ccollisionutils.h"
#include "Rigidbody.h"

compDef(Gravity)

vec3 pull;

Gravity() : pull() {}

compEndDef