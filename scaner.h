#pragma once
#include<string>
#include<fstream>
#include<vector>
#include<iostream>
using namespace std;

class Scaner
{
	vector <string> KW_vector;//Вектор Ключевых слов
	vector <string> DIVIDER_vector;//Вектор разделителей
	ifstream in_main;//Указатель на файл с иходным кодом

public:
	Scaner();

	bool try_KW(string &A);
};