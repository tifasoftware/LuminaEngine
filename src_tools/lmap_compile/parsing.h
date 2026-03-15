#pragma once

#include <formats/lmap.h>
#include <common/types.h>
#include <json.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "global.h"

bool parse_tilemapdef(FILE* file);
void parse_layout(const char* file);