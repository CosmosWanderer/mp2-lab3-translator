#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <stack>

#include "functions.h"

class calculator {
public:
	std::string calculate(std::vector<std::pair<std::string, std::string>> postfixForm); 
};