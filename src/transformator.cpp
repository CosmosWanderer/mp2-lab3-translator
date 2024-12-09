#include "transformator.h"

#include <iostream> 
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include <queue>

#include "functions.h"

std::vector<std::pair<std::string, std::string>> transformator::transform(std::vector<std::pair<std::string, std::string>> lexems) {
	
	std::stack <std::pair<std::string, std::string>> S;
	std::vector <std::pair<std::string, std::string>> result;

	std::set<std::string> znacheniya = {
		"integer", "float", "constant", "variable"
	};

	for (std::pair<std::string, std::string> token : lexems) {
		std::string type = token.first;

		/* --- Number (or comma) --- */
		if (znacheniya.count(type) || type == "comma") {
			result.push_back(token);
		}
		
		/* --- Operation --- */
		else if (type == "operation") {
			
			// Staack is empty/placing operation with higher prioruty/func1 in stack, the push operation in the stack
			if (S.size() == 0 || ((S.top().second == "-" || S.top().second == "+") && (token.second == "/" || token.second == "*")) || 
				((S.top().second == "-" || S.top().second == "+" || S.top().second == "/" || S.top().second == "*") && (token.second == "-u" || token.second == "+u")) || S.top().first == "func1") {
				S.push(token);
			}

			// Если в сверху лежит функция меньшего или равного приоритета, то перемещаем из стека в ответ до тех пор, пока это не будет исправлено
			// Shortly speaking: ELSE:
			else {
				// Checking *, / and +, - separatly cuz of priorities
				if (token.second == "-u" || token.second == "+u") {
					while (!(S.size() == 0 || S.top().second == "-u" || S.top().second == "+u" || S.top().second == "*" || S.top().second == "/" || S.top().second == "-" || S.top().second == "+" || S.top().first == "func1")) {
						result.push_back(S.top());
						S.pop();
					}
					S.push(token);
				}
				else if (token.second == "*" || token.second == "/") {
					while (!(S.size() == 0 || S.top().second == "-" || S.top().second == "+" || S.top().first == "func1")) {
						result.push_back(S.top());
						S.pop();
					}
					S.push(token);
				}
				else {
					while (!(S.size() == 0 || S.top().first == "func1")) {
						result.push_back(S.top());
						S.pop();
					}
					S.push(token);
				}
			}
		}

		/* --- func1 --- */
		else if (type == "func1") {
			S.push(token);
		}

		/* --- func2 --- */
		else if (type == "func2") {
			S.push(token);
		}

		/* --- closing bracket --- */
		else {
			while (S.top().first != "func1" && S.top().first != "func2") {
				result.push_back(S.top());
				S.pop();
			}
			result.push_back(S.top());
			S.pop();
		}
	}
	
	while (!S.empty()) {
		result.push_back(S.top());
		S.pop();
	}

	return result;
}