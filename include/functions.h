# pragma once

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
 
class functions {
public:
	/*
	��� ���������� ����� �������:
	1) �������� �� � set, ������� �����, ����� ���������� ���� � ������������� ���� �������
	2) �������� ���������� ������� � cpp � h �����
	3) �������� � solveFunc
	������
	*/

	// ������ ������� ��������� ��� ����, ����� ������, ��� ���������� ����� �������
	std::set<std::string> func1 = { "(", "sin(", "cos(" };
	std::set<std::string> func2 = { "max(", "min(" };


	/*
	������� ������� �� ��� ����
	func1 - �������� ���������, ���������� ��������. ��������� ����� ���� ����� ������ �������, ��������, ��� ������: sin(Pi/2 - 12 * (max(1, 2, 3))

	func2 - �������� ��������� �������� ����� �������. ���� ��� ��������� ������������� ��������� �������� (float, integer, constant � variable) ����� �������.
	�.�. ���� �������� -3.0 �� ����� ���� ������������ � ����� �������, �.�. ����� ������������ ������� �����. 
	����� ������ ���������� ����������, ��� ������ ��������� ������ ������� ����� ������������� ������
	����
	������: max(Pi, 1, 2, 3, 8)
	*/

	// ������� ������� ����
	std::string solveFunc1(std::string value, std::string function);

	float myBracket(float value);

	float mySin(float value);

	float myCos(float value);

	// ������� ������� ����
	std::string solveFunc2(std::vector<std::string> value, std::string function);

	float myMax(std::vector<float> values);

	float myMin(std::vector<float> values);
	
};