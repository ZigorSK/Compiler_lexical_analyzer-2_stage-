#pragma once
#include<string>
#include<fstream>
#include<vector>
#include<iostream>
using namespace std;

class Scaner
{
	vector <string> KW_vector;//������ �������� ����
	vector <string> DIVIDER_vector;//������ ������������
	ifstream in_main;//��������� �� ���� � ������� �����

public:
	Scaner();

	bool try_KW(string &A);
};