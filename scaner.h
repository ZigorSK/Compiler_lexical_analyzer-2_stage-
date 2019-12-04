#pragma once
#include"AllStruct.h"
#include<string>
#include<fstream>
#include<vector>
#include<iostream>
using namespace std;

class Scaner
{
	ifstream in_main;//��������� �� ���� � ������� �����

	All_KeyWords table_of_keyWords;//��� �������� �����, �������� table_of_keyWords == string obg ���������� true, ���� � ������� ���� ����� �����
	All_Dividers table_of_dividers;//��� �����������, �������� table_of_dividers == string obg ���������� true, ���� � ������� ���� ����� �����������

	Table <Token> stream_of_token;//������� ������ ������(��������� stream_of_token[i]). ��������  stream_of_token += Token ��������� � ������� �����
	Table <Identifier> table_of_identifier;//������� ID(��������� table_of_identifier[i]). ��������  table_of_identifier += Identifier ��������� � ������� �����
	Table <Constant> table_of_constant;//������� ��������. (��������� table_of_constant[i]). ��������  table_of_constant += Constant ��������� � ������� ���������
public:
	Scaner();//��������� �������-��������� �� ����, �������� �����
	~Scaner();// �������� �����

	string get_lex();//��������� ��������� �������

	bool try_KeyWord(string &A);//�������� �������� �� ������� �������� ������
	bool try_Divider(string &A);//�������� �������� �� ������� ������������
};