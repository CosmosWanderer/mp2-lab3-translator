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
	1) добавить их в set, который нужен, чтобы транслятор знал о существовании этих функций
	2) добавить реализацию функции в cpp и h файлы
	3) добавить в solveFunc
	Готово
	*/

	// Другие функции проверяют эти сеты, чтобы понять, что существует такая функция
	std::set<std::string> func1 = { "(", "sin(", "cos(" };
	std::set<std::string> func2 = { "max(", "min(" };


	/*
	Функции делятся на два вида
	func1 - получают выражение, возвращают значение. Выражение может быть сколь угодно сложным, например, для синуса: sin(Pi/2 - 12 * (max(1, 2, 3))

	func2 - получают несколько значений через запятые. Пока что принимают исключительно единичные значения (float, integer, constant и variable) через запятую.
	Т.е. даже значение -3.0 не может быть использовано в такой функции, т.к. здесь присутствует унарный минус. 
	Потом сделаю нормальную реализацию, где каждое выражение внутри функции будет высчитываться рекурс
	ивно
	пример: max(Pi, 1, 2, 3, 8)
	*/

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