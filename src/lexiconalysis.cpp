#include "lexiconalysis.h"

#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include "functions.h"
#include "translator.h"

std::vector<std::pair<std::string, std::string>> lexiconalysis::analyse(std::string str, std::unordered_map<std::string, std::string> variables, std::unordered_map<std::string, std::string> constants, std::set<std::string> func1, std::set<std::string> func2) {
	// Хранилище для лексем: "тип" - "значение"
	std::vector<std::pair<std::string, std::string>> tokens;  
	
	// c - текущий рассматриваемый символ
	if (str.empty()) {  
		return tokens; 
	}
	// статус отвечает за текущее состояние
	int status = 0;

	/*
	Список состояний:
	0 - пустое состояние
	1 - ввод названия переменной/константы/функции
	2 - ввод числа (целое или целая часть)
	3 - ожидание точки (дробной части)
	4 - ввод дробной части
	5 - одна точка (как 4, но только обязательно получить число)

	6 - ввод аргументов func2
	*/
	int bracketCounter = 0; // Для подсчёта скобок в статусе 6
	std::string value;

	std::string token = ""; 
	for (char c : str) {   
		if (!(c == ' ') && !(characters.count(c)) && !(numbers.count(c)) && !(others.count(c))) { 
			throw std::string("Lexiconalysis error - unknown symbols");
		}

		switch (status) {
		
		/* --- пустое состояние --- */
		case 0: {
			if (c == ' ') {
				status = 0;
				break;
			}
			if (characters.count(c)) {
				status = 1;
				token += c;
				break;
			}
			if (numbers.count(c)) {
				if (c == '0') {
					status = 3;
					token += c;
					break;
				}
				status = 2;
				token += c;
				break;
			}
			if (others.count(c)) {
				if (c == '=') {
					token += c;
					tokens.push_back({ "equal", token }); 
					token = "";
					status = 0;
					break;
				}
				if (c == '.') {
					status = 5;
					token += '0';
					token += '.';
					break;
				}
				if (c == '(') {
					token += c;
					tokens.push_back({ "func1", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ')') {
					token += c;
					tokens.push_back({ "closing bracket", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ',') {
					token += c;
					tokens.push_back({ "comma", token });
					token = "";
					status = 0;
					break;
				}
				token += c;
				tokens.push_back({ "operation", token });
				token = "";
				status = 0;
				break;
			}
			throw std::string("Lexiconalysis error - case 0");
		}
		
		/* --- ввод названия переменной / константы / функции --- */
		case 1: {
			if (c == ' ') {
				if (constants.count(token)) {
					tokens.push_back({ "constant", token });
					token = "";
					status = 0;
					break;
				}
				tokens.push_back({ "variable", token });
				token = "";
				status = 0;
				break;
			}
			if (characters.count(c)) {   
				token += c;
				status = 1;
				break;
			}
			if (numbers.count(c)) {
				token += c;
				status = 1;
				break;
			}
			if (others.count(c)) {
				if (c == '(') {
					token += c;
					if (func1.count(token)) {
						tokens.push_back({ "func1", token });
						token = "";
						status = 0;
						break;
					}
					if (func2.count(token)) {
						tokens.push_back({ "func2", token });
						token = "";
						status = 6;
						bracketCounter = 0;
						break;
					}
					else throw std::string("Lexiconalysis error - case 1");
				}

				if (c == '.') throw std::string("Lexiconalysis error - case 1");

				if (constants.count(token)) {
					tokens.push_back({ "constant", token });
				}
				else {
					tokens.push_back({ "variable", token });
				}

				token = "";
				
				if (c == '=') {
					token += c;
					tokens.push_back({ "equal", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ')') {
					token += c;
					tokens.push_back({ "closing bracket", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ',') {
					token += c;
					tokens.push_back({ "comma", token });
					token = "";
					status = 0;
					break;
				}
				token += c;
				tokens.push_back({ "operation", token });
				token = "";
				status = 0;
				break;
			}
			throw std::string("Lexiconalysis error - case 1");
	}

		/* --- ввод числа(целое или целая часть) --- */
		case 2: {
			if (c == ' ') {
				tokens.push_back({ "integer", token });
				token = "";
				status = 0;
				break;
			}
			if (characters.count(c)) {
				throw std::string("Lexiconalysis error - case 2");
			}
			if (numbers.count(c)) {
				token += c;
				status = 2;
				break;
			}
			if (others.count(c)) {
				if (c == '.') {
					token += c;
					status = 4;
					break;
				}

				tokens.push_back({ "integer", token });
				token = "";

				if (c == '=') {
					token += c;
					tokens.push_back({ "equal", token });
					token = "";
					status = 0;
					break;
				}
				if (c == '(') {
					token += c;
					tokens.push_back({ "func1", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ')') {
					token += c;
					tokens.push_back({ "closing bracket", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ',') {
					token += c;
					tokens.push_back({ "comma", token });
					token = "";
					status = 0;
					break;
				}

				token += c;
				tokens.push_back({ "operation", token });
				token = "";
				status = 0;
				break;
			}
			throw std::string("Lexiconalysis error - case 2");
		}
		/* --- Ожидание точки(дробной части) --- */
		case 3: {

			if (!numbers.count(c) && c != '.') {
				tokens.push_back({ "integer", token });
				token = "";
				if (c == ' ') {
					status = 0;
					break;
				}
				if (characters.count(c)) {
					status = 1;
					token += c;
					break;
				}
				if (others.count(c)) {
					if (c == '=') {
						token += c;
						tokens.push_back({ "equal", token });
						token = "";
						status = 0;
						break;
					}
					if (c == '.') {
						status = 5;
						token += '0';
						token += '.';
						break;
					}
					if (c == '(') {
						token += c;
						tokens.push_back({ "func1", token });
						token = "";
						status = 0;
						break;
					}
					if (c == ')') {
						token += c;
						tokens.push_back({ "closing bracket", token });
						token = "";
						status = 0;
						break;
					}
					if (c == ',') {
						token += c;
						tokens.push_back({ "comma", token });
						token = "";
						status = 0;
						break;
					}
					token += c;
					tokens.push_back({ "operation", token });
					token = "";
					status = 0;
					break;
				}
				break;
			}
			if (c == '.') {
				token += c;
				status = 4;
				break;
			}
			throw std::string("Lexiconalysis error - case 3");
		}
		/* --- Ввод дробной части-- - */
		case 4: {
			if (c == ' ') {
				token += '0';
				tokens.push_back({ "float", token });
				token = "";
				status = 0;
				break;
			}
			if (characters.count(c)) {
				throw std::string("Lexiconalysis error - case 4");
			}
			if (numbers.count(c)) {
				token += c;
				status = 4;
				break;
			}
			if (others.count(c)) {
				if (c == '.') {
					throw std::string("Lexiconalysis error - case 4");
				}
				
				tokens.push_back({ "float", token }); 
				token = "";
				
				if (c == '=') {
					token += c;
					tokens.push_back({ "equal", token });
					token = "";
					status = 0;
					break;
				}
				if (c == '(') {
					token += c;
					tokens.push_back({ "func1", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ')') {
					token += c;
					tokens.push_back({ "closing bracket", token });
					token = "";
					status = 0;
					break;
				}
				if (c == ',') {
					token += c;
					tokens.push_back({ "comma", token });
					token = "";
					status = 0;
					break;
				}

				token += c;
				tokens.push_back({ "operation", token });
				token = "";
				status = 0;
				break;
			}
			throw std::string("Lexiconalysis error - case 4");
		}
		/* --- Проверка на то, чтобы не была введена только одна точка без цифр --- */
		case 5: {
			if (numbers.count(c)) {
				token += c;
				status = 4;
				break;
			}
			throw std::string("Lexiconalysis error - case 5");
		}

		/* --- Ввод аргументов func2 --- */
		case 6: {

			// Если ввод аргумента закончен, то вычисляем его значение
			if (((c == ',' || c == ')') && bracketCounter == 0) || bracketCounter < 0) {
				translator tr;
				tr.constants = constants;
				tr.variables = variables;
				tr.func1 = func1;
				tr.func2 = func2;

				try {
					//std::cout << token << std::endl;
					value = tr.execute(token);
				}
				catch (std::string err) {
					throw std::string("recursion error: " + err);
				}

				if (tr.isVar) {
					throw std::string("Lexiconalysis error - recursion error");
				}

				tokens.push_back({"float", value});
				if (c == ')') {
					tokens.push_back({"closing bracket", ")"});
					status = 0;
					bracketCounter = 0;
				}
				else {
					tokens.push_back({ "comma", "," });
					status = 6;
					bracketCounter = 0;
				}

				token = "";
				break;
			}
			// Все следующие вводимые значения будут частью выражения, к которому мы применим translator (т.е. рекурсивно их вычислим)
			else {
				status = 6;
				token += c;
				if (c == '(') bracketCounter++;
				else if (c == ')') bracketCounter--;
				break;
			}
		}

		// Вроде бы нет ситуаций, когда не подходит ни один case, но хуже от добавления этого не будет
		default:
			throw std::string("Lexiconalysis error");
		}
	}

	// Цикл может закончится до того, как токен добавлен в список лексем
	if (!token.empty()) {
		if (status == 6) {
			throw std::string("Lexiconalysis error - unexpected end of input");
		}
		if (token == "0") {
			tokens.push_back({ "integer", token });
		}
		else if (status == 1) { 
			if (constants.count(token)) {
				tokens.push_back({ "constant", token });
			}
			else {
				tokens.push_back({ "variable", token });
			}
		}
		else if (status == 2) { 
			tokens.push_back({ "integer", token });
		}
		else if (status == 4) { 
			tokens.push_back({ "float", token + '0'});
		}
		else {
			throw std::string("Lexiconalysis error - unexpected end of input");
		}
	}

	return tokens; 
}