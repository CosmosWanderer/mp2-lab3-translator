#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <cmath>

#include "translator.h"

int main() {
 
	translator tr;

	// Creating constants
	tr.constants.insert({ "Pi", "3.14159265359" }); 
	tr.constants.insert({ "e", "2.7182"});

	// Inserting functions from functions.h
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2; 
	tr.addFunctions(f1, f2);

	// Mini-user-guide
	std::cout << "Potashnink Maxim mp2-lab3-translator" << std::endl <<
		"There are two types of funtions: func1 (1 argument), func2 (multiple arguments)" << std::endl <<
		"func1: "; 
	for (auto f : f1) std::cout << f << ", ";
	std::cout << std::endl << "example: sin(Pi / 2), cos(1 - sin(3 * Pi / 2))" << std::endl <<
		"func2: ";
	for (auto f : f2) std::cout << f << ", ";
	std::cout << std::endl << "example: max(1, 2, 3), min(Pi * 3, sin(Pi), -2), max(max(max(1, 2, 3), 4), 5)" << std::endl;
	std::cout << "Enter 'end' to close the program" << std::endl; 

	// Program cycle
	std::string input;
	std::string output;
	while (tr.isGoing) {

		// tr.execute(..) gets input string, either returns output value, or creates/changes variable. If something is wrong, throws exception 
		// command "end" ends program cycle 

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







