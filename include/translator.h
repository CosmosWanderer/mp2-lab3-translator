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
	// Функции задаются из файла/класса functions. Для добавления новых функций, нужно перейти туда
	std::set<std::string> func1; 
	std::set<std::string> func2; 

	// Для упрощения мыслительного процесса, я решил, что все переменные/константы - float
	std::unordered_map <std::string, std::string> variables;
	std::unordered_map <std::string, std::string> constants;
	// И ещё я решил, что если имеются функции, или хоть что-то float, (в т. ч. переменная или константа), ну или значение записываем в переменную, то делаем вообще всё - float. 
	// Это, наверное, неверно, но я хз, как надо, а лаба всё равно не про разделение на инты и флоты
	// Ну, т.е., я ведь реализовал разделение на инты и флоты? Реализовал. А как бы поменять потом это на правильную расстановку труда особого составить не должно

	// Можно было заменить на внешнюю булевую штуку, но я захотел запихнуть это внутрь класса
	bool isGoing = 1;  

	// Добавление функций в список функций. Список функций берём из заголовочного файла functions.h
	void addFunctions(std::set<std::string> f1, std::set<std::string> f2);

	// Получаем строку, выводим ответ или создаём переменную с полученным значением, ну или выводим ошибку и ничего не делаем
	std::string execute(std::string input);
};
