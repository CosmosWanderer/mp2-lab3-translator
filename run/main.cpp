#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <cmath>

#include "translator.h"

int main() {
 
	translator tr;

	// ����� ���������
	tr.constants.insert({ "Pi", "3.14159265359" }); 
	tr.constants.insert({ "e", "2.7182"});

	// ����� ������� �� ������������� ����� functions.h
	// ���� �� ������� ���������� ����� ������� � ����� functions.h
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2; 
	tr.addFunctions(f1, f2);

	// ���� ���������
	std::string input;
	std::string output;
	while (tr.isGoing) {

		// tr.execute(..) �������� �� ���� ������, ���������� ������� ���������, ���� ����� ���������� �� ������� ������. ���� ���-�� �� ���, ������� ����������
		// ������� "end" ����������� ���� ���������

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







