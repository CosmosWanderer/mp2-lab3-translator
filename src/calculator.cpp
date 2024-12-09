#include "calculator.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include <float.h>
#include <cmath>

#include "functions.h"

std::string calculator::calculate(std::vector<std::pair<std::string, std::string>> postfixForm) {
	std::stack<std::pair<std::string, std::string>> S;
	functions f;

	
	for (std::pair<std::string, std::string> token : postfixForm) {
		/* --- Number --- */
		if (token.first == "float") {
			S.push(token);
		}
		/* --- Comma (for func2) --- */
		else if (token.first == "comma") {
			S.push(token);
		}
		/* --- Operation --- */
		else if (token.first == "operation") {
			// For unar plus and minus
			if (token.second.size() > 1) {
				float resValue = 0;
				float a = std::stof(S.top().second);
				if (token.second == "+u") {
					resValue += a;
				}
				else {
					resValue -= a;
				}
				S.pop();
				S.push({ "float", std::to_string(resValue) });
			}
			else {

				float resValue;
				float a = std::stof(S.top().second);
				S.pop();
				float b = std::stof(S.top().second);
				S.pop();
				if (token.second == "+") {
					resValue = b + a;
				}
				else if (token.second == "-") {
					resValue = b - a;
				}
				else if (token.second == "*") {
					resValue = b * a;
				}
				else {
					if (abs(a) <= FLT_EPSILON) {
						throw std::string("Division by zero");
					}
					resValue = b / a;
				}
				S.push({ "float", std::to_string(resValue) });
			}
		}
		/* --- func1 --- */
		else if (token.first == "func1") {
			std::string resValue = f.solveFunc1(S.top().second, token.second);
			S.pop();
			S.push({ "float", resValue });
		}
		/* --- func2 (they need vector of arguments) --- */
		else if (token.first == "func2") {
			std::vector<std::string> values;
			values.push_back(S.top().second);
			S.pop();
			while (!S.empty() && S.top().first == "comma") {
				S.pop();
				values.push_back(S.top().second);
				S.pop();
			}
			std::string resValue = f.solveFunc2(values, token.second);
			S.push({ "float", resValue });
		}
	}

	

	// Just deleting all unnecessary zeroes
	std::string value = S.top().second;
	
	bool canFix = 0;
	for (char s : value) {
		if (s == '.') {
			canFix = 1;
			break;
		}
	}
	if (canFix) {
		for (int i = value.length() - 1; i > 1; i--) {
			if (value[i] == '0' && value[i - 1] == '0') {
				value.pop_back();
			}
			else {
				break;
			}
		}
	}

	// Lets just leave it here, I believe, it wont hurt anybody
	if (value == "-0.0") {
		value = "0.0";
	}
	else if (value == "-0") {
		value = "0";
	}

	
	return value;
}


