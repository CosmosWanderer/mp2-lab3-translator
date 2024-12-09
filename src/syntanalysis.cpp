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
	If input begins with "variable =", then skip those lexems


	First number - current state:
	0 - expect variable, constant, number, function
	1 - expect operation (+, -, *, /) or closing bracket. Also, not empty input must end on this state
	
	2 - inside func2, expect an expression
	3 - inside func2, expect a comma or closing bracket

	The second number is responsible for the number of expected closing brackets.
	When a function ("sin(", "fact(", etc., it is important - "(" is also considered a function) appears, the number increases, when ")" appears, the number decreases.
	It cannot become less than 0, at the end it must be equal to 0

	Functions are divided into two types:
	type 1: func1( expression ) example: fact(2 + 1 / 8)
	type 2: func2(value, value..) example max(Pi, 1, 3, variable)

	If a function of type one arrives, then we simply add 1 to the second number.

	If a function of type two arrives, then we wait for the sequential input of a variable/number/constant and a comma until the closing bracket arrives.
	The input cannot begin or end with a comma.
	
	*/

	std::set<std::string> znacheniya = {
		"integer", "float", "variable", "constant"
	};

	// Checking the existance of all constants/variables
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
		
		/* --- Expecting value --- */
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
			// u+/u-
			if (token.second == "+" || token.second == "-") {
				copyLexems[pntr].second += "u";
				status.first = 0;
				break;
			}
			throw std::string("Syntanalysis error - case 0");
		}
		/* --- Expecting + , -, *, / , or ) --- */
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
		/* --- func2 --- */
		case 2: {
			if (znacheniya.count(type)) {
				status.first = 3;
				break;
			}
			throw std::string("Syntanalysis error - case 2");
		}
		/* --- more func2 --- */
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

		// too much closing brackets
		if (status.second < 0) throw std::string("Syntanalysis error - bracket error 1");
	}
	// not all brackets are closed
	if (status.second != 0) throw std::string("Syntanalysis error - bracket error 2");
	// bad end of input
	if (status.first != 1) throw std::string("Syntanalysis error - unexpected ending");

	// Useless rant	
	// ¬ообще, изначально функци€ не должна была ничего мен€ть, но времена изменились, когда € стал пытатьс€ работать с унарными операци€ми
	return copyLexems;
}