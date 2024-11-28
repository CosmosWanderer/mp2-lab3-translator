#include "functions.h"

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

/* Функции первого вида */
// Внешняя функция
std::string functions::solveFunc1(std::string value, std::string function) {
	float vl = stof(value);
	float ans = 0;
	if (function == "(") {
		ans = myBracket(vl);
	}
	else if(function == "sin(") {
		ans = mySin(vl);
	}
	else if(function == "cos(") {
		ans = myCos(vl);
	}
	
	return std::to_string(ans);
}

// Скобка
float functions::myBracket(float value) {
	return value;
}
// Синус (не готов)
float functions::mySin(float value) {
	return sin(value);
}
// Косинус (не готов)
float functions::myCos(float value) {
	return cos(value);
}

/* Функции второго вида */
// Внешняя функция
std::string functions::solveFunc2(std::vector<std::string> values, std::string function) {
	std::vector<float> fvalues;
	for (int i = 0; i < values.size(); i++) {
		fvalues.push_back(stof(values[i]));
	}
	float ans = 0;
	if (function == "max(") {
		ans = myMax(fvalues);
	}
	else if (function == "min(") {
		ans = myMin(fvalues);
	}

	return std::to_string(ans);

}

// Максим(ум)
float functions::myMax(std::vector<float> values) {
	float mx = FLT_MIN;
	for (int i = 0; i < values.size(); i++) {
		if (values[i] > mx) mx = values[i];
	}
	return mx;
}
// Минимум
float functions::myMin(std::vector<float> values) {
	float mn = FLT_MAX;
	for (int i = 0; i < values.size(); i++) {
		if (values[i] < mn) mn = values[i];
	}
	return mn;
}