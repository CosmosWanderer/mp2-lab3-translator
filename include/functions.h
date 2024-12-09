# pragma once

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
 
class functions {
public:
	/*
	Fast function-adding system:
	1) Add it into set, which is needed for tanslator to know, that this function exists
	2) Add realistatin of this function in cpp and h files
	3) Add it in solveFunc
	Ready
	*/

	// Functions lists for translator
	std::set<std::string> func1 = { "(", "sin(", "cos(" };
	std::set<std::string> func2 = { "max(", "min(" };


	/*
	func1 - receive an expression, return a value. The expression can be as complex as you like.
	example: sin(Pi/2 - 12 * (max(1, 2, 3))

	func2 - receive several values ??separated by commas. 
	OLD:
	So far, only single values ??(float, integer, constant and variable) separated by commas are accepted.
	That is, even the value -3.0 cannot be used in such a function, since there is a unary minus here.
	Then I will make a normal implementation, where each expression inside the function will be calculated recursively.
	example: max(Pi, 1, 2, 3, 8)

	UPD: 
	I did it, now they are working as intended! You can enter whatever you want for as long as it is exactly what I want for you to enter, and it will work!
	example: max(sin(Pi / 2), 1 + 2 * (1 - 2), -123, max(min(1, 2), 2))
	*/

	// func1
	std::string solveFunc1(std::string value, std::string function);

	float myBracket(float value);

	float mySin(float value);

	float myCos(float value);

	// func2
	std::string solveFunc2(std::vector<std::string> value, std::string function);

	float myMax(std::vector<float> values);

	float myMin(std::vector<float> values);
	
};