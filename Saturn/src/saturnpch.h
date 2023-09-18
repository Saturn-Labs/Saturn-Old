#pragma once

#include <string>
#include <iostream>
#include <ostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>
#include <vector>
#include <filesystem>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <cctype>
#include <regex>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Saturn/IO/Log.h"
#include "Saturn/Debug/Instrumentor.h"

#ifdef ST_PLATFORM_WINDOWS
#include <Windows.h>
#endif