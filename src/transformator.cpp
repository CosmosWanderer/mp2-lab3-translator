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

		/* --- �������� �� ���� ����� (��� �������) --- */
		if (znacheniya.count(type) || type == "comma") {
			result.push_back(token);
		}
		
		/* --- �������� �� ���� �������� --- */
		else if (type == "operation") {
			
			// ���� ���� ������/����� �������� � ������� �����������/� ����� func1, �� ����� �������� � ����
			if (S.size() == 0 || ((S.top().second == "-" || S.top().second == "+") && (token.second == "/" || token.second == "*")) || 
				((S.top().second == "-" || S.top().second == "+" || S.top().second == "/" || S.top().second == "*") && (token.second == "-u" || token.second == "+u")) || S.top().first == "func1") {
				S.push(token);
			}

			// ���� � ������ ����� ������� �������� ��� ������� ����������, �� ���������� �� ����� � ����� �� ��� ���, ���� ��� �� ����� ����������
			else {
				// ���� ����������� ��� *, / � +, - ��������, �.�. ���� ��������� � ������������
				if (token.second == "u-" || token.second == "u+") {
					while (!(S.size() == 0 || S.top().second == "*" || S.top().second == "/" || S.top().second == "-" || S.top().second == "+" || S.top().first == "func1")) {
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

		/* --- �������� �� ���� func1 (� ��� ����� ������������ ������) --- */
		else if (type == "func1") {
			S.push(token);
		}

		/* --- �������� �� ���� func2 --- */
		else if (type == "func2") {
			// �� ����, ������� � ���������� �����������
			S.push(token);
		}

		/* --- �������� ����������� ������ --- */
		else {
			// ���������� �� � ���������, ���� �� �������� func1 ��� func2, �� ���� � ���������
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