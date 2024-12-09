#pragma once

#include <iostream> 
#include <unordered_map>
#include <string>
#include <set>
#include <vector>

#include "lexiconalysis.h"
#include "syntanalysis.h"
#include "functions.h"
#include "transformator.h"
#include "calculator.h"

class translator { 
public:
	// Used for func2 counting
	bool recErr = 0;

	// Use addFunction on function-lists from functions.h
	std::set<std::string> func1; 
	std::set<std::string> func2; 

	std::unordered_map <std::string, std::string> variables;
	std::unordered_map <std::string, std::string> constants;
	
	// I dont want to translate this
	// И ещё я решил, что если имеются функции, или хоть что-то float, (в т. ч. переменная или константа), ну или значение записываем в переменную, то делаем вообще всё - float. 
	// Это, наверное, неверно, но я хз, как надо, а лаба всё равно не про разделение на инты и флоты
	// Ну, т.е., я ведь реализовал разделение на инты и флоты? Реализовал. А как бы поменять потом это на правильную расстановку труда особого составить не должно

	// For breaking program cycle
	bool isGoing = 1;  

	// Adding functions from functions.h
	void addFunctions(std::set<std::string> f1, std::set<std::string> f2);

	// Get string, return answer or create variable, or throw exception
	std::string execute(std::string input);
};
