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
	// ������� �������� �� �����/������ functions. ��� ���������� ����� �������, ����� ������� ����
	std::set<std::string> func1; 
	std::set<std::string> func2; 

	// ��� ��������� ������������� ��������, � �����, ��� ��� ����������/��������� - float
	std::unordered_map <std::string, std::string> variables;
	std::unordered_map <std::string, std::string> constants;
	// � ��� � �����, ��� ���� ������� �������, ��� ���� ���-�� float, (� �. �. ���������� ��� ���������), �� ��� �������� ���������� � ����������, �� ������ ������ �� - float. 
	// ���, ��������, �������, �� � ��, ��� ����, � ���� �� ����� �� ��� ���������� �� ���� � �����
	// ��, �.�., � ���� ���������� ���������� �� ���� � �����? ����������. � ��� �� �������� ����� ��� �� ���������� ����������� ����� ������� ��������� �� ������

	// ����� ���� �������� �� ������� ������� �����, �� � ������� ��������� ��� ������ ������
	bool isGoing = 1;  

	// ���������� ������� � ������ �������. ������ ������� ���� �� ������������� ����� functions.h
	void addFunctions(std::set<std::string> f1, std::set<std::string> f2);

	// �������� ������, ������� ����� ��� ������ ���������� � ���������� ���������, �� ��� ������� ������ � ������ �� ������
	std::string execute(std::string input);
};
