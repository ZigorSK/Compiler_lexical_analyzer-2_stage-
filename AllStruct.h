#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

enum {KEYWORD, DIVIDER, IDENTIFIER, CONSTANT, END_OF_programM, ERROR, BEGIN_STATE};

class Token//1 Лексема
{
	string name;
	int type;//1-ID; 2- KEYWORD; 3 -DIVIDER; 4-CONSTANT.

public:
	Token() :name(""), type(ERROR) {};
	Token(string &NAME, int TYPE);
	Token(const Token &obg);

	void set_name(string &N) { name = N; };
	string &get_name() { return name; };

	void set_type(int N) { type = N; };
	int get_type() { return type; };

	Token &operator=(Token &obg);
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

	vector <string> & get_vect_key_word() { return keyWords; };
	bool operator ==(string &obg);//Есть ли среди всех ключевых слов слово obg?

};

class All_Dividers//Все ключевые слова из входного файла
{
	vector <string> dividers;
public:
	All_Dividers();
	
	vector <string> & get_dividers() { return dividers; };
	bool operator ==(string &obg);//Есть ли среди всех разделителей слово obg?
};

template <typename T>
class Table
{
	vector <T> table;
	int count;
public:
	Table();

	int get_count() { return count; };
	vector <T> &get_table() { return table; };


	Table<T> &operator=(Table<T> obg);
	Table <T> &operator +=(T &obg);
	T &operator [](int num);
	bool operator ==(string &obg);

};

template<typename T>
inline Table<T>::Table()
{
	count = 0;
}

template<typename T>
inline Table<T>& Table<T>::operator=(Table<T> obg)
{
	int j = 0;
	for (auto i  : obg.get_table())
	{
		table[j] = i;
		j++;
	}
	count = obg.get_count();
	return *this;
}

template<typename T>
inline Table<T>& Table<T>::operator+=(T & obg)
{
	table.push_back(obg);
	count++;
	
	return *this;
}

template<typename T>
inline bool Table<T>::operator==(string & obg)
{
	for (auto var : table)
	{
		if (obg == var.get_name())
			return true;
	}

	return false;
}

template<typename T>
inline T &Table<T>::operator[](int num)
{
	return table[num];
}
