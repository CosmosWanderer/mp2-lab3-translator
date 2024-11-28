#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <cmath>

#include "translator.h"

int main() {
 
	translator tr;

	// Задаём константы
	tr.constants.insert({ "Pi", "3.14159265359" }); 
	tr.constants.insert({ "e", "2.7182"});

	// Задаём функции
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	// Цикл программы
	while (tr.isGoing) {
		std::string S;
		std::getline(std::cin, S);
		tr.execute(S); 
	}

	return 0;
}







