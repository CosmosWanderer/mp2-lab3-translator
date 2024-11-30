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

	// Задаём функции из заголовочного файла functions.h
	// Гайд на быстрое добавление новых функций в файле functions.h
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2; 
	tr.addFunctions(f1, f2);

	// Цикл программы
	std::string input;
	std::string output;
	while (tr.isGoing) {

		// tr.execute(..) получает на вход строку, возвращает знаение выражения, либо задаёт переменную по входным данным. Если что-то не так, бросает исключение
		// команда "end" заканчивает цикл программы

		std::getline(std::cin, input);
		try {
			output = tr.execute(input);
			std::cout << output << std::endl;
		}
		catch (std::string err) {
			std::cout << err << std::endl;
		}
	}

	return 0;
}







