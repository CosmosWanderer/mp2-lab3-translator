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
	При добавлении новых функций:
	1) добавить их в set
	2) добавить функцию в cpp и h файлы
	3) добавить в solveFunc
	Готово
	*/

	// Другие функции проверяют эти сеты, чтобы понять, что существует такая функция
	std::set<std::string> func1 = { "(", "sin(", "cos(" };
	std::set<std::string> func2 = { "max(", "min(" };

	// Функции первого вида
	std::string solveFunc1(std::string value, std::string function);

	float myBracket(float value);

	float mySin(float value);

	float myCos(float value);

	// Функции второго вида
	std::string solveFunc2(std::vector<std::string> value, std::string function);

	float myMax(std::vector<float> values);

	float myMin(std::vector<float> values);
	
};