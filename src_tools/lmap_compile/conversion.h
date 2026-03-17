#pragma once

#include <formats/lmap.h>
#include <common/types.h>
#include <json.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>

CollisionType stringToCollisionType(char str[]);
Orientation stringToOrientation(char str[]);
Orientation stringToOrientation(const char* str);
EntityType stringToEntityType(const char* str);
EntityType stringToEntityType(char str[]);