#pragma once
#include"Parser.h"

class Base_NeTerminal;

class Terminal: public Base_NeTerminal
{
	Terminal() = delete;

public:
	Terminal(int *now_lex, Scaner * All_table, Base_NeTerminal *parent, string name) : Base_NeTerminal{ now_lex, All_table, parent, name }{ };

	Base_NeTerminal *derivation(int *now_lex, Scaner *table, MyCheckVector *_MyCheck) override;
};