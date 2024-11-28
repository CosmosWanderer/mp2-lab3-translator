#include "translator.h"

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

void translator::addFunctions(std::set<std::string> f1, std::set<std::string> f2) {
	for (auto f : f1) { 
		func1.insert(f);  
	}
	for (auto f : f2) {
		func2.insert(f); 
	}
}

void translator::execute(std::string input) {
	// Если ввели команду "end"
	bool isEnd = 1;
	if (input[0] == 'e' && input[1] == 'n' && input[2] == 'd') {
		for (int i = 3; i < input.size(); i++) {
			if (input[i] != ' ') {
				isEnd = 0;
				break;
			}
		}
	}
	else {
		isEnd = 0;
	}
	if (isEnd) {
		isGoing = 0;
		return;
	}

	// Если ввод пустой
	if (input.empty()) {
		std::cout << ("Your input is empty") << std::endl;
		return;
	}

	std::vector<std::pair<std::string, std::string>> lexems;

	/* --- Лексический анализ --- */
	lexiconalysis lex;
	try {
		lexems = lex.analyse(input, variables, constants, func1, func2);
	}
	catch (std::string err) {
		std::cout << "An error has been occured on lexiconalysis part: " << err << std::endl;
		return;
	}
	
	/* --- Синтаксический анализ --- */
	syntanalysis syn;
	try {
		lexems = syn.analyse(lexems, variables, constants, func1, func2);
	}
	catch (std::string err) {
		std::cout << "An error has been occured on syntanalysis part: " << err << std::endl;
		return;
	}
	
	/*
	У нас есть два случая:
	1) вычисляем значение для некоторой переменной
	2) вычисляем значение и выводим его


	Для второго пункта ничего менять не нужно, просто вывести значение.
	Для первого надо убрать из лексем первые два элемента (название переменной и знак равно), а после вместо того,
	чтобы вывести значение, присвоить уже существующей переменной значение/создать новую
	*/
	bool isFloat = 0;
	std::pair<std::string, std::string> newVar; //   Название/значение
	bool type1 = false;
	if (lexems.size() > 1 && lexems[1].first == "equal") {
		type1 = true;
		isFloat = 1;
		newVar.first = lexems[0].second;
		lexems.erase(lexems.begin());
		lexems.erase(lexems.begin());
	}
	
	/* --- Переводим в префиксную форму --- */
	transformator trnsfmtr;
	lexems = trnsfmtr.transform(lexems);
	// Все константы и переменные заменяем на их значения (флоты, потому что) 
	for (int i = 0; i < lexems.size(); i++) {
		if (lexems[i].first == "variable") {
			lexems[i].first = "float";
			std::string vr = variables[lexems[i].second];
			lexems[i].second = vr;
		}
		if (lexems[i].first == "constant") {
			lexems[i].first = "float";
			std::string cs = constants[lexems[i].second];
			lexems[i].second = cs;
		}
	}
	for (int i = 0; i < lexems.size(); i++) {
		if (lexems[i].first == "float" || lexems[i].first == "func1" || lexems[i].first == "func2") {
			isFloat = 1;
			break;
		}
	}
	if (isFloat || type1) {
		for (int i = 0; i < lexems.size(); i++) {
			if (lexems[i].first == "integer") {
				lexems[i].first = "float";
				lexems[i].second += ".0";
			}
		}
	}
	// Про моё решение с интами и флотами в комменте в translator.h написано
	/* --- Вычисляем значение выражения --- */
	calculator calc;
	std::string value;

	try {
		value = calc.calculate(isFloat, lexems);
	}
	catch (std::string err) {
		std::cout << err << std::endl;
		return;
	}

	// Конец
	if (type1) {
		newVar.second = value;
		variables[newVar.first] = newVar.second;
	}
	else {
		std::cout << value << std::endl;
	}
	return;
}