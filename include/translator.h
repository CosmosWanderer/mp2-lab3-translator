#pragma once

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

class translator { 
public:
	// Used for func2 counting
	bool recErr = 0;

	// Use addFunction on function-lists from functions.h
	std::set<std::string> func1; 
	std::set<std::string> func2; 

	std::unordered_map <std::string, std::string> variables;
	std::unordered_map <std::string, std::string> constants;
	
	// I dont want to translate this
	// � ��� � �����, ��� ���� ������� �������, ��� ���� ���-�� float, (� �. �. ���������� ��� ���������), �� ��� �������� ���������� � ����������, �� ������ ������ �� - float. 
	// ���, ��������, �������, �� � ��, ��� ����, � ���� �� ����� �� ��� ���������� �� ���� � �����
	// ��, �.�., � ���� ���������� ���������� �� ���� � �����? ����������. � ��� �� �������� ����� ��� �� ���������� ����������� ����� ������� ��������� �� ������

	// For breaking program cycle
	bool isGoing = 1;  

	// Adding functions from functions.h
	void addFunctions(std::set<std::string> f1, std::set<std::string> f2);

	// Get string, return answer or create variable, or throw exception
	std::string execute(std::string input);
};
