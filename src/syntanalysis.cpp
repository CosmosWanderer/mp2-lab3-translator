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
	���� ���� ���������� � (variable =), �� ������� ��� ��� ������� � ��� ��������� ������
	��� ����, ���� = �� ����� ����������� ����� ������


	������ ����� �������� �� ������� ������:
	0 - ������� ����������, ���������, �����, �������
	1 - ������� �������� (+, -, *, /) ��� ����������� ������. ����� �� ������ ��������� ������������� �� ���� ���������
	
	2 - ������ func2, ������� ���������
	3 - ������ func2, ������� ������� ��� ����������� ������

	������ ����� �������� �� ���������� ��������� ������������� ������.
	��� ��������� ������� ("sin(", "fact(", �.�., ����� - "(" ���� ��������� ��������) ����� �������������, ��� ��������� ")" - �����������.
	��� �� ����� ����� ������ 0, � ����� �������� ��� ������ ���� ����� 0


	������� ������� �� ��� ����:
	��� 1: func1( ��������� ) ������: fact(2 + 1 / 8)
	��� 2: func2(��������, ��������..) ������ max(Pi, 1, 3, variable)

	���� ������ ������� ���� ����, �� ������ ��������� �� ������� ����� 1.
	
	���� ������ ������� ���� ���, �� ������� ���������������� ���� ����������/�����/��������� � �������, ���� �� ����� ����������� ������. 
	���� �� ����� ���������� ��� ������������� � �������. ����� ����
	
	*/

	std::set<std::string> znacheniya = {
		"integer", "float", "variable", "constant"
	};

	// ���������, ����� � ���� ����������/�������� ���� ������� ��������
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
		
		/* --- ������� �����-������ �������� --- */
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
			// ������� ����/�����
			if (token.second == "+" || token.second == "-") {
				// ����� ��������, ��� ��� ������� ��������
				copyLexems[pntr].second += "u";
				status.first = 0;
				break;
			}
			throw std::string("Syntanalysis error - case 0");
		}
		/* --- ������� ���� + , -, *, / , ��� ����������� ������ --- */
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
		/* --- ��-�� ��� ��� ������� ������� ���� --- */
		case 2: {
			if (znacheniya.count(type)) {
				status.first = 3;
				break;
			}
			throw std::string("Syntanalysis error - case 2");
		}
		/* --- � ��� --- */
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

		// ����������� ������ ������, ��� �����������
		if (status.second < 0) throw std::string("Syntanalysis error - bracket error 1");
	}
	// �� ��� ������ �������
	if (status.second != 0) throw std::string("Syntanalysis error - bracket error 2");
	// �������� ����� ���������
	if (status.first != 1) throw std::string("Syntanalysis error - unexpected ending");

	// ���� ����� �� ������� throw, �� �� ����
	
	// ������, ���������� ������� �� ������ ���� ������ ������, �� ������� ����������, ����� � ���� �������� �������� � �������� ����������
	return copyLexems;
}