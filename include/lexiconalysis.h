#pragma once

#include <unordered_map>
#include <string>
#include <set>
#include <vector>

#include "functions.h"

class lexiconalysis {
public: 
	std::set<char> characters = { 'a', 'A', 'b', 'B',
	'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G',
	'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L',
	'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q',
	'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V',
	'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z' };
	std::set<char> numbers = { '0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9' };
	std::set<char> others = { '+', '-', '*', '/', '=', '(', ')', '.', ',' };

	std::vector<std::pair<std::string, std::string>> analyse(std::string str, std::unordered_map<std::string, std::string> variables, std::unordered_map<std::string, std::string> constants, std::set<std::string> func1, std::set<std::string> func2);
};
