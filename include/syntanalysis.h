#pragma once

#include <unordered_map>
#include <string>
#include <set>
#include <vector>


#include "functions.h"

class syntanalysis {
public:
	std::vector<std::pair<std::string, std::string>> analyse(std::vector<std::pair<std::string, std::string>> lexems, std::unordered_map<std::string, std::string> variables, std::unordered_map<std::string, std::string> constants, std::set<std::string> func1, std::set<std::string> func2);
};