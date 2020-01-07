#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

enum {KEYWORD, DIVIDER, IDENTIFIER, CONSTANT, END_OF_programM, ERROR, BEGIN_STATE};

class Token//1 �������
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
	string id_type;//��� ��������������
	string value;
	bool dec;// false - �� ���������, true ��������
public:
	Identifier(string &NAME) { name = NAME; id_type = "int"; dec = false;/*�� ��������*/ value = "";/*���� ������ ������, �� �� ����������������*/ };
	Identifier(const Identifier &obg) { name = obg.name; id_type = obg.id_type; dec = obg.dec;/*�� ��������*/ value = obg.value; };

	void set_name(string &N) { name = N; };
	string &get_name() { return name; };

	void set_id_type(string &N) { id_type = N; };
	string &get_id_type() { return id_type; };

	void set_dec(bool N) { dec = N; };
	bool get_dec() { return dec; };

	void set_value(string &N) { value = N; };
	string &get_value() { return value; };
};

class Constant
{
	string name;
	string const_type;//��� ��������� - int, char(���� ������ � '')
public:
	Constant(string &NAME) { name = NAME; const_type ="int" ;};
	Constant(const Constant &obg) {name = obg.name; const_type = const_type = obg.const_type;};

	void set_name(string &N) { name = N; };
	string &get_name() { return name; };

	void set_const_type(string &N) { const_type = N; };
	string &get_const_type() { return const_type; };
};

class All_KeyWords//��� �������� ����� �� �������� �����
{
	vector <string> keyWords;
public:
	All_KeyWords();

	vector <string> & get_vect_key_word() { return keyWords; };
	bool operator ==(string &obg);//���� �� ����� ���� �������� ���� ����� obg?

};

class All_Dividers//��� �������� ����� �� �������� �����
{
	vector <string> dividers;
public:
	All_Dividers();
	
	vector <string> & get_dividers() { return dividers; };
	bool operator ==(string &obg);//���� �� ����� ���� ������������ ����� obg?
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

	T * finde(string & obg)//���� � ������� ������� � ������ obg(��� �������� � ID)
	{
		for (auto i : table)
		{
			if (i.get_name() == obg)
				return &i;
		}
	};
	int finde_num(string & obg)//���� � ������� ������� � ������ obg(��� �������� � ID)
	{
		int Mycount = 0;
		for (auto i : table)
		{
			if (i.get_name() == obg)
				return Mycount;
			Mycount++;
		}
	};
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
