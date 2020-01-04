#pragma once
#include<string>
#include"Parser.h"

using namespace std;

class Base_NeTerminal;

class Terminal;

class program: public Base_NeTerminal
{
	program() = delete;

public:
	
	explicit program(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, "program" }{};

	Base_NeTerminal *getSyntaxTree();//Возвращает указатель на корень
	virtual Base_NeTerminal *derivation(int *now_lex, Scaner *table) override;
};