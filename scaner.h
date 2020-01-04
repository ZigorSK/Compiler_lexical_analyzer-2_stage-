#pragma once
#include"AllStruct.h"
#include<string>
#include<fstream>
#include<vector>
#include<iostream>
#include<iomanip>
using namespace std;

class Scaner
{
	ifstream in_main;//��������� �� ���� � ������� �����

	All_KeyWords table_of_keyWords;//��� �������� �����, �������� table_of_keyWords == string obg ���������� true, ���� � ������� ���� ����� �����
	All_Dividers table_of_dividers;//��� �����������, �������� table_of_dividers == string obg ���������� true, ���� � ������� ���� ����� �����������

	Table <Token> stream_of_token;//������� ������ ������(��������� stream_of_token[i]). ��������  stream_of_token += Token ��������� � ������� �����
	Table <Identifier> table_of_identifier;//������� ID(��������� table_of_identifier[i]). ��������  table_of_identifier += Identifier ��������� � ������� �����
	Table <Constant> table_of_constant;//������� ��������. (��������� table_of_constant[i]). ��������  table_of_constant += Constant ��������� � ������� ���������

	char keeper_last_char;//������, �������� ��������� ����������� ������ ������� get_lex

public:
	Scaner();//��������� �������-��������� �� ����, �������� �����
	~Scaner();// �������� �����

	string get_lex();//��������� ��������� �������
	bool delete_coment(char c1, char c2);//�������� �����������, ���� ���������� ��� ����� ���������� true, ����� false

	Scaner & to_scan();//�������� ������ ������ � ������ ID and Const

	All_KeyWords &get_table_of_keyWords()			{ return table_of_keyWords;	 };
	All_Dividers &get_table_of_dividers()			{ return table_of_dividers; };

	Table <Token> &get_stream_of_token()			{ return stream_of_token; };
	Table <Identifier> &get_table_of_identifier()	{ return table_of_identifier; };
	Table <Constant> &get_table_of_constant()		{ return table_of_constant;	};

	void print_stream_of_lex();
	void print_another_table();
};