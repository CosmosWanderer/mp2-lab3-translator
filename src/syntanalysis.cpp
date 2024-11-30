#include "syntanalysis.h"

#include <unordered_map>
#include <string>
#include <set>
#include <vector>

#include "functions.h"


std::vector<std::pair<std::string, std::string>> syntanalysis::analyse(std::vector<std::pair<std::string, std::string>> lexems, std::unordered_map<std::string, std::string> variables, std::unordered_map<std::string, std::string> constants, std::set<std::string> func1, std::set<std::string> func2) {
	std::vector<std::pair<std::string, std::string>> copyLexems = lexems;
	if (lexems.empty()) return lexems;

	int pntr = -1;
	if (lexems.size() > 1 && lexems[0].first == "variable" && lexems[1].first == "equal") {
		pntr += 2;
		lexems.erase(lexems.begin());
		lexems.erase(lexems.begin());
		if (!lexems.size()) throw std::string("Syntanalysis error - equal-error");
	}

	/*	
	Если ввод начинается с (variable =), то скипаем эти две лексемы и идём проверять дальше
	При этом, знак = не может встречаться нигде больше


	Первое число отвечает за текущий статус:
	0 - ожидаем переменную, константу, число, функцию
	1 - ожидаем операцию (+, -, *, /) или закрывающую скобку. Также не пустое выражение заканчивается на этом состоянии
	
	2 - внутри func2, ожидаем выражение
	3 - внутри func2, ожидаем запятую или закрывающую скобку

	Второе число отвечает за количество ожидаемых закрывающихся скобок.
	При появлении функции ("sin(", "fact(", т.д., важно - "(" тоже считается функцией) число увеличивается, при появлении ")" - уменьшается.
	Оно не может стать меньше 0, в конце проверки оно должно быть равно 0


	Функции делятся на два типа:
	тип 1: func1( выражение ) пример: fact(2 + 1 / 8)
	тип 2: func2(значение, значение..) пример max(Pi, 1, 3, variable)

	Если пришла функция типа один, то просто добавляем ко второму числу 1.
	
	Если пришла функция типа два, то ожидаем последовательный ввод переменной/числа/константы и запятой, пока не придёт закрывающая скобка. 
	Ввод не может начинаться или заканчиваться с запятой. Такие дела
	
	*/

	std::set<std::string> znacheniya = {
		"integer", "float", "variable", "constant"
	};

	// Проверяем, чтобы у всех переменных/констант были заданны значения
	for (std::pair<std::string, std::string> token : lexems) {
		if (token.first == "variable" && !(variables.count(token.second))) {
			throw std::string("Syntanalysis error - variables error");
		}
		if (token.first == "constant" && !(constants.count(token.second))) {
			throw std::string("Syntanalysis error - constants error");
		}
	}

	std::pair<int, int> status = { 0, 0 };

	
	for (std::pair<std::string, std::string> token : lexems) {
		pntr++;
		std::string type = token.first;

		switch (status.first) {
		
		/* --- Ожидаем какое-нибудь значение --- */
		case 0: {
			if (znacheniya.count(type)) {
				status.first = 1;
				break;
			}
			if (type == "func1") {
				status.second++;
				status.first = 0;
				break;
			}
			if (type == "func2") {
				status.first = 2;
				break;
			}
			// Унарный плюс/минус
			if (token.second == "+" || token.second == "-") {
				// Нужно отметить, что это унарная операция
				copyLexems[pntr].second += "u";
				status.first = 0;
				break;
			}
			throw std::string("Syntanalysis error - case 0");
		}
		/* --- Ожидаем знак + , -, *, / , или закрывающую скобку --- */
		case 1: {
			if (type == "operation") {
				status.first = 0;
				break;
			}
			if (type == "closing bracket") {
				status.second--;
				status.first = 1;
				break;
			}
			throw std::string("Syntanalysis error - case 1");
		}
		/* --- Че-то там для функций второго типа --- */
		case 2: {
			if (znacheniya.count(type)) {
				status.first = 3;
				break;
			}
			throw std::string("Syntanalysis error - case 2");
		}
		/* --- И ещё --- */
		case 3: {
			if (type == "comma") {
				status.first = 2;
				break;
			}
			if (type == "closing bracket") {
				status.first = 1;
				break;
			}
			throw std::string("Syntanalysis error - case 3");
		}
		default: {
			throw std::string("Syntanalysis error");
		}
		}

		// Закрывающих скобок больше, чем открывающих
		if (status.second < 0) throw std::string("Syntanalysis error - bracket error 1");
	}
	// Не все скобки закрыли
	if (status.second != 0) throw std::string("Syntanalysis error - bracket error 2");
	// Неверный конец выражения
	if (status.first != 1) throw std::string("Syntanalysis error - unexpected ending");

	// Если нигде не словили throw, то всё норм
	
	// Вообще, изначально функция не должна была ничего менять, но времена изменились, когда я стал пытаться работать с унарными операциями
	return copyLexems;
}