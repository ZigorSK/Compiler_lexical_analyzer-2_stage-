#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

enum {KEYWORD, DIVIDER, IDENTIFIER, CONSTANT, END_OF_PROGRAMM, ERROR};

class Token//1 Лексема
{
	string name;
	int type;//1-ID; 2- KEYWORD; 3 -DIVIDER; 4-CONSTANT.
public:
	Token(string &NAME, int TYPE);
	Token(const Token &obg);

	void set_name(string &N) { name = N; };
	string &get_name() { return name; };

	void set_type(int N) { type = N; };
	int get_type() { return type; };
};

class Identifier
{
	string name;
public:
	Identifier(string &NAME) { name = NAME; };
	Identifier(const Identifier &obg) { name = obg.name; };

	void set_name(string &N) { name = N; };
	string &get_name() { return name; };
};

class Constant
{
	string name;
public:
	Constant(string &NAME) { name = NAME; };
	Constant(const Constant &obg) { name = obg.name; };

	void set_name(string &N) { name = N; };
	string &get_name() { return name; };
};

class All_KeyWords//Все ключевые слова из входного файла
{
	vector <string> keyWords;
public:
	All_KeyWords();

	bool operator ==(string &obg);//Есть ли среди всех ключевых слов слово obg?

};

class All_Dividers//Все ключевые слова из входного файла
{
	vector <string> dividers;
public:
	All_Dividers();
	
	bool operator ==(string &obg);//Есть ли среди всех разделителей слово obg?
};

template <typename T>
class Table
{
	vector <T> table;
	int count;
public:
	Table();

	Table <T> &operator +=(T &obg);
	T operator [](int num);
};

template<typename T>
inline Table<T>::Table()
{
	count = 0;
}

template<typename T>
inline Table<T>& Table<T>::operator+=(T & obg)
{
	table.push_back(obg);
	count++;
	
	return *this;
}

template<typename T>
inline T Table<T>::operator[](int num)
{
	return table[num];
}
