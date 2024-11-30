#include "translator.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>

#include "lexiconalysis.h"
#include "syntanalysis.h"
#include "functions.h"
#include "transformator.h"
#include "calculator.h"

void translator::addFunctions(std::set<std::string> f1, std::set<std::string> f2) {
	for (auto f : f1) { 
		func1.insert(f);  
	}
	for (auto f : f2) {
		func2.insert(f); 
	}
}

std::string translator::execute(std::string input) {
	// ���� ����� ������� "end"
	bool isEnd = 1;
	if (input[0] == 'e' && input[1] == 'n' && input[2] == 'd') {
		for (int i = 3; i < input.size(); i++) {
			if (input[i] != ' ') {
				isEnd = 0;
				break;
			}
		}
	}
	else {
		isEnd = 0;
	}
	if (isEnd) {
		isGoing = 0;
		return std::string("Translation is over");
	}

	// ���� ���� ������
	if (input.empty()) {
		return std::string("Input is empty");
	}

	std::vector<std::pair<std::string, std::string>> lexems; 

	/* --- ����������� ������ --- */
	lexiconalysis lex;
	try {
		lexems = lex.analyse(input, variables, constants, func1, func2);
	}
	catch (std::string err) { // const char*
		throw std::string("An error has been occured on lexiconalysis part: " + err);
	}
	
	/* --- �������������� ������ --- */
	syntanalysis syn;
	try {
		lexems = syn.analyse(lexems, variables, constants, func1, func2);
	}
	catch (std::string err) {
		throw std::string("An error has been occured on syntanalysis part: " + err);
	}
	
	/*
	� ��� ���� ��� ������:
	1) ��������� �������� ��� ��������� ����������
	2) ��������� �������� � ������� ���


	��� ������� ������ ������ ������ �� �����, ������ ������� ��������.
	��� ������� ���� ������ �� ������ ������ ��� �������� (�������� ���������� � ���� �����), � ����� ������ ����,
	����� ������� ��������, ��������� ��� ������������ ���������� ��������/������� �����
	*/
	std::pair<std::string, std::string> newVar; //��������/��������
	bool type1 = false;
	if (lexems.size() > 1 && lexems[1].first == "equal") {
		type1 = true;
		newVar.first = lexems[0].second;
		lexems.erase(lexems.begin());
		lexems.erase(lexems.begin());
	}
	/* --- ��������� � ���������� ����� --- */
	transformator trnsfmtr;
	lexems = trnsfmtr.transform(lexems);

	// ��� ��������� � ���������� �������� �� �� �������� 
	for (int i = 0; i < lexems.size(); i++) {
		if (lexems[i].first == "variable") {
			lexems[i].first = "float";
			std::string vr = variables[lexems[i].second];
			lexems[i].second = vr;
		}
		if (lexems[i].first == "constant") {
			lexems[i].first = "float";
			std::string cs = constants[lexems[i].second];
			lexems[i].second = cs;
		}
	}
	// �������, ��� ����� �� ������ �������. � ����� �� ������� ��������� �������, ������� ��������� ���� ���������� � ������, �.�. ��� ����� ����� ������������, �� ������ �������� ��� ���� �� �����
	for (int i = 0; i < lexems.size(); i++) {
		if (lexems[i].first == "integer") {
			lexems[i].first = "float";
			lexems[i].second += ".0";
		}
	}
	/* --- ��������� �������� ��������� --- */
	calculator calc;
	std::string value;
	try {
		value = calc.calculate(lexems);
	}
	catch (std::string err) {
		throw std::string("An error has been occured on calculation part : " + err);
	}
	
	// �����
	if (type1) {
		newVar.second = value;
		variables[newVar.first] = newVar.second;
		return std::string("Variable " + newVar.first + " set with value " + newVar.second);
	}
	return value;
}