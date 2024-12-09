#pragma once

#include <iostream> 
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <stack>

#include "functions.h"

class transformator {
public:
	std::vector<std::pair<std::string, std::string>> transform(std::vector<std::pair<std::string, std::string>> lexems);
};